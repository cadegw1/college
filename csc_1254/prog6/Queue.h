/*
        Author: W. Douglas Lafield
        Queue.h
*/
#ifndef _QUEUE_GUARD
#define _QUEUE_GUARD 1
#define QUEUE_MAX_NUM_OF_NODES 1000

using namespace std;

template <class T>
class Queue
{
	
	private:
		/* number of items currently in the queue */
		int length; 	
		T queue[QUEUE_MAX_NUM_OF_NODES];
		int first;
		int last;
		/* You put the rest of the private variables here */
		
	public:
		/* constructer */
		Queue() 
		{
			length = 0;
			first = 0;
			last = 0;
		}
		
		/* destructer */
		~Queue() 
		{}
		
		int getLength() { return length; }

		bool dequeue();
		/* remove item from the front of the queue and return the item */
		
		bool enqueue(T item);
		/* add new item to the end of the queue */
		
		T *front();
		/* return item at front of the queue without dequeueing */
		
};

/***************************************************/

template <class T>
bool Queue<T>::dequeue()
{ /* remove item from the front of the queue and return the item */
	if(length == 0)
	{
		return false;
	}
	first = (first+1) % QUEUE_MAX_NUM_OF_NODES;
	length--;
	return true;
} /* dequeue */

/***************************************************/

template <class T>
bool Queue<T>::enqueue(T item)
{ /* add new item to the end of the queue */
	if(length == QUEUE_MAX_NUM_OF_NODES)
	{
		return false;
	}
	if(length == 0)
	{
		queue[0] = item;
		first = 0;
		last = 0;
		length++;
		return true;
	}
	length++;
	last = (last+1) % QUEUE_MAX_NUM_OF_NODES;
	queue[last] = item;
	return true;
	
} /* enqueue */

/***************************************************/

template <class T>
T *Queue<T>::front()
{ /* return item at front of the queue without dequeueing */
	if(length == 0)
	{
		return NULL;
	}
	return &queue[first];
} /* front */

/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/

#endif
