/*
        Author: W. Douglas Lafield
        OrderedList.h
*/
#ifndef _ORDERED_LIST_GUARD
#define _ORDERED_LIST_GUARD 1
#define _ARRAY_LIST_MAX_NUM_OF_NODES 100

#include "Student.h"

using namespace std;

class OrderedList
{
	
	private:
		int size; 	// number of items currently in the list
		Student nodes[_ARRAY_LIST_MAX_NUM_OF_NODES];	// place where the list is stored 
		
	public:
		/* constructer */
		OrderedList();// { length = 0; }
		
		/* destructer */
		~OrderedList();
		
		int getSize();// { return size; }
		
		bool remove(string lastName, string firstName);
		/* If target item exists in list, remove it, decrement length, and return true
		 * otherwise, return false */
	 
		bool insert(Student newItem);
		/* If new item exists in list, or list is full, return false
		 * otherwise, add item to list, increment length, and return true */
	 
		Student *search(string lastName, string firstName);
		/* If target exists in list, return pointer to the target
		 * otherwise, return null
		 * */
		 
		void traverse(void);
		/* For each student, print the student's order, name, and letter grade in the following format:
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
		 
		void traverseByGrade(void);
		/* This functions is similar to the traverse function, except that the 
		 * students are listed in order by their grade, with the highest 
		 * grade appearing first and the lowest grade appearing last.
		 * 
		 * This is accomplished by sorting the list of nodes by their grade,
		 * traversing the list, and then sorting the list by their last and 
		 * first names again.
		 * */
		 
		void traverseOut(ofstream *f, double hwWeight, double qzWeight, double fxWeight);
		/* The file *f should already be open prior to calling traverseOut.
		 * 
		 * First, output to *f the weights and number of students, then for each student, 
		 * output the student's name, homework grades, quiz grades, and exam grade to *f.
		 * */
};

#endif
