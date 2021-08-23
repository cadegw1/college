/*
        Author: Cade Williams
        OrderedList.h
*/
#ifndef _ORDERED_LIST_GUARD
#define _ORDERED_LIST_GUARD 1

using namespace std;

template <class T>
class OrderedList
{
	
	private:
		/* node structure */
		struct Node
		{
			T value;
			struct Node *nextNode;
		};
		
		/* pointer to the first node in the list */
		Node *firstNode;
	
		/* number of items currently in the list */
		int length; 	
		
		/* function that returns 1 if the left argument is greater 
		 * than the right argument, returns -1 if the right argument
		 * is greater than the left argument, and 0 otherwise */		
		int (*defaultCompare)(T, T);	
		
	public:
		/* constructer */
		OrderedList(int (*dc)(T, T))
		{ 
		}
		
		/* destructer */
		~OrderedList() 
		{
			Node *p_temp = firstNode;
			Node *p_next;
			while(p_temp != NULL)
			{
				p_next = p_temp->nextNode;
				delete p_temp;
				p_temp = p_next;
			}
			/* you must delete all nodes before deleting the ordered list */
		}
		
		int getLength();
		
		bool remove(T target);
		/* If target item exists in list, remove it, decrement length, and return true
		 * otherwise, return false */
	 
		bool insert(T newItem);
		/* If new item exists in list, or list is full, return false
		 * otherwise, add item to list, increment length, and return true */
	 
		T *search(T target);
		/* If target exists in list, return pointer to the target
		 * otherwise, return null
		 * */
		 
		void traverse(void (*visit)(int, T));
		/* For each node, run the visit function */
		
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
int OrderedList<T>::getLength() 
{ 
	return length;
} /* get length */

/***************************************************/

template <class T>
T *OrderedList<T>::search(T target)
{
	Node *p_cursor = firstNode;
	for(int index = 0; index < length; index++)
	{
		if(target.getLastName() == p_cursor->value.getLastName() && target.getFirstName() == p_cursor->value.getFirstName())
		{
			return &p_cursor->value;
		}
		p_cursor = p_cursor->nextNode;
	}
	
	return nullptr;
} /* search */

/***************************************************/

template <class T>
bool OrderedList<T>::insert(T newItem)
{
	bool b_item_nonexistant = true;
	Node *p_cursor = firstNode;
	for(int index = 0; index < length; index++)
	{
		if(newItem.getFirstName() == p_cursor->value.getFirstName() && newItem.getLastName() == p_cursor->value.getLastName())
		{
			b_item_nonexistant = false;
		}
		if(length - index > 1)
		{
			p_cursor = p_cursor->nextNode;
		}
	}
	if(b_item_nonexistant)
	{
		Node *p_temp = new Node;
		p_temp->value = newItem;
		p_temp->nextNode = firstNode;
		firstNode = p_temp;
		length++;
	}

	return b_item_nonexistant;
} /* insert */

/***************************************************/

template <class T>
bool OrderedList<T>::remove(T target)
{
	bool b_item_exists = false;
	Node *p_cursor = firstNode;
	for(int index = 0; index < length; index++)
	{
		if(target.getFirstName() == p_cursor->value.getFirstName() && target.getLastName() == p_cursor->value.getLastName())
		{
			b_item_exists = true;
			length--;
			Node *temp = p_cursor;
			p_cursor = p_cursor->nextNode;
			delete temp;
			break;
		}
		p_cursor = p_cursor->nextNode;
	}

	return b_item_exists;
} /* remove */

/***************************************************/

template <class T>
void OrderedList<T>::traverse(void (*visit)(int, T))
{
	Node *p_temp = firstNode;
	Node *p_first = firstNode;
	Node *p_item_to_compare = firstNode;
	for(int i = 0; i < length; i++)
	{
		p_first = p_temp;
		p_item_to_compare = p_temp->nextNode;
		for(int j = i+1; j < length; j++)
		{
			if(compareStudentsByName(p_first->value, p_item_to_compare->value) != -1)
			{
				p_first = p_item_to_compare;
				swap(p_temp->value, p_item_to_compare->value);
			}
			p_item_to_compare = p_item_to_compare->nextNode;
		}
		visit(i, p_temp->value);
		p_temp = p_temp->nextNode;
	}
} /* traverse */

/***************************************************/

template <class T>
double OrderedList<T>::traverseDouble(double initialValue, double (*visit)(double, T))
{
	Node *p_temp = firstNode;
	for(int index = 0; index < length; index++)
	{
		initialValue = visit(initialValue, p_temp->value);
		p_temp = p_temp->nextNode;
	}
	
	return initialValue;
} /* traverse double */

/***************************************************/

template <class T>
int OrderedList<T>::traverseInt(int initialValue, int (*visit)(int, T))
{
	Node *p_temp = firstNode;
	for(int index = 0; index < length; index++)
	{
		initialValue = visit(initialValue, p_temp->value);
		p_temp = p_temp->nextNode;
	}
	
	return initialValue;	
} /* traverse double */

/***************************************************/

template <class T>
void OrderedList<T>::traverseOut(ofstream *f, void (*visit)(ofstream *, T))
{
	Node *p_temp = firstNode;
	for(int index = 0; index < length; index++)
	{
		visit(f, p_temp->value);
		p_temp = p_temp->nextNode;
	}
}

/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/

#endif
