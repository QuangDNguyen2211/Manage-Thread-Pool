#include <tuple>

#include <unistd.h>

#include "threadpool.h"
#include <semaphore.h>

using std::ignore;

int ThreadPool::enqueue(Task work)
{
    workToDo.push(work);
    return 0;
}

Task ThreadPool::dequeue()
{ return workToDo.pop(); }

// I'm not sure about this worker function
void *ThreadPool::worker(void *param)
{
    if(!workToDo.isEmpty())
    {
      Task work = dequeue();
      execute(work.function, work.data);
    }
}

void ThreadPool::execute(void (*somefunction)(void *p), void *p)
{ somefunction(p);}

ThreadPool::ThreadPool()
{
    for(int c = 0; c < NUMBER_OF_THREADS; c++)
    {
      pthread_create(&thread, NULL, ThreadPool::worker, this);
      threadPool.push_back(thread);
    }
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
    if(threadPool[i].joinable())
      threadPool[i].join();
}
