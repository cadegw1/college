/*
        Author: [put your name here]
        OrderedList.cpp
         
        Your beloved instructer has lovingly provided you with a skeleton
        file for the Ordered List class.  All the functions are 
        there; you just need to provide the guts.
         
        Happy coding!!!
*/

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "OrderedList.h"

using namespace std;

/***************************************************/

OrderedList::OrderedList() //constructer
{ 
}

/***************************************************/

OrderedList::~OrderedList() 
{
}

/***************************************************/

int OrderedList::getSize()
{
	return size;
}

/***************************************************/

Student *OrderedList::search(string lastName, string firstName)
{   /* If target exists in list, return pointer to the target
	 * otherwise, return null
	 * */
	for(int index = 0; index < size; index++)
	{
		if(nodes[index].getLastName() == lastName && nodes[index].getFirstName() == firstName)
		{
			return &nodes[index];
		}
	}
	
	return nullptr;

} /* search */

/***************************************************/

bool OrderedList::insert(Student newItem)
{  /* If new item exists in list, or list is full, return false
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

} /* insert */

/***************************************************/

bool OrderedList::remove(string lastName, string firstName)
{	/* If target item exists in list, remove it, decrement length, and return true
	 * otherwise, return false */

	bool b_item_exists = false;
	for(int index = 0; index < size; index++)
	{
		if(nodes[index].getFirstName() == firstName && nodes[index].getLastName() == lastName)
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

} /*remove */

/***************************************************/

void OrderedList::traverse(void)
{   /* For each student, print the student's order, name, and letter grade in the following format:
	 * order <tab> lastName, firstName - <grade>
	 * 
	 * For example, the second student in the roster, whose name is 
	 * Bridgett Avendado and whose grade is D would appear as follows:
	 * 2.	Cassel, Beth - A
	 * 
	 * The students are listed in lexicographical order by their last name,
	 * with 2 or more students having the same last name being listed in
	 * lexicographical order by their first name.
	 * */
	int tempsize = size;
	int position = 0;
	Student cursor;
	Student tempA[_ARRAY_LIST_MAX_NUM_OF_NODES] = {};	// remaining elements to compare to
	Student tempB[_ARRAY_LIST_MAX_NUM_OF_NODES] = {};	// remaining elements to be compared
	for(int index = 0; index < size; index++)	// sets contents of temp arrays to that of nodes
	{
		tempA[index] = nodes[index];
		tempB[index] = nodes[index];
	}
	for(int i = 0; i < size; i++)
	{
		cursor = tempB[0];
		for(int j = 0; j < tempsize; j++)
		{
			if(cursor.isGreaterThanName(&tempA[j]) || cursor.isEqualToName(&tempA[j]))	// finds the first lexicographically occuring name in temp arrays
			{
				cursor = tempA[j];
				position = j;
			}
		}
		cout<<i + 1<<". "<<cursor.toString()<<" - "<<cursor.letterGrade()<<endl;
		nodes[i] = cursor;
		for(int k = position; k < tempsize; k++)	// removes the first lexicographically name from temp arrays
		{
			tempA[k] = tempA[k+1];
			tempB[k] = tempB[k+1];
		}
		tempsize--;
		
	}

} /* traverse */

/***************************************************/

void OrderedList::traverseByGrade(void)
{
	int tempsize = size;
	int position = 0;
	Student cursor;
	Student tempA[_ARRAY_LIST_MAX_NUM_OF_NODES] = {};	// remaining elements to compare to
	Student tempB[_ARRAY_LIST_MAX_NUM_OF_NODES] = {};	// remaining elements to be compared
	for(int index = 0; index < size; index++)
	{
		tempA[index] = nodes[index];
		tempB[index] = nodes[index];
	}
	for(int i = 0; i < size; i++)
	{
		cursor = tempB[0];
		for(int j = 0; j < tempsize; j++)
		{
			if(cursor.isLessThanGrade(&tempA[j]) || cursor.isEqualToGrade(&tempA[j]))	// finds the greatest grade in the temp arrays
			{
				cursor = tempA[j];
				position = j;
			}
		}
		cout<<i + 1<<". "<<cursor.toString()<<" - "<<cursor.letterGrade()<<endl;
		nodes[i] = cursor;
		for(int k = position; k < tempsize; k++)	// removes greatest grade from temp arrays
		{
			tempA[k] = tempA[k+1];
			tempB[k] = tempB[k+1];
		}
		tempsize--;
		
	}
} /* traverse by grade */

/***************************************************/

void OrderedList::traverseOut(ofstream *f, double hwWeight, double qzWeight, double fxWeight)
{
	*f<<hwWeight<<"\n"<<qzWeight<<"\n"<<fxWeight<<"\n"<<size<<"\n";
	Student x;
	for(int index  = 0; index < size; index++)
	{
		x = nodes[index];
		*f<<x.getLastName()<<" "<<x.getFirstName()<<" ";
		*f<<x.getHWScore(0)<<" "<<x.getHWScore(1)<<" "<<x.getHWScore(2)<<" "<<x.getHWScore(3)<<" ";
		*f<<x.getQuizScore(0)<<" "<<x.getQuizScore(1)<<" "<<x.getQuizScore(2)<<" "<<x.getQuizScore(3)<<" ";
		*f<<x.getFinalExam()<<"\n";
	}
}

/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
