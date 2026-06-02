package internal

import (
	"encoding/json"
	"testing"

	"github.com/ananthvk/protohackers-go/09_job_centre/internal/job"
)

func TestGetOneJob(t *testing.T) {
}

func TestPutThenRetrieveOneJob(t *testing.T) {
	jm := NewJobManager()
	j := &job.Job{Id: 1, Queue: "Q1", Priority: 100, Payload: json.RawMessage(`{"msg":"test job"}`)}

	jm.Put(j)

	retrieved := jm.Get([]string{"Q1"})
	if retrieved == nil || retrieved.Id != j.Id {
		t.Errorf("Expected job %d, got %v", j.Id, retrieved)
	}
}

func TestDeleteJob(t *testing.T) {
	jm := NewJobManager()
	j := &job.Job{Id: 1, Queue: "Q1", Priority: 100, Payload: json.RawMessage(`{"msg":"test job"}`)}

	jm.Put(j)

	if deleted := jm.Delete(1); deleted == nil || deleted.Id != 1 {
		t.Fatalf("Expected deleted job 1, got %v", deleted)
	}

	if deleted := jm.Delete(1); deleted != nil {
		t.Errorf("Expected nil for already deleted job, got %v", deleted)
	}

	if deleted := jm.Delete(2); deleted != nil {
		t.Errorf("Expected nil for id greater than assigned ids, got %v", deleted)
	}
}

func TestAbortReturnsJobToOriginalQueue(t *testing.T) {
	jm := NewJobManager()
	j := &job.Job{Id: 1, Queue: "Q1", Priority: 100, Payload: json.RawMessage(`{"msg":"test job"}`)}

	jm.Put(j)

	claimed := jm.Get([]string{"Q1"})
	if claimed == nil || claimed.Id != 1 {
		t.Fatalf("Expected claimed job 1, got %v", claimed)
	}

	aborted := jm.Abort(1)
	if aborted == nil || aborted.Id != 1 {
		t.Fatalf("Expected aborted job 1, got %v", aborted)
	}

	retrieved := jm.Get([]string{"Q1"})
	if retrieved == nil || retrieved.Id != 1 {
		t.Errorf("Expected job 1 to be back in original queue, got %v", retrieved)
	}

	aborted = jm.Abort(1)
	if aborted == nil || aborted.Id != 1 {
		t.Fatalf("Expected aborted job 1, got %v", aborted)
	}

	if aborted := jm.Abort(1); aborted != nil {
		t.Errorf("Expected nil for already aborted job, got %v", aborted)
	}

	if aborted := jm.Abort(2); aborted != nil {
		t.Errorf("Expected nil for id greater than assigned ids, got %v", aborted)
	}
}

func TestPutMultipleJobsGetWithQueues(t *testing.T) {
	jm := NewJobManager()

	// Put 5 jobs in 5 different queues
	jobs := []*job.Job{
		{Id: 1, Queue: "Q1", Priority: 10, Payload: json.RawMessage(`{"msg":"job1"}`)},
		{Id: 2, Queue: "Q2", Priority: 20, Payload: json.RawMessage(`{"msg":"job2"}`)},
		{Id: 3, Queue: "Q3", Priority: 30, Payload: json.RawMessage(`{"msg":"job3"}`)},
		{Id: 4, Queue: "Q4", Priority: 40, Payload: json.RawMessage(`{"msg":"job4"}`)},
		{Id: 5, Queue: "Q5", Priority: 50, Payload: json.RawMessage(`{"msg":"job5"}`)},
	}

	for _, j := range jobs {
		jm.Put(j)
	}

	// Get with Q1, Q2, Q3 -> should return max (job3 with pri 30)
	retrieved := jm.Get([]string{"Q1", "Q2", "Q3"})
	if retrieved == nil || retrieved.Id != 3 {
		t.Errorf("Expected job 3, got %v", retrieved)
	}

	// Get with Q2, Q3, Q4, Q5 -> should return max (job5 with pri 50)
	retrieved = jm.Get([]string{"Q2", "Q3", "Q4", "Q5"})
	if retrieved == nil || retrieved.Id != 5 {
		t.Errorf("Expected job 5, got %v", retrieved)
	}

	// Get with all queues twice
	retrieved = jm.Get([]string{"Q1", "Q2", "Q3", "Q4", "Q5"})
	if retrieved == nil || retrieved.Id != 4 {
		t.Errorf("Expected job 4, got %v", retrieved)
	}

	retrieved = jm.Get([]string{"Q1", "Q2", "Q3", "Q4", "Q5"})
	if retrieved == nil || retrieved.Id != 2 {
		t.Errorf("Expected job 2, got %v", retrieved)
	}

	// Get with only Q5 (should be empty) -> returns nil
	retrieved = jm.Get([]string{"Q5"})
	if retrieved != nil {
		t.Errorf("Expected nil, got %v", retrieved)
	}

	// Get with all queues -> should return last element (job1)
	retrieved = jm.Get([]string{"Q1", "Q2", "Q3", "Q4", "Q5"})
	if retrieved == nil || retrieved.Id != 1 {
		t.Errorf("Expected job 1, got %v", retrieved)
	}
}
