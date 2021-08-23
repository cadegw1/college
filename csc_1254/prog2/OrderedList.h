/*
        Author: W. Douglas Lafield and Cade Williams
        OrderedList.h
*/
#ifndef _ORDERED_LIST_GUARD
#define _ORDERED_LIST_GUARD 1
#define _ARRAY_LIST_MAX_NUM_OF_NODES 100

using namespace std;

template <class T>
class OrderedList
{
	
	private:
		/* number of items currently in the list */
		int size; 	
		
		/* place where the list is stored */
		T nodes[_ARRAY_LIST_MAX_NUM_OF_NODES];	
		
		/* function that returns 1 if the left argument is greater 
		 * than the right argument, returns -1 if the right argument
		 * is greater than the left argument, and 0 otherwise */		
		int (*defaultCompare)(T, T);	
		
		void sort(int (*compare)(T, T));
	public:
		/* constructer */
		OrderedList(int (*dc)(T, T))
		{ 
			defaultCompare = dc; 
			size = 0; 
		}
		
		/* destructer */
		~OrderedList() {}
		
		int getSize();
		
		bool remove(T target);
		/* If target item exists in list, remove it, decrement size, and return true
		 * otherwise, return false */
	 
		bool insert(T newItem);
		/* If new item exists in list, or list is full, return false
		 * otherwise, add item to list, increment size, and return true */
	 
		T *search(T target);
		/* If target exists in list, return pointer to the target
		 * otherwise, return null
		 * */
		 
		void traverse(void (*visit)(int, T));
		/* For each node, run the visit function */
		 
		void traverseByCustomOrder(void (*visit)(int, T), int (*compare)(T, T));
		/* sort nodes by compare
		 * For each node, run the visit function 
		 * sort nodes by default comparison
		 *  */
		 
		double traverseDouble(double initialValue, double (*visit)(double, T));
		/* for each node, run the visit function 
		 * The initial value is used as an arguement for the first 
		 * visit.  The return value for each visit is used as an 
		 * arguement for the next visit.  The return value for the 
		 * final visit is returned.
		 * */
		 
		int traverseInt(int initialValue, int (*visit)(int, T));
		/* for each node, run the visit function 
		 * The initial value is used as an arguement for the first 
		 * visit.  The return value for each visit is used as an 
		 * arguement for the next visit.  The return value for the 
		 * final visit is returned.
		 * */
		 
		void traverseOut(ofstream *f, void (*visit)(ofstream *, T));
		/* The file *f should already be open prior to calling traverseOut.
		 * 
		 * For each node, run the visit function
		 * */
};

/***************************************************/

template <class T>
T *OrderedList<T>::search(T target)
{
	/* If target exists in list, return pointer to the target
	 * otherwise, return null
	 * */
	for(int index = 0; index < size; index++)
	{
		if(nodes[index].getLastName() == target.getLastName() && nodes[index].getFirstName() == target.getFirstName())
		{
			return &nodes[index];
		}
	}
	
	return nullptr;
}

/***************************************************/

template <class T>
bool OrderedList<T>::insert(T newItem)
{
	/* If new item exists in list, or list is full, return false
	 * otherwise, add item to list, increment size, and return true */	
	bool b_item_nonexistant = true;
	for(int index = 0; index < size; index++)
	{
		if(newItem.getFirstName() == nodes[index].getFirstName() && newItem.getLastName() == nodes[index].getLastName())
		{
			b_item_nonexistant = false;
			break;
		}
	}
	if(b_item_nonexistant)
	{
		if(size < 100)
		{
			nodes[size] = newItem;
			size++;
		}
	}

	return b_item_nonexistant;
} 

/***************************************************/

template <class T>
bool OrderedList<T>::remove(T target)
{
	/* If target item exists in list, remove it, decrement size, and return true
	 * otherwise, return false */
	bool b_item_exists = false;
	for(int index = 0; index < size; index++)
	{
		if(nodes[index].getFirstName() == target.getFirstName() && nodes[index].getLastName() == target.getLastName())
		{
			b_item_exists = true;
			size--;
			for(int i = index; i < size; i++)
			{
				nodes[i] = nodes[i + 1];
			}
			break;
		}
	}

	return b_item_exists;
}

/***************************************************/

template <class T>
void OrderedList<T>::sort(int (*compare)(T, T))
{
	int position = 0;
	T cursor;
	for(int i = 0; i < size; i++)
	{
		cursor = nodes[i];
		for(int j = i+1; j < size; j++)
		{
			if(compare(nodes[j], cursor) == -1)
			{
				cursor = nodes[j];
				position = j;
			}
		}
		if(compare(cursor, nodes[i]) != 0)
		{
			nodes[position] = nodes[i];
			nodes[i] = cursor;
		}
	}
} 

/***************************************************/

template <class T>
void OrderedList<T>::traverse(void (*visit)(int, T))
{
	sort(defaultCompare);
	for(int index = 0; index < size; index++)
	{
		visit(index, nodes[index]);
	}
} 

/***************************************************/

template <class T>
void OrderedList<T>::traverseByCustomOrder(void (*visit)(int, T), int (*compare)(T, T))
{
	/* sort by custom order */			
	/* traverse the list */
	/* sort by default order */
	sort(compare);
	for(int index = 0; index < size; index++)
	{
		visit(index, nodes[index]);
	}
	sort(defaultCompare);
}

/***************************************************/

template <class T>
double OrderedList<T>::traverseDouble(double initialValue, double (*visit)(double, T))
{
	for(int index = 0; index < size; index++)
	{
		initialValue = visit(initialValue, nodes[index]);
	}
	
	return initialValue;
}

/***************************************************/

template <class T>
int OrderedList<T>::traverseInt(int initialValue, int (*visit)(int, T))
{	
	for(int index = 0; index < size; index++)
	{
		initialValue = visit(initialValue, nodes[index]);
	}
	
	return initialValue;	
}

/***************************************************/

template <class T>
void OrderedList<T>::traverseOut(ofstream *f, void (*visit)(ofstream *, T))
{
	for(int index = 0; index < size; index++)
	{
		visit(f, nodes[index]);
	}
} /* traverse for the purpose of outputing to the file */

/***************************************************/

template <class T>
int OrderedList<T>::getSize()
{ 
	return size;
} 

/***************************************************/

#endif
