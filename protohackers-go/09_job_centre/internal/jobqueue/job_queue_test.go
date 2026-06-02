package jobqueue

import (
	"reflect"
	"testing"

	"github.com/ananthvk/protohackers-go/09_job_centre/internal/job"
)

func TestEmptyJobQueue(t *testing.T) {
	jq := New("queue1")
	if name := jq.Name(); name != "queue1" {
		t.Fatalf("expected name %q, got %q", "queue1", name)
	}

	if len := jq.Len(); len != 0 {
		t.Fatalf("expected len %d, got %d", 1, len)
	}
}

func TestSingleElementInsertion(t *testing.T) {
	jq := New("queue1")
	job := job.Job{Id: 1, Priority: 10}

	jq.Enqueue(&job)

	if got := jq.Len(); got != 1 {
		t.Fatalf("expected len %d, got %d", 1, got)
	}

	got := jq.Dequeue()
	if !reflect.DeepEqual(*got, job) {
		t.Fatalf("expected dequeued job %+v, got %+v", job, got)
	}

	if got := jq.Len(); got != 0 {
		t.Fatalf("expected len %d, got %d", 0, got)
	}
}

func TestTwoElementInsertion(t *testing.T) {
	jq := New("queue1")
	job1 := job.Job{Id: 1, Priority: 5}
	job2 := job.Job{Id: 2, Priority: 3}

	jq.Enqueue(&job1)
	jq.Enqueue(&job2)

	if got := jq.Len(); got != 2 {
		t.Fatalf("expected len %d, got %d", 2, got)
	}

	if got := jq.Dequeue(); !reflect.DeepEqual(*got, job1) {
		t.Fatalf("expected first dequeued job %+v, got %+v", job1, got)
	}

	if got := jq.Dequeue(); !reflect.DeepEqual(*got, job2) {
		t.Fatalf("expected second dequeued job %+v, got %+v", job2, got)
	}

	if got := jq.Len(); got != 0 {
		t.Fatalf("expected len %d, got %d", 0, got)
	}
}

func TestRandomOrderInsertion(t *testing.T) {
	jq := New("queue1")
	jobs := []job.Job{{Id: 3, Priority: 7}, {Id: 1, Priority: 5}, {Id: 4, Priority: 9}, {Id: 2, Priority: 6}}
	expected := []job.Job{{Id: 4, Priority: 9}, {Id: 3, Priority: 7}, {Id: 2, Priority: 6}, {Id: 1, Priority: 5}}

	for _, job := range jobs {
		jq.Enqueue(&job)
	}

	if got := jq.Len(); got != len(jobs) {
		t.Fatalf("expected len %d, got %d", len(jobs), got)
	}

	for i, want := range expected {
		if got := jq.Dequeue(); !reflect.DeepEqual(*got, want) {
			t.Fatalf("expected dequeued job %d to be %+v, got %+v", i, want, got)
		}
	}
}

func TestAscendingOrderInsertionReturnsDescending(t *testing.T) {
	jq := New("queue1")
	jobs := []job.Job{{Id: 1, Priority: 1}, {Id: 2, Priority: 2}, {Id: 3, Priority: 3}, {Id: 4, Priority: 4}}
	expected := []job.Job{{Id: 4, Priority: 4}, {Id: 3, Priority: 3}, {Id: 2, Priority: 2}, {Id: 1, Priority: 1}}

	for _, jb := range jobs {
		jq.Enqueue(&jb)
	}

	for i, want := range expected {
		if got := jq.Dequeue(); !reflect.DeepEqual(*got, want) {
			t.Fatalf("expected dequeued job %d to be %+v, got %+v", i, want, *got)
		}
	}
}

func TestFiftyDifferentJobs(t *testing.T) {
	jq := New("queue1")

	jobs := make([]job.Job, 50)

	for i := range jobs {
		jobs[i] = job.Job{Id: i + 1, Priority: i + 1}
		jq.Enqueue(&jobs[i])
	}

	if got := jq.Len(); got != len(jobs) {
		t.Fatalf("expected len %d, got %d", len(jobs), got)
	}

	for i := len(jobs) - 1; i >= 0; i-- {
		if got := jq.Dequeue(); !reflect.DeepEqual(*got, jobs[i]) {
			t.Fatalf("expected dequeued job %+v, got %+v", jobs[i], *got)
		}
	}

	if got := jq.Len(); got != 0 {
		t.Fatalf("expected len %d, got %d", 0, got)
	}
}

