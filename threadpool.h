#ifndef THREADPOOL_H
#define THREADPOOL_H

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

        Queue workToDo;
        vector <pthread_t> threadPool;
        pthread_t thread;
        sem_t sem;

        int enqueue(Task w);
        Task dequeue();
        void execute(void (*)(void *), void *);

        static void *worker(void *);
};


#endif
