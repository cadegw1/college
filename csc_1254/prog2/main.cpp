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

//#include "LinkedList.h"
//#include "Tree.h"

#define EXIT_CHOICE 11

using namespace std;

/***************************************************/

int compareStudentsByGrade(Student a, Student b);
int compareStudentsByName(Student a, Student b);
int menu(void);
void outStudentToFile(ofstream *outFile, Student s);
void printStudent(int i, Student s);
void printStudentIf_A(int i, Student s);
void printStudentIf_B(int i, Student s);
void printStudentIf_C(int i, Student s);
void printStudentIf_D(int i, Student s);
void printStudentIf_F(int i, Student s);
void printStudentIfFailing(int i, Student s);
void printStudentIfPassing(int i, Student s);
double sumAdd(double prevSum, Student s);

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
	
	//OrderedList<int> *l = new OrderedList<int>();
	OrderedList<Student> *l = new OrderedList<Student>(compareStudentsByName);
	//LinkedList *l = new LinkedList();
	
	//Tree *t = new Tree();
	
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
			Student *s = new Student(lastN, firstN); 
			s = l->search(*s); 			
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
			
			/* search */
			Student *s = new Student(lastN, firstN); 
			s = l->search(*s); 
			
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

			Student *s = new Student(lastN, firstN); 
			//s = l->search(*s); 
			
			/* delete it */
			if(l->remove(*s))
				cout << "Student deleted" << endl;
			else
				cout << "No student with the name " << lastN << ", " << firstN << " was found" << endl;
		} /* remove */

		if(choice == 4)
			cout << "There are " << l->getSize() << " items in the list." << endl;
			
		if(choice == 5)
		{ /* list students by name */
			cout << "-----Begin List-----" << endl;
			l->traverse(printStudent);
			cout << "-----End List-----" << endl;
		} /* list students by name */
		
		if(choice == 6)
		{ /* list students by grade */
			cout << "-----Begin List-----" << endl;
			l->traverseByCustomOrder(printStudent, compareStudentsByGrade);
			cout << "-----End List-----" << endl;
		} /* list students by grade */
		
		if(choice == 7)
		{ /* list passing students */
			cout << "-----Begin List-----" << endl;
			l->traverse(printStudentIfPassing);
			cout << "-----End List-----" << endl;
		} /* list passing students */
		
		if(choice == 8)
		{ /* list failing students */
			cout << "-----Begin List-----" << endl;
			l->traverse(printStudentIfFailing);
			cout << "-----End List-----" << endl;
		} /* list failing students */
		
		if(choice == 9)
		{ /* list students by letter grade */
			
			/* get grade */
			char lGrade = ' ';
			while(true)
			{
				cout << "Please enter the grade (A-F): ";
				cin >> lGrade;
				if(lGrade == 'A' || lGrade == 'B' || lGrade == 'C' || lGrade == 'D' || lGrade == 'F')
					break;
				cout << "\"" << lGrade << "\" is not a valid grade" << endl;
			}
			cout << "-----Begin List-----" << endl;
			if(lGrade == 'A')
				l->traverse(printStudentIf_A);
			if(lGrade == 'B')
				l->traverse(printStudentIf_B);
			if(lGrade == 'C')
				l->traverse(printStudentIf_C);
			if(lGrade == 'D')
				l->traverse(printStudentIf_D);
			if(lGrade == 'F')
				l->traverse(printStudentIf_F);
			cout << "-----End List-----" << endl;
			
		} /* list students by letter grade */		
		
		if(choice == 10)
		{
			/* get sum */
			double gradeSum = l->traverseDouble(0.0, sumAdd);
			
			/* divide sum by count */
			cout << "The average grade for the class is " << gradeSum / l->getSize() << endl;
			
		} /* get grade average for the class */

		choice = menu();
	}
	
	/* update file */
	ofstream g;
	g.open(argv[1]);
	g << hwWeight << endl << qzWeight << endl << fxWeight << endl << l->getSize() << endl;
	l->traverseOut(&g, outStudentToFile);
	g.close();
	cout << "Done." << endl;
	
	return 0;
} /* main */

/***************************************************/

int compareStudentsByGrade(Student a, Student b)
{
	if(a.isEqualToGrade(&b))
		return 0;
	if(a.isGreaterThanGrade(&b))
		return -1;
	return 1;
} /* compare students by grade */

/***************************************************/

int compareStudentsByName(Student a, Student b)
{
	if(a.isEqualToName(&b))
		return 0;
	if(a.isGreaterThanName(&b))
		return 1;
	return -1;
} /* compare students by name */

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
		cout << "6: List all students by grade" << endl; // deprecate for LL and tree
		cout << "7: List all passing students " << endl;
		cout << "8: List all failing students " << endl;
		cout << "9: List all students by letter grade " << endl;
		cout << "10: Get average grade for the whole class " << endl;
		cout << "11: exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;
		if(choice >= 1 && choice <= EXIT_CHOICE)
			return choice;
		cout << "\"" << choice << "\" is not a valid option" << endl;
	} /* repeat until return */
	
} /* menu */

/***************************************************/

void outStudentToFile(ofstream *outFile, Student s)
{	
	(*outFile) << s.getLastName() << "\t" << s.getFirstName() << "\t";
	for(int j = 0; j < NUM_OF_HOMEWORKS; j++)
		(*outFile) << s.getHWScore(j) << "\t";
	for(int j = 0; j < NUM_OF_QUIZZES; j++)
		(*outFile) << s.getQuizScore(j) << "\t";
	(*outFile) << s.getFinalExam() << endl;
	
} /* output student to file */

/***************************************************/

void printStudent(int i, Student s)
{
	cout << i + 1 << ".\t" << s.toString() << " - " << s.letterGrade() << endl;
} /* print a student */

/***************************************************/

void printStudentIfPassing(int i, Student s)
{
	s.displayIfPass();
} /* print student if the student is passing */

/***************************************************/

void printStudentIfFailing(int i, Student s)
{
	s.displayIfFail();
} /* print student if the student is passing */

/***************************************************/

void printStudentIf_A(int i, Student s)
{
	s.displayIfA();
} /* print student if the student has an A */

/***************************************************/

void printStudentIf_B(int i, Student s)
{
	s.displayIfB();
} /* print student if the student has a B */

/***************************************************/

void printStudentIf_C(int i, Student s)
{
	s.displayIfC();
} /* print student if the student has a C */

/***************************************************/

void printStudentIf_D(int i, Student s)
{
	s.displayIfD();
} /* print student if the student has a D */

/***************************************************/

void printStudentIf_F(int i, Student s)
{
	s.displayIfF();
} /* print student if the student has an F */

/***************************************************/

double sumAdd(double prevSum, Student s)
{
	return prevSum + s.calculateGrade();
} /* add current grade to the sum */

/***************************************************/
/***************************************************/
/***************************************************/