func TestDeleteNonExistentJobByID(t *testing.T) {
	jq := New("queue1")

	if got := jq.Delete(1); got != nil {
		t.Fatalf("expected nil when deleting missing job, got %+v", got)
	}
}

func TestDeleteAlreadyDeletedJobByID(t *testing.T) {
	jq := New("queue1")
	jb := job.Job{Id: 1, Priority: 10}

	jq.Enqueue(&jb)

	if got := jq.Delete(1); got == nil {
		t.Fatalf("expected deleted job, got nil")
	}

	if got := jq.Delete(1); got != nil {
		t.Fatalf("expected nil when deleting already deleted job, got %+v", got)
	}
}

func TestDeleteMiddleJobByID(t *testing.T) {
	jq := New("queue1")
	jobs := []job.Job{{Id: 1, Priority: 1}, {Id: 2, Priority: 2}, {Id: 3, Priority: 3}}

	for i := range jobs {
		jq.Enqueue(&jobs[i])
	}

	if got := jq.Delete(2); got == nil {
		t.Fatalf("expected deleted job, got nil")
	}

	if got := jq.Dequeue(); !reflect.DeepEqual(*got, jobs[2]) {
		t.Fatalf("expected remaining job %+v, got %+v", jobs[2], got)
	}

	if got := jq.Dequeue(); !reflect.DeepEqual(*got, jobs[0]) {
		t.Fatalf("expected remaining job %+v, got %+v", jobs[0], got)
	}
}

func TestDeleteFirstJobByID(t *testing.T) {
	jq := New("queue1")
	jobs := []job.Job{{Id: 1, Priority: 1}, {Id: 2, Priority: 2}, {Id: 3, Priority: 3}}

	for i := range jobs {
		jq.Enqueue(&jobs[i])
	}

	if got := jq.Delete(1); got == nil {
		t.Fatalf("expected deleted job, got nil")
	}

	if got := jq.Dequeue(); !reflect.DeepEqual(*got, jobs[2]) {
		t.Fatalf("expected remaining job %+v, got %+v", jobs[2], got)
	}

	if got := jq.Dequeue(); !reflect.DeepEqual(*got, jobs[1]) {
		t.Fatalf("expected remaining job %+v, got %+v", jobs[1], got)
	}
}

func TestDeleteLastJobByID(t *testing.T) {
	jq := New("queue1")
	jobs := []job.Job{{Id: 1, Priority: 1}, {Id: 2, Priority: 2}, {Id: 3, Priority: 3}}

	for i := range jobs {
		jq.Enqueue(&jobs[i])
	}

	if got := jq.Delete(3); got == nil {
		t.Fatalf("expected deleted job, got nil")
	}

	if got := jq.Dequeue(); !reflect.DeepEqual(*got, jobs[1]) {
		t.Fatalf("expected remaining job %+v, got %+v", jobs[1], got)
	}

	if got := jq.Dequeue(); !reflect.DeepEqual(*got, jobs[0]) {
		t.Fatalf("expected remaining job %+v, got %+v", jobs[0], got)
	}
}

func TestDeleteAllJobsByID(t *testing.T) {
	jq := New("queue1")
	jobs := make([]job.Job, 10)

	for i := range jobs {
		jobs[i] = job.Job{Id: i + 1, Priority: i + 1}
		jq.Enqueue(&jobs[i])
	}

	for i := range jobs {
		if got := jq.Delete(jobs[i].Id); got == nil {
			t.Fatalf("expected deleted job %+v, got nil", jobs[i])
		}
	}

	if got := jq.Len(); got != 0 {
		t.Fatalf("expected len %d, got %d", 0, got)
	}

	if got := jq.Delete(1); got != nil {
		t.Fatalf("expected nil after deleting all jobs, got %+v", got)
	}
}
