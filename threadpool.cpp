/*
  Team Members: Vinh Tran (Email: kimvinh@csu.fullerton.edu)
								Quang Nguyen (Email: quangdnguyen2211@csu.fullerton.edu)
  Course: CPSC 351 - 04
  Professor: Kenytt Avery
  Project 3: Designing a Thread Pool
*/

#include <tuple>
#include <unistd.h>
#include <iostream>
#include "threadpool.h"

pthread_mutex_t ThreadPool::mutexQueue;
sem_t ThreadPool::sem;
std::queue<Task> ThreadPool::workToDo;

int ThreadPool::enqueue(Task t) {
	// Acquire the mutex lock
	pthread_mutex_lock(&mutexQueue);

	// Push 'work' into the queue
	workToDo.push(t);

	// Release the mutex lock
	pthread_mutex_unlock(&mutexQueue);

  return 0;
}

Task ThreadPool::dequeue() {
	// Acquire the mutex lock
	pthread_mutex_lock(&mutexQueue);

	// Retrieve the work in the head of queue and assign to 'work'
	Task work = workToDo.front();
	// Remove it from the queue
	workToDo.pop();

	// Release the mutex lock
	pthread_mutex_unlock(&mutexQueue);

	return work;
}

void *ThreadPool::worker(void *param) {
	ThreadPool *self = reinterpret_cast<ThreadPool *>(param);
	Task work;

	// Wait for available work
	sem_wait(&sem);

	while (!workToDo.empty()) {
		// Remove the work from the queue
		work = self->dequeue();

		// Run the specified function
		self->execute(work.function, work.data);
	}

	// Unlock the semaphore
	sem_post(&sem);

  pthread_exit(NULL);
}

void ThreadPool::execute(void (*somefunction)(void *p), void *p) {
  somefunction(p);
}

ThreadPool::ThreadPool() {
	// Initialize a mutex
	pthread_mutex_init(&mutexQueue,NULL);

	// Initialize a semaphore
	sem_init(&sem, 0, 1);

	// Create threads
  for(int i = 0; i < NUMBER_OF_THREADS; i++) {
    pthread_create(&thread[i], NULL, ThreadPool::worker, this);
	}
}

int ThreadPool::submit(void (*somefunction)(void *), void *p) {
	// Push tasks to the queue by calling enqueue() function
	Task work;
	work.function = somefunction;
	work.data = p;
  enqueue(work);

  return 0;
}

void ThreadPool::shutdown() {
  for (int i = 0; i < NUMBER_OF_THREADS; i++) {
    pthread_join(thread[i], NULL);
	}

	// Destroy the mutex and semaphore once all task have completed
  pthread_mutex_destroy(&mutexQueue);
	sem_destroy(&sem);
}
