/**
 * Author: Cade Williams
 * This is the linked list based stack implementation
 */ 
#ifndef STACK_INCLUDE  
#define STACK_INCLUDE

using namespace std;

template <class T>
class Stack
{
    private:
        // Node structure for linked list
        struct Node
        {
            T value;
            struct Node *nextNode;
        };

        // Node at the top of the stack
        Node *topNode;

        // number of nodes currently on stack
        int size;
    
    public:
        // Constructor for Stack class
        Stack()
        {
            size = 0;
            topNode = NULL;
        }

        // Destructor for the Stack class
        ~Stack()
        {
            while(topNode != NULL)
            {
                Node * temp = topNode;
                topNode = topNode->nextNode;
                delete temp;
            }
        }

        // Creates a new node, setting top as the newest item, and incrementing size
        void push(T newNode); 

        // Returns true if there is an item in the list and decrements size, returns 
        // false if the list is empty
        bool pop();

        // Returns true if the stack is empty
        bool isEmpty();

        // If the list is not empty return the value of the item on top, else return NULL
        T *top();
};

template <class T>
void Stack<T>::push(T nI)
{
    Node * newNode = new Node;
    newNode->value = nI;
    newNode->nextNode = topNode;
    topNode = newNode;
    size++;
}

template <class T>
bool Stack<T>::pop()
{
    if(size == 0)
    {
        return false;
    }
    else
    {
        size--;
        Node * temp = topNode;
        topNode = topNode->nextNode;
        delete temp;
        return true;
    }
}

template <class T>
bool Stack<T>::isEmpty()
{
    if(size > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

template <class T>
T *Stack<T>::top()
{
    if(size == 0)
    {
        return NULL;
    }
    else
    {
        return &topNode->value;
    }
}

#endif
