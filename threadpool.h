#ifndef THREADPOOL_H
#define THREADPOOL_H\

#include <queue>
#include <vector>
#include <semaphore.h>
//#include <condition_variable>
#include <mutex>

using std::unique_lock;
using std::mutex;

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

	//The mutexQueue is used to protect access to the queue
        static pthread_mutex_t mutexQueue;
        //The cout_mutex is used to protect the final cout
        static mutex cout_mutex;
        //The workAvailable is used to signal if there's work in the queue
        static pthread_cond_t workAvailable;
        
        //Thread pool
        pthread_t thread[NUMBER_OF_THREADS];
   	//The queue to store all the work
        static std::queue<Task> workToDo;
		
        int enqueue(Task t);
        Task dequeue();
        void execute(void (*)(void *), void *);

        static void *worker(void *);
};

#endif
