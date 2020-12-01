#include <iostream>
#include <tuple>
#include <unistd.h>
#include <mutex>
#include <semaphore.h>
#include "threadpool.h"

using std::cout;

pthread_mutex_t mutexQueue;
sem_t sem;
queue<Task> ThreadPool::worktodo;

int ThreadPool::enqueue(Task t) {
  pthread_mutex_lock(&mutexQueue);

  if (worktodo.size() > QUEUE_SIZE) {
    pthread_mutex_unlock(&mutexQueue);
    return 1;
  }

  worktodo.push(t);

  pthread_mutex_unlock(&mutexQueue);

  return 0;
}

Task ThreadPool::dequeue() {
  pthread_mutex_lock(&mutexQueue);

  Task work = worktodo.front();
  worktodo.pop();

  pthread_mutex_unlock(&mutexQueue);
  return work;
}

void *ThreadPool::worker(void *param) {
  /*
   * pthread_create() expects a C function, not a C++ member function,
   * so we're going to have to do this ourselves...
   *
   */
  ThreadPool *self = reinterpret_cast<ThreadPool *>(param);
  Task work;

  while (true) {
    sem_wait(&sem);
    work = self->dequeue();
    pthread_mutex_lock(&mutexQueue);
    self->execute(work.function, work.data);
    pthread_mutex_unlock(&mutexQueue);
  }

  pthread_exit(NULL);
}

void ThreadPool::execute(void (*somefunction)(void *p), void *p) {
  somefunction(p);
}

ThreadPool::ThreadPool() {
  pthread_mutex_init(&mutexQueue, NULL);
  sem_init(&sem, 0, 0);
  for (int i = 0; i < NUMBER_OF_THREADS; i++) {
    pthread_create(&bee[i], NULL, ThreadPool::worker, this);
  }
}

int ThreadPool::submit(void (*somefunction)(void *), void *p) {
  int check = 0;
  Task work;
  work.function = somefunction;
  work.data = p;

  check = enqueue(work);
  if (!check) {
    sem_post(&sem);
  }

  return check;
}

void ThreadPool::shutdown() {
  for (int i = 0; i < NUMBER_OF_THREADS; i++) {
    pthread_cancel(bee[i]);
    pthread_join(bee[i], NULL);
  }
  sem_destroy(&sem);
  pthread_mutex_destroy(&mutexQueue);
}
