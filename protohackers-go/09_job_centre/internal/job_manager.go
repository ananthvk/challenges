package internal

import (
	"math"
	"sync"

	"github.com/ananthvk/protohackers-go/09_job_centre/internal/job"
	"github.com/ananthvk/protohackers-go/09_job_centre/internal/jobqueue"
)

type JobManager struct {
	mu        sync.Mutex
	queues    map[string]*jobqueue.JobQueue
	jobs      map[int]*job.Job
	nextJobId int
}

func NewJobManager() *JobManager {
	return &JobManager{
		queues:    map[string]*jobqueue.JobQueue{},
		jobs:      map[int]*job.Job{},
		nextJobId: 1,
	}
}

// Put adds the job to the queue, if the queue does not exist, a new queue is created
// It returns the id of the newly created job. This method is safe for concurrent use.
// It also sets the job id in newJob
func (jm *JobManager) Put(newJob *job.Job) int {
	jm.mu.Lock()
	var id = jm.nextJobId
	newJob.Id = id
	jm.jobs[jm.nextJobId] = newJob
	jm.nextJobId += 1
	queue, ok := jm.queues[newJob.Queue]
	if !ok {
		queue = jobqueue.New(newJob.Queue)
		jm.queues[newJob.Queue] = queue
	}
	jm.mu.Unlock()
	queue.Enqueue(newJob)
	return id
}

// Get returns the highest priority job that is present in any of the given queues
func (jm *JobManager) Get(queueNames []string) *job.Job {
	jm.mu.Lock()
	// We need to hold the lock for the whole duration, otherwise some other client can dequeue the queue that holds
	// the job with max priority
	defer jm.mu.Unlock()

	var maxPriority int = math.MinInt
	var maxPriorityQueue *jobqueue.JobQueue

	for _, queueName := range queueNames {
		queue, ok := jm.queues[queueName]
		if ok {
			job := queue.Peek()
			if job == nil {
				continue
			}
			if job.Priority > maxPriority {
				maxPriority = job.Priority
				maxPriorityQueue = queue
			}
		}
	}

	if maxPriorityQueue != nil {
		job := maxPriorityQueue.Dequeue()
		if job != nil {
			job.Running = true
			return job
		} else {
			panic("Invalid state")
		}
	}
	return nil
}

func (jm *JobManager) Delete(id int) *job.Job {
	jm.mu.Lock()
	job, ok := jm.jobs[id]
	if !ok {
		jm.mu.Unlock()
		return nil
	}
	queue, ok := jm.queues[job.Queue]
	if !ok {
		jm.mu.Unlock()
		return nil
	}
	delete(jm.jobs, id)
	jm.mu.Unlock()
	queue.Delete(id)
	return job
}

func (jm *JobManager) Abort(id int) *job.Job {
	jm.mu.Lock()
	job, ok := jm.jobs[id]
	if !ok {
		jm.mu.Unlock()
		return nil
	}
	if !job.Running {
		jm.mu.Unlock()
		return nil
	}
	job.Running = false
	queue, ok := jm.queues[job.Queue]
	if !ok {
		jm.mu.Unlock()
		panic("Invalid state, queue must exist")
	}
	jm.mu.Unlock()
	queue.Enqueue(job)
	return job
}

func (jm *JobManager) IsJobIdActive(id int) bool {
	jm.mu.Lock()
	defer jm.mu.Unlock()

	if id > jm.nextJobId {
		return false
	}

	// The job has been deleted
	_, ok := jm.jobs[id]
	if !ok {
		return false
	}
	return true
}
