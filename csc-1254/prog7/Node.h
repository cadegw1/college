/*
        Author: Cade Williams
        Node.h
*/
#ifndef _NODE_GUARD
#define _NODE_GUARD 1

using namespace std;

template <class T>
class Node
{
	public:
		T *value;
		struct Node *left;
		struct Node *right;

		Node(T *newValue) 
		{ 
			value = newValue;
		}
		
		~Node()
		{
		}
		
		bool insert(T *newItem, int (*defaultCompare)(T, T));
		/* If new item exists in tree, return false
		 * otherwise, add item to tree, and return true */
		 
		bool remove(T *target, int (*defaultCompare)(T, T));
		/* If target item exists in tree, remove it, and return true
		 * otherwise, return false */
		 
		T *search(T *target, int (*defaultCompare)(T, T));
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
T *Node<T>::search(T *target, int (*defaultCompare)(T, T))
{	
	if(value == NULL)
	{
		return nullptr;
	}
	else if(target->isEqualToName(value))
	{
		return value;
	}
	else if(target->isLessThanName(value))
	{
		if(left == NULL)
		{
			return nullptr;
		}
		left->search(target, defaultCompare);
	}
	else if(target->isGreaterThanName(value))
	{
		if(right == nullptr)
		{
			return nullptr;
		}
		right->search(target, defaultCompare);
	}
	else
	{
		return nullptr;
	}
} /* search */

/***************************************************/

template <class T>
bool Node<T>::insert(T *newItem, int (*defaultCompare)(T, T))
{	
	if(newItem->isLessThanName(value))
	{
		if(left == NULL)
		{
			Node<T> * tempNode = new Node<T>(newItem);
			left = tempNode;
			return true;
		}
		else
		{
			left->insert(newItem, defaultCompare);
		}
	}
	else if(newItem->isGreaterThanName(value))
	{
		if(right == NULL)
		{
			Node<T> * tempNode = new Node<T>(newItem);
			right = tempNode;
			return true;
		}
		else
		{
			right->insert(newItem, defaultCompare);
		}
		
	}
	else
	{
		return false;
	}
} /* insert */

/***************************************************/

template <class T>
bool Node<T>::remove(T *target, int (*defaultCompare)(T, T))
{
	if(target->isLessThanName(value))
	{
		if(left == NULL)
		{
			return false;
		}
		else
		{
			if(left->right->value->isEqualToName(target))
			{
				Node<T> * current = left->right;
				Node<T> * temp = nullptr;
				if(current->right == NULL && current->left == NULL)
				{
					left->right = NULL;
				}
				else if(current->right == NULL && current->left != NULL)
				{
					left->right = current->left;
				}
				else if(current->left == NULL && current->right != NULL)
				{
					left->right = current->right;
				}
				else
				{
					while(current->right != NULL)	// finds the predecessor to replace with root
					{
						if(current->right->right == NULL)
						{
							temp = current;
						}
						current = current->right;
					}
					value = current->value;
					temp->right = NULL;
				}
				delete current;
				return true;
			}
			else if(left->left->value->isEqualToName(target))
			{
				Node<T> * current = left->left;
				if(current->right == NULL && current->left == NULL)
				{
					left->left = NULL;
				}
				else if(current->right == NULL && current->left != NULL)
				{
					left->left = current->left;
				}
				else if(current->left == NULL && current->right != NULL)
				{
					left->left = current->right;
				}
				else
				{
					
				}
				delete current;
				return true;
			}
			left->remove(target, defaultCompare);
		}
	}
	else if(target->isGreaterThanName(value))
	{
		if(right == NULL)
		{
			return false;
		}
		else
		{
			right->remove(target, defaultCompare);
		}
	}
} /* remove */

/***************************************************/

template <class T>
void Node<T>::traverse(void (*visit)(T))
{	
	if(left != NULL)
	{
		left->traverse(visit);
	}
	visit(*value);
	if(right != NULL)
	{
		right->traverse(visit);
	}
} /* traverse */

/***************************************************/

template <class T>
double Node<T>::traverseDouble(double initialValue, double (*visit)(double, T))
{	
	if(left != NULL)
	{
		initialValue = left->traverseDouble(initialValue, visit);
	}
	initialValue = visit(initialValue, *value);
	if(right != NULL)
	{
		initialValue = right->traverseDouble(initialValue, visit);
	}
	return initialValue;
} /* traverse double */

/***************************************************/

template <class T>
int Node<T>::traverseInt(int initialValue, int (*visit)(int, T))
{
	if(left != NULL)
	{
		initialValue = left->traverseInt(initialValue, visit);
	}
	initialValue = visit(initialValue, *value);
	if(right != NULL)
	{
		initialValue = right->traverseInt(initialValue, visit);
	}
	return initialValue;
} /* traverse int */

/***************************************************/

template <class T>
void Node<T>::traverseOut(ofstream *f, void (*visit)(ofstream *, T))
{
	if(left != NULL)
	{
		left->traverseOut(f, visit);
	}
	visit(f, *value);
	if(right != NULL)
	{
		right->traverseOut(f, visit);
	}
} /* traverse out */

/***************************************************/

#endif
