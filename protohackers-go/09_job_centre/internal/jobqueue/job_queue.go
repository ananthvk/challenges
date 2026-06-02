package jobqueue

import (
	"container/heap"
	"sync"

	"github.com/ananthvk/protohackers-go/09_job_centre/internal/job"
)

type JobQueue struct {
	pq   *PQ
	name string
	mu   sync.Mutex
}

func New(name string) *JobQueue {
	return &JobQueue{
		name: name,
		pq: &PQ{
			indexMap: map[int]int{},
			jobs:     []*job.Job{},
		},
	}
}

func (jq *JobQueue) Name() string {
	return jq.name
}

func (jq *JobQueue) Enqueue(j *job.Job) {
	jq.mu.Lock()
	defer jq.mu.Unlock()
	jq.pq.Enqueue(j)
}

func (jq *JobQueue) Len() int {
	jq.mu.Lock()
	defer jq.mu.Unlock()
	return jq.pq.Len()
}

func (jq *JobQueue) Dequeue() *job.Job {
	jq.mu.Lock()
	defer jq.mu.Unlock()
	return jq.pq.Dequeue()
}

func (jq *JobQueue) Peek() *job.Job {
	jq.mu.Lock()
	defer jq.mu.Unlock()
	return jq.pq.Peek()
}

func (jq *JobQueue) Delete(id int) *job.Job {
	jq.mu.Lock()
	defer jq.mu.Unlock()
	return jq.pq.Remove(id)
}

type PQ struct {
	jobs     []*job.Job
	indexMap map[int]int
	// Maps job id to index in the array for deletion by id
}

func (pq *PQ) Enqueue(j *job.Job) {
	pq.indexMap[j.Id] = len(pq.jobs)
	heap.Push(pq, j)
}

func (pq *PQ) Len() int {
	return len(pq.jobs)
}

func (pq *PQ) Dequeue() *job.Job {
	if len(pq.jobs) == 0 {
		return nil
	}
	x := heap.Pop(pq)
	j := x.(*job.Job)
	delete(pq.indexMap, j.Id)
	return j
}

func (pq *PQ) Push(x any) {
	j := x.(*job.Job)
	pq.indexMap[j.Id] = len(pq.jobs)
	pq.jobs = append(pq.jobs, j)
}

func (pq *PQ) Peek() *job.Job {
	if len(pq.jobs) == 0 {
		return nil
	}
	return pq.jobs[0]
}

func (pq *PQ) Pop() any {
	n := len(pq.jobs)
	item := pq.jobs[n-1]
	pq.jobs[n-1] = nil
	pq.jobs = pq.jobs[0 : n-1]
	return item
}

func (pq *PQ) Less(i, j int) bool {
	return pq.jobs[i].Priority > pq.jobs[j].Priority
}

func (pq *PQ) Swap(i, j int) {
	pq.jobs[i], pq.jobs[j] = pq.jobs[j], pq.jobs[i]
	pq.indexMap[pq.jobs[i].Id] = i
	pq.indexMap[pq.jobs[j].Id] = j
}

func (pq *PQ) Remove(id int) *job.Job {
	idx, exists := pq.indexMap[id]
	if !exists {
		return nil
	}
	x := heap.Remove(pq, idx)
	j := x.(*job.Job)
	delete(pq.indexMap, id)
	return j
}
