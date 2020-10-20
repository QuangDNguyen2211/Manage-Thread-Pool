#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include "threadpool.h"

using std::cout;
using std::endl;

struct data {
    int a, b;
};

const int number_of_job = 10;

void add(void *param)
{
    data *temp = reinterpret_cast<data *>(param);

    cout << "I add two values " << temp->a << " and " << temp->b
         << " result = " << temp->a + temp->b << endl;
}

int main()
{
	ThreadPool pool;
  data work[number_of_job];

  //Submit works for the program to do
	for(int i = 0; i < number_of_job; ++i)
	{
		work[i].a = i;
    work[i].b = i + 1;
		pool.submit(add, &work[i]);
	}

  pool.shutdown();

  return EXIT_SUCCESS;
}
