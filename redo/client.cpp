#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <time.h>

#include "threadpool.h"

using std::cout;
using std::endl;

struct data {
    int a, b;
};

void add(void *param) {
    data *temp = reinterpret_cast<data *>(param);

    cout << "I add two values " << temp->a << " and " << temp->b
         << " result = " << temp->a + temp->b << endl;
}

int main() {
    // create some work to do
    const int number_of_tasks = 10;

    data works[number_of_tasks];

    ThreadPool pool;

    srand(time(NULL));
    for (int i = 0; i < number_of_tasks; i++) {
      // Generate a random number from 0 to 4 and assign it to the value 'a' of 'data' struct
  		works[i].a = rand() % 5;
      // Generate a random number from 5 to 9 and assign it to the value 'b' of 'data' struct
      works[i].b = rand() % 5 + 5;

      // Submit a task to the thread pool
  		while (pool.submit(add, &works[i]) != 0) {
        sleep(1);
      }
    }

    sleep(1);

    pool.shutdown();

    return EXIT_SUCCESS;
}
