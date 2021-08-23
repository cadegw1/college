/*
        Author: Cade Williams
        OrderedList.h
*/
#ifndef _ORDERED_LIST_GUARD
#define _ORDERED_LIST_GUARD 1

#include "Node.h"

using namespace std;

template <class T>
class OrderedList
{
	
	private:
		
		/* pointer to the first node in the list */
		Node<T> *root;
	
		/* number of items currently in the list */
		int sizeOfTree; 	
		
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
		}
		
		int getLength();
		
		bool remove(T *target);
		/* If target item exists in tree, remove it, decrement size, and return true
		 * otherwise, return false */
	 
		bool insert(T *newItem);
		/* If new item exists in tree, return false
		 * otherwise, add item to tree, increment length, and return true */
	 
		T *search(T *target);
		/* If target exists in tree, return pointer to the target
		 * otherwise, return null
		 * */
		 
		void traverse(void (*visit)(T));
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
	return sizeOfTree;
} /* get length */

/***************************************************/

template <class T>
T *OrderedList<T>::search(T *target)
{
	if(root == NULL)
	{
		return nullptr;	// target doesn't exist
	}
	else if(target->isEqualToName(root->value))
	{
		return root->value;
	}
	else if(target->isLessThanName(root->value))
	{
		root->left->search(target, defaultCompare);
	}
	else if(target->isGreaterThanName(root->value))
	{
		root->right->search(target, defaultCompare);
	}
	else
	{
		return nullptr;	
	}
} /* search */

/***************************************************/

template <class T>
bool OrderedList<T>::insert(T *newItem)
{	
	if(root == NULL)
	{
		Node<T> * tempNode = new Node<T>(newItem);
		root = tempNode;
		sizeOfTree++;
		return true;
	}
	Node<T> * current = root;
	if(newItem->isEqualToName(current->value))
	{
		return false;	// there is a duplicate item
	}
	else if(newItem->isLessThanName(current->value))
	{
		if(current->left == NULL)
		{
			Node<T> * tempNode = new Node<T>(newItem);
			current->left = tempNode;
			sizeOfTree++;
		}
		else
		{
			if(current->left->insert(newItem, defaultCompare))
			{
				sizeOfTree++;
			}
		}
	}
	else if(newItem->isGreaterThanName(current->value))
	{
		if(current->right == NULL)
		{
			Node<T> * tempNode = new Node<T>(newItem);
			current->right = tempNode;
			sizeOfTree++;
		}
		else
		{
			if(current->right->insert(newItem, defaultCompare))
			{
				sizeOfTree++;
			}
		}
	}
} /* insert */

/***************************************************/

template <class T>
bool OrderedList<T>::remove(T *target)
{
	if(target->isEqualToName(root->value))
	{
		Node<T> * current = root->left;
		Node<T> * temp = nullptr;
		while(current->right != NULL)	// finds the predecessor to replace with root
		{
			if(current->right->right == NULL)
			{
				temp = current;
			}
			current = current->right;
		}
		root->value = current->value;
		temp->right = NULL;
		delete current;
		return true;
	}
	else if(target->isLessThanName(root->value))
	{
		if(root->left == NULL)
		{
			return false;	// target doesn't exist
		}
		else
		{
			// need to add preemptive check for the target
			root->left->remove(target, defaultCompare);
		}
	}
	else if(target->isGreaterThanName(root->value))
	{
		if(root->right == NULL)
		{
			return false;	// target doesn't exist
		}
		else
		{
			root->right->remove(target, defaultCompare);
		}
	}
} /* delete */

/***************************************************/

template <class T>
void OrderedList<T>::traverse(void (*visit)(T))
{
	if(root->left != NULL)
	{
		root->left->traverse(visit);
	}
	visit(*root->value);
	if(root->right != NULL)
	{
		root->right->traverse(visit);
	}
} /* traverse */

/***************************************************/
template <class T>
double OrderedList<T>::traverseDouble(double initialValue, double (*visit)(double, T))
{
	if(root->left != NULL)
	{
		initialValue = root->left->traverseDouble(initialValue, visit);
	}
	initialValue = visit(initialValue, *root->value);
	if(root->right != NULL)
	{
		initialValue = root->right->traverseDouble(initialValue, visit);
	}
	return initialValue;
} /* traverse double */

/***************************************************/

template <class T>
int OrderedList<T>::traverseInt(int initialValue, int (*visit)(int, T))
{
	if(root->left != NULL)
	{
		initialValue = root->left->traverseInt(initialValue, visit);
	}
	initialValue = visit(initialValue, *root->value);
	if(root->right != NULL)
	{
		initialValue = root->right->traverseInt(initialValue, visit);
	}
	return initialValue;
} /* traverse int */

/***************************************************/

template <class T>
void OrderedList<T>::traverseOut(ofstream *f, void (*visit)(ofstream *, T))
{
	if(root->left != NULL)
	{
		root->left->traverseOut(f, visit);
	}
	visit(f, *root->value);
	if(root->right != NULL)
	{
		root->right->traverseOut(f, visit);
	}
} /* traverse for the purpose of outputing to the file */

/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/

#endif
