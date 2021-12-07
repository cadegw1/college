/*
        Author: W. Douglas Lafield
        OrderedList.h
*/
#ifndef _ORDERED_LIST_GUARD
#define _ORDERED_LIST_GUARD 1
#define _ARRAY_LIST_MAX_NUM_OF_NODES 100000

using namespace std;

template <class T>
class OrderedList
{
	
	private:
		/* number of items currently in the list */
		int length; 	
		
		/* place where the list is stored */
		T nodes[_ARRAY_LIST_MAX_NUM_OF_NODES];	
		
		/* function that returns -1 if the left argument is greater 
		 * than the right argument, returns 1 if the right argument
		 * is greater than the left argument, and 0 otherwise */		
		int (*defaultCompare)(T, T);	
		
		/* the following prototype is for an optional function,
		 * if you don't wish for searchReturnIndex to be used, 
		 * you may comment the prototype out */
		int searchReturnIndex(T target);
		/* If there exists a node in the list that matches the target, 
		 * return its index
		 * otherwise, return -1 if target would be the first item
		 * and return index of highest item lower than what would be
		 * the index of the target, had the target existed in the list
		 * */
	 
		void sort(int (*compare)(T, T));
	public:
		/* constructer */
		OrderedList(int (*dc)(T, T))
		{ 
			defaultCompare = dc; 
			length = 0; 
		}
		
		/* destructer */
		~OrderedList() {}
		
		T getNode(int index);
		int getLength();
		
		void setNode(int index, T value);
		
		
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
		 
		//void traverseByGrade(void);
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
T OrderedList<T>::getNode(int index) 
{ 
	return nodes[index]; 
} /* get node */

/***************************************************/

template <class T>
void OrderedList<T>::setNode(int index, T value) 
{ 
	nodes[index] = value; 
} /* set node */

/***************************************************/

template <class T>
int OrderedList<T>::searchReturnIndex(T target)
{
	/* If there exists a node in the list that matches the target, 
	 * return its index
	 * otherwise, return -1 if target would be the first item
	 * and return index of highest item lower than what would be
	 * the index of the target, had the target existed in the list
	 * */
	
	if(length == 0)
		return -1;
	
	int first = 0;
	int last = length - 1;
	int mid = (first + last) / 2;
	
	T current = nodes[mid];
	
	while(last >= first)
	{
		if(defaultCompare(target, current) == 0)
			return mid;
		
		if(defaultCompare(target, current) < 0)
			last = mid - 1;
		else
			first = mid + 1;
		mid = (first + last) / 2;
		current = nodes[mid];
	}
	
	return mid;
	
} /* search return index */


/***************************************************/

template <class T>
T *OrderedList<T>::search(T target)
{
	/* If target exists in list, return pointer to the target
	 * otherwise, return null
	 * */
	
	int index = searchReturnIndex(target);
	
	if(index == -1 || defaultCompare(target, nodes[index]) != 0)
		return nullptr;
		
	return &(nodes[index]);
	
} /* search */

/***************************************************/

template <class T>
bool OrderedList<T>::insert(T newItem)
{
	/* If new item exists in list, or list is full, return false
	 * otherwise, add item to list, increment length, and return true */
	
	/* check if list is full */
	if(length == _ARRAY_LIST_MAX_NUM_OF_NODES)
	{
		cout << "List is full." << endl;
		return false;
	}
		
	/* find location */
	int index = searchReturnIndex(newItem);
	
	/* check if item exists */
	if(index >= 0 && index < _ARRAY_LIST_MAX_NUM_OF_NODES && defaultCompare(newItem, nodes[index]) == 0)
		return false;
		
	/* increment length */
	length++;
	
	/* shift items over */
	for(int i = length - 1; i > index + 1; i--)
		nodes[i] = nodes[i - 1];
	 
	/* put new item in */ 
	nodes[index + 1] = newItem;
	
	return true;
	
} /* insert */

/***************************************************/

template <class T>
bool OrderedList<T>::remove(T target)
{
	/* If target item exists in list, remove it, decrement length, and return true
	 * otherwise, return false */
	
	/* find location */
	int index = searchReturnIndex(target);
	
	/* if item doesn't exist, return false */
	if(index == -1 || defaultCompare(target, nodes[index]) != 0)
		return false;
		
	/* shift items over */
	while(index < length)
	{
		nodes[index] = nodes[index + 1];
		index++;
	}
	
	/* decrement length */
	length--;
	
	return true;

} /* delete */

/***************************************************/

template <class T>
void OrderedList<T>::sort(int (*compare)(T, T))
{
	for(int i = 0; i < length - 1; i++)
		for(int j = i + 1; j < length; j++)
			if(compare(nodes[i], nodes[j]) > 0)
			{
				T temp = nodes[i];
				nodes[i] = nodes[j];
				nodes[j] = temp;
			}
} /* sort */

/***************************************************/

template <class T>
void OrderedList<T>::traverse(void (*visit)(int, T))
{
	for(int i = 0; i < length; i++)
		visit(i, nodes[i]);
} /* traverse */

/***************************************************/

template <class T>
void OrderedList<T>::traverseByCustomOrder(void (*visit)(int, T), int (*compare)(T, T))
{
	/* sort by custom order */
	sort(compare);			
			
	/* traverse the list */
	for(int i = 0; i < length; i++)
		visit(i, nodes[i]);
		
	/* sort by default order */
	sort(defaultCompare);
	
} /* traverse by grade */

/***************************************************/

template <class T>
double OrderedList<T>::traverseDouble(double initialValue, double (*visit)(double, T))
{
	double retVal = initialValue;
	
	for(int i = 0; i < length; i++)
		retVal = visit(retVal, nodes[i]);
	
	return retVal;
	
} /* traverse double */

/***************************************************/

template <class T>
int OrderedList<T>::traverseInt(int initialValue, int (*visit)(int, T))
{
	int retVal = initialValue;
	
	for(int i = 0; i < length; i++)
		retVal = visit(retVal, nodes[i]);
	
	return retVal;
	
} /* traverse int */

/***************************************************/

template <class T>
void OrderedList<T>::traverseOut(ofstream *f, void (*visit)(ofstream *, T))
{
	for(int i = 0; i < length; i++)
		visit(f, nodes[i]);
} /* traverse for the purpose of outputing to the file */

/***************************************************/

template <class T>
int OrderedList<T>::getLength()
{ 
	return length; 
} 

/***************************************************/

#endif
