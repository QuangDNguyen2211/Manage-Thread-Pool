/*
  Team Members: Vinh Tran (Email: kimvinh@csu.fullerton.edu)
								Quang Nguyen (Email: quangdnguyen2211@csu.fullerton.edu)
  Course: CPSC 351 - 04
  Professor: Kenytt Avery
  Project 3: Designing a Thread Pool
*/

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
        static const int QUEUE_SIZE = 10;

        static const int NUMBER_OF_THREADS = 10;

        //Thread pool
        pthread_t thread[NUMBER_OF_THREADS];

   	    // Initialize the queue of 'Task' struct to store all the work named 'workToDo'
        static queue<Task> workToDo;

        int enqueue(Task t);
        Task dequeue();
        void execute(void (*)(void *), void *);
        bool check_active();

        static void *worker(void *);
};

#endif
