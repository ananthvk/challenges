package internal

import (
	"bufio"
	"log/slog"
	"net"
	"time"

	"github.com/ananthvk/protohackers-go/09_job_centre/internal/job"
)

// Handle handles a single client connection. This should be run in a separate gorutine so that requests can be handled
// concurrently.
func Handle(jobManager *JobManager, connection net.Conn) {
	slog.Info("client connected", "remote_address", connection.RemoteAddr().String())
	activeJobs := map[int]struct{}{}
	defer func() {
		slog.Info("client disconnected", "address", connection.RemoteAddr().String(), "aborted active jobs", len(activeJobs))
		for k := range activeJobs {
			jobManager.Abort(k)
		}
	}()
	defer connection.Close()

	r := bufio.NewReader(connection)
	w := bufio.NewWriter(connection)

	for {
		line, err := r.ReadBytes('\n')
		if err != nil {
			return
		}
		request, err := ParseRequest(line)
		if err != nil {
			response := SerializeResponse(Response{Status: "error", Error: err.Error()})
			if _, err = w.WriteString(response); err != nil {
				return
			}
			if err = w.Flush(); err != nil {
				return
			}
			continue
		}

		var response Response

		switch request.RequestType {
		case "put":
			id := jobManager.Put(&job.Job{
				Queue:    *request.Queue,
				Payload:  request.Job,
				Priority: *request.Priority,
			})
			response = Response{Status: "ok", Id: id}
		case "get":
			var gotJob bool
			for {
				job := jobManager.Get(request.Queues)
				if job != nil {
					activeJobs[job.Id] = struct{}{}
					response = Response{
						Status:   "ok",
						Id:       job.Id,
						Job:      job.Payload,
						Priority: job.Priority,
						Queue:    job.Queue,
					}
					gotJob = true
					break
				}
				// No job available, wait for one
				if request.WaitParsed {
					// TODO
					// Very simple crude solution - write a better one with subscribers later
					// This just polls every 500ms
					time.Sleep(time.Millisecond * 500)
					continue
				}
				break
			}
			if !gotJob {
				response = Response{Status: "no-job"}
			}
		case "delete":
			job := jobManager.Delete(*request.Id)
			if job != nil {
				response = Response{Status: "ok"}
			} else {
				response = Response{Status: "no-job"}
			}
		case "abort":
			if !jobManager.IsJobIdActive(*request.Id) {
				response = Response{Status: "no-job"}
				break
			}

			_, ok := activeJobs[*request.Id]
			if !ok {
				response = Response{Status: "error", Error: "cannot abort jobs that have not been created by this client"}
				break
			}

			job := jobManager.Abort(*request.Id)
			delete(activeJobs, *request.Id)
			if job != nil {
				response = Response{Status: "ok"}
			} else {
				response = Response{Status: "no-job"}
			}

		default:
			panic("invalid state")
		}

		if _, err = w.WriteString(SerializeResponse(response)); err != nil {
			return
		}
		if err = w.Flush(); err != nil {
			return
		}
	}
}
