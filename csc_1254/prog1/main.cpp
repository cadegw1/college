/*
        Author: W. Douglas Lafield
        main.cpp
*/
#include <iostream>
#include <fstream>
#include "Student.h"
#include "OrderedList.h"
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define EXIT_CHOICE 7

using namespace std;

/***************************************************/

int menu(void);

/***************************************************/

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		cout << "You must enter a filename by command line." << endl;
		cout << "The command should be as follows:" << endl;
		cout << argv[0] << " [file containing roster]." << endl;
		return 0;
	}
	
	OrderedList *l = new OrderedList;
	
	/* read file */
	ifstream f;
	f.open(argv[1]);
	if(!f)
	{
		cout << "File " << argv[1] << " does not exist." << endl;
		return 0;
	}
	
	double hwWeight, qzWeight, fxWeight;
	int numInRoster;
	string tempS;
	
	f >> hwWeight >> qzWeight >> fxWeight >> numInRoster;

	for(int x = 0; x < numInRoster; x++)
	{ /* go through each student in roster */
		
		int tempHw[4];
		int tempQz[4];
		int tempFx;
		string tempFn;
		string tempLn;
		f >> tempLn >> tempFn;
		for(int i = 0; i < 4; i++)
			f >> tempHw[i];
		for(int i = 0; i < 4; i++)
			f >> tempQz[i];
		f >> tempFx;
		
		Student *tempStudent = new Student(tempLn, tempFn, tempQz, tempHw, tempFx, qzWeight, hwWeight, fxWeight);
		l->insert(*tempStudent);
		
	} /* go through each student in roster */
	
	f.close();
	
	int choice = menu();
	
	while(choice != EXIT_CHOICE)
	{
		if(choice == 1)
		{ /* search */
			
			/* get input */
			cout << "Enter first name: ";
			string firstN;
			cin >> firstN;
			cout << "Enter last name: ";
			string lastN;
			cin >> lastN;
			
			/* search */
			Student *s = l->search(lastN, firstN); 

			if(s != nullptr && s->getFirstName() == firstN && s->getLastName() == lastN)
			{
				cout << "\n\n\n" << s->toString() << "\tHw total: " << s->getTotalHW() << "\tQz total: " << s->getTotalQuizzes() << "\tFinal exam: " << s->getFinalExam() << "\tGrade: " << s->calculateGrade() << " " << s->letterGrade() << endl;
				cout << "Hmwk:\t\t\tQuiz" << endl;
				for(int i = 0; i < MIN(NUM_OF_QUIZZES, NUM_OF_HOMEWORKS); i++)
					cout << s->getHWScore(i) << "\t\t\t" << s->getQuizScore(i) << endl;
				for(int i = MIN(NUM_OF_QUIZZES, NUM_OF_HOMEWORKS) + 1; i < MAX(NUM_OF_QUIZZES, NUM_OF_HOMEWORKS); i++)
					cout << s->getHWScore(i) << "\t\t\t" << s->getQuizScore(i) << endl;
				cout << "Final Exam: " << s->getFinalExam() << "\n\n\n";
			}
			else
				cout << "No student with the name " << lastN << ", " << firstN << " was found" << endl;

		} /* search */
		
		if(choice == 2)
		{ /* insert */
			
			/* get input */
			cout << "Enter first name: ";
			string firstN;
			cin >> firstN;
			cout << "Enter last name: ";
			string lastN;
			cin >> lastN;
			
			Student *s = l->search(lastN, firstN); 
			
			if(s != nullptr && s->getFirstName() == firstN && s->getLastName() == lastN)
				cout << "The student " << lastN << ", " << firstN << " already exists in the roster" << endl;
			else
			{ /* student not found, so insert */

				int tempHw[4];
				int tempQz[4];
				int tempFx;
				for(int i = 0; i < 4; i++)
				{
					cout << "Enter grade for homework " << i + 1 << ": ";
					cin >> tempHw[i];
				}
				
				for(int i = 0; i < 4; i++)
				{
					cout << "Enter grade for quiz " << i + 1 << ": ";
					cin >> tempQz[i];
				}
				
				cout << "Enter final exam grade: ";
				cin >> tempFx;
				
				/* insert */
				Student *tempStudent = new Student(lastN, firstN, tempQz, tempHw, tempFx, qzWeight, hwWeight, fxWeight);
				if(l->insert(*tempStudent))
					cout << "New student added" << endl;
				else
					cout << "WARNING!!!  Student add failed." << endl;

			} /* student not found, so insert */
				
		} /* insert */
		
		if(choice == 3)
		{ /* remove */
			
			/* get input */
			cout << "Enter first name: ";
			string firstN;
			cin >> firstN;
			cout << "Enter last name: ";
			string lastN;
			cin >> lastN;
			
			/* delete it */
			if(l->remove(lastN, firstN))
				cout << "Student deleted" << endl;
			else
				cout << "No student with the name " << lastN << ", " << firstN << " was found" << endl;
		} /* remove */

		if(choice == 4)
			cout << "There are " << l->getSize() << " items in the list." << endl;
			
		if(choice == 5)
		{
			cout << "-----Begin List-----" << endl;
			l->traverse();
			cout << "-----End List-----" << endl;
		}
		
		if(choice == 6)
		{
			cout << "-----Begin List-----" << endl;
			l->traverseByGrade();
			cout << "-----End List-----" << endl;
		}

		choice = menu();
	}
	
	/* update file */
	ofstream g;
	g.open(argv[1]);
	l->traverseOut(&g, hwWeight, qzWeight, fxWeight);
	g.close();
	cout << "Done." << endl;
	
	return 0;
} /* main */

/***************************************************/

int menu(void)
{
	int choice;
	
	
	while(true)
	{
		cout << "1: Search" << endl;
		cout << "2: Insert" << endl;
		cout << "3: Delete" << endl;
		cout << "4: Count" << endl;
		cout << "5: List all students by name" << endl;
		cout << "6: List all students by grade" << endl;
		/* list all passing students */
		/* list all failing students */
		/* list all students with a grade of A */
		/* list all students with a grade of B */
		/* list all students with a grade of C */
		/* list all students with a grade of D */
		/* list all students with a grade of F */
		cout << "7: exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;
		if(choice >= 1 && choice <= EXIT_CHOICE)
			return choice;
		cout << "\"" << choice << "\" is not a valid option" << endl;
		
	} /* repeat until return */
	
} /* menu */

/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
