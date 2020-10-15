#include <mutex>
#include <queue>
using namespace std;

#ifndef QUEUE
#define QUEUE

template <class value_type>
class Queue
{
public:
	bool        isEmpty(void) const
	{
		unique_lock<mutex> lock(mutex);
		return items.empty(); 
	}

	void        push(const value_type &item)
	{ 
		unique_lock<mutex> lock(mutex);
		items.push(item);
	}
	
	value_type  pop(void)
	{
		unique_lock<mutex> lock(mutex);
		assert(!isEmpty());
		value_type topItem = items.front();
		items.pop();
		return topItem;
	}

private:
	queue <value_type> items;
	mutex mutexLock;
};

#endif
