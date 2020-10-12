#include <tuple>

#include <unistd.h>

#include "threadpool.h"

using std::ignore;

int ThreadPool::enqueue(Task t) {
    ignore = t;

    return 0;
}

Task ThreadPool::dequeue()
{
    return worktodo;
}


void *ThreadPool::worker(void *param)
{
    /*
     * pthread_create() expects a C function, not a C++ member function,
     * so we're going to have to do this ourselves...
     *
     */

    ThreadPool *self = reinterpret_cast<ThreadPool *>(param);

    self->execute(self->worktodo.function, self->worktodo.data);

    pthread_exit(NULL);
}

void ThreadPool::execute(void (*somefunction)(void *p), void *p)
{
    somefunction(p);
}

ThreadPool::ThreadPool()
{
    pthread_create(&bee, NULL, ThreadPool::worker, this);
}

int ThreadPool::submit(void (*somefunction)(void *), void *p)
{
    worktodo.function = somefunction;
    worktodo.data = p;

    return 0;
}

void ThreadPool::shutdown()
{
    pthread_join(bee, NULL);
}
