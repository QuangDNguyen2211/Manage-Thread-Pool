#include <tuple>
#include <unistd.h>
#include <iostream>

#include "threadpool.h"

//Because worker is static, in order to work everything needs to be static
//That's why it needs to be redefine in threadpool.cpp
pthread_mutex_t ThreadPool::mutexQueue;
sem_t ThreadPool::sem;
std::queue<Task> ThreadPool::workToDo;

//lock -> push the work in the queue -> unlock -> signal the thread
//The queue needs to be lock before it can be accessed and unlock after
int ThreadPool::enqueue(Task work)
{
	pthread_mutex_lock(&mutexQueue);

	workToDo.push(work);

	pthread_mutex_unlock(&mutexQueue);

  return 0;
}

Task ThreadPool::dequeue()
{
	pthread_mutex_lock(&mutexQueue);

	Task work = workToDo.front();
	workToDo.pop();

	pthread_mutex_unlock(&mutexQueue);

	return work;
}

void *ThreadPool::worker(void *param)
{
	ThreadPool *self = reinterpret_cast<ThreadPool *>(param);
	Task work;

  while(!workToDo.empty())
  {
			 sem_post(&sem);
	     work = self->dequeue();
	     self->execute(work.function, work.data);
			 sem_wait(&sem);
	}

  pthread_exit(NULL);
}

void ThreadPool::execute(void (*somefunction)(void *p), void *p)
{
  somefunction(p);
}

ThreadPool::ThreadPool()
{
	pthread_mutex_init(&mutexQueue,NULL);
	sem_init(&sem, 0, 0);

  for(int c = 0; c < NUMBER_OF_THREADS; c++)
    pthread_create(&thread[c], NULL, ThreadPool::worker, this);
}

int ThreadPool::submit(void (*somefunction)(void *), void *p)
{
	Task work;
	work.function = somefunction;
	work.data = p;

  enqueue(work);

  return 0;
}

void ThreadPool::shutdown()
{
  for(int c = 0; c < NUMBER_OF_THREADS; c++)
      pthread_join(thread[c], NULL);

  pthread_mutex_destroy(&mutexQueue);
	sem_destroy(&sem);
}
