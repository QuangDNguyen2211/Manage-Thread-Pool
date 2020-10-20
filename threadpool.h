#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <queue>
#include <semaphore.h>
#include <mutex>

struct Task {
    void (*function)(void *);
    void *data;
};

class ThreadPool {
    public:
        ThreadPool();
        int submit(void (*)(void *), void *);
        void shutdown();

    private:
        static const int QUEUE_SIZE = 10;
        static const int NUMBER_OF_THREADS = 10;

	      // 'mutexQueue' is used to protect access to the queue
        static pthread_mutex_t mutexQueue;

        static sem_t sem;

        //Thread pool
        pthread_t thread[NUMBER_OF_THREADS];

   	    // Initialize the queue of 'Task' struct to store all the work named 'workToDo'
        static std::queue<Task> workToDo;

        int enqueue(Task t);
        Task dequeue();
        void execute(void (*)(void *), void *);

        static void *worker(void *);
};

#endif
