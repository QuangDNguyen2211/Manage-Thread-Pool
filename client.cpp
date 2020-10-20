/*
  Team Members: Vinh Tran (Email: kimvinh@csu.fullerton.edu)
								Quang Nguyen (Email: quangdnguyen2211@csu.fullerton.edu)
  Course: CPSC 351 - 04
  Professor: Kenytt Avery
  Project 3: Designing a Thread Pool
*/

#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include "threadpool.h"
#include <time.h>

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
  const int number_of_job = 10;

  // Initialize the thread pool
	ThreadPool pool;
  // Initialize the array which contains 'data' structs
  data works[number_of_job];

  srand(time(NULL));
	for(int i = 0; i < number_of_job; ++i) {
    // Generate a random number from 0 to 4 and assign it to the value 'a' of 'data' struct
		works[i].a = rand() % 5;
    // Generate a random number from 5 to 9 and assign it to the value 'b' of 'data' struct
    works[i].b = rand() % 5 + 5;

    // Submit a task to the thread pool
		pool.submit(add, &works[i]);
	}

  pool.shutdown();

  return EXIT_SUCCESS;
}
