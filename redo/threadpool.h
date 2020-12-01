#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <queue>
using std::queue;

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
        static const auto QUEUE_SIZE = 10;
        static const auto NUMBER_OF_THREADS = 10;

        static queue<Task> worktodo;
        pthread_t bee[NUMBER_OF_THREADS];

        int enqueue(Task t);
        Task dequeue();
        void execute(void (*)(void *), void *);

        static void *worker(void *);
};

#endif
