/*
  Team Members: Vinh Tran (Email: kimvinh@csu.fullerton.edu)
								Quang Nguyen (Email: quangdnguyen2211@csu.fullerton.edu)
  Course: CPSC 351 - 04
  Professor: Kenytt Avery
  Project 3: Designing a Thread Pool
*/

#include <tuple>
#include <unistd.h>
#include <semaphore.h>
#include "threadpool.h"
#include <iostream>

pthread_mutex_t mutexQueue;
sem_t sem;
std::queue<Task> ThreadPool::workToDo;

int ThreadPool::enqueue(Task t) {
	// Acquire the mutex lock
	pthread_mutex_lock(&mutexQueue);

	// Put a task into the queue
	workToDo.push(t);

	// Release the mutex lock
	pthread_mutex_unlock(&mutexQueue);

  return 0;
}

Task ThreadPool::dequeue() {

	// Retrieve the work in the head of queue and assign to 'work'
	Task work = workToDo.front();

	// Remove it from the queue
	workToDo.pop();

	return work;
}

void *ThreadPool::worker(void *param) {
	ThreadPool *self = reinterpret_cast<ThreadPool *>(param);
	Task work;

	while (true) {
		sem_wait(&sem);

		pthread_mutex_lock(&mutexQueue);

		// Breaking condition
		if(workToDo.empty()) {
			pthread_mutex_unlock(&mutexQueue);
			break;
		}

		// Remove the work from the queue
		work = self->dequeue();

		pthread_mutex_unlock(&mutexQueue);

		// Run the specified function
		self->execute(work.function, work.data);
	}
  pthread_exit(NULL);
}

void ThreadPool::execute(void (*somefunction)(void *p), void *p) {
  somefunction(p);
}

ThreadPool::ThreadPool() {
	// Initialize a mutex
	pthread_mutex_init(&mutexQueue,NULL);

	// Initialize a semaphore
	sem_init(&sem, 0, 0);

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
	sem_post(&sem);

  return 0;
}

void ThreadPool::shutdown() {
	for (int i = 0; i < NUMBER_OF_THREADS; i++) {
		sem_post(&sem);
	}
  for (int i = 0; i < NUMBER_OF_THREADS; i++) {
    pthread_join(thread[i], NULL);
	}

	// Destroy the mutex and semaphore once all task have completed
  pthread_mutex_destroy(&mutexQueue);
	sem_destroy(&sem);
}
