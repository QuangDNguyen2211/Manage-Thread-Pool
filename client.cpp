#include <cstdlib>
#include <iostream>

#include "threadpool.h"

using std::cout;
using std::endl;

struct data {
    int a, b;
};

void add(void *param)
{
    data *temp = reinterpret_cast<data *>(param);

    cout << "I add two values " << temp->a << " and " << temp->b
         << " result = " << temp->a + temp->b << endl;
}

int main()
{
    // create some work to do
    data work = {5, 10};

    ThreadPool pool;
    pool.submit(add, &work);

    // may be helpful
    // sleep(3);

    pool.shutdown();

    return EXIT_SUCCESS;
}
