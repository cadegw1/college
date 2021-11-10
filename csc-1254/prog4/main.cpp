/*
        Author: Cade Williams
        main.cpp
*/
#include <iostream>
#include <fstream>
#include <ctime>
#include "Student.h"
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAX_NUM_OF_STUDENTS 10000

using namespace std;

/***************************************************/

int bubbleSortByAdjustedGrade(Student lst[], int length);
int bubbleSortByOriginalGrade(Student lst[], int length);
int insertSortByAdjustedGrade(Student lst[], int length);
int insertSortByOriginalGrade(Student lst[], int length);
int mergeByAdjustedGrade(Student lst[], int firstA, int lastA, int lastB);
int mergeByOriginalGrade(Student lst[], int firstA, int lastA, int lastB);
int mergeSortByAdjustedGrade(Student lst[], int first, int last);
int mergeSortByOriginalGrade(Student lst[], int first, int last);
void outList(Student lst[], int length, string fileName);
int quicksortByAdjustedGrade(Student lst[], int first, int last);
int quicksortByOriginalGrade(Student lst[], int first, int last);
int selectionSortByAdjustedGrade(Student lst[], int length);
int selectionSortByOriginalGrade(Student lst[], int length);
void swap(Student lst[], int indexA, int indexB);

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
	
	Student bubbleSortList[MAX_NUM_OF_STUDENTS];
	Student insertSortList[MAX_NUM_OF_STUDENTS];
	Student selectionSortList[MAX_NUM_OF_STUDENTS];
	Student mergeSortList[MAX_NUM_OF_STUDENTS];
	Student quickSortList[MAX_NUM_OF_STUDENTS];
	
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
		
		bubbleSortList[x] = *tempStudent;
		insertSortList[x] = *tempStudent;
		selectionSortList[x] = *tempStudent;
		mergeSortList[x] = *tempStudent;
		quickSortList[x] = *tempStudent;
		
	} /* go through each student in roster */
	
	f.close();
	
	/* do sorts */
	cout << "bubble sort by grade..." << endl;
	clock_t beginTime = clock();
	int bubbleCompares1 = bubbleSortByOriginalGrade(bubbleSortList, numInRoster);
	clock_t endTime = clock();
	double bubbleSortTime1 = double(endTime - beginTime) / CLOCKS_PER_SEC;
	outList(bubbleSortList, numInRoster, "bubbleSortByOriginalGrade.txt");
	
	cout << "bubble sort by adjusted grade..." << endl;
	beginTime = clock();
	int bubbleCompares2 = bubbleSortByAdjustedGrade(bubbleSortList, numInRoster);
	endTime = clock();
	double bubbleSortTime2 = double(endTime - beginTime) / CLOCKS_PER_SEC;
	outList(bubbleSortList, numInRoster, "bubbleSortByAdjustedGrade.txt");
	
	cout << "selection sort by grade..." << endl;
	beginTime = clock();
	int selectCompares1 = selectionSortByOriginalGrade(selectionSortList, numInRoster);
	endTime = clock();
	double selectSortTime1 = double(endTime - beginTime) / CLOCKS_PER_SEC;
	outList(selectionSortList, numInRoster, "selectSortByOriginalGrade.txt");
	
	cout << "selection sort by adjusted grade..." << endl;
	beginTime = clock();
	int selectCompares2 = selectionSortByAdjustedGrade(selectionSortList, numInRoster);
	endTime = clock();
	double selectSortTime2 = double(endTime - beginTime) / CLOCKS_PER_SEC;
	outList(selectionSortList, numInRoster, "selectSortByAdjustedGrade.txt");
	
	cout << "insertion sort by grade..." << endl;
	beginTime = clock();
	int insertCompares1 = insertSortByOriginalGrade(insertSortList, numInRoster);
	endTime = clock();
	double insertSortTime1 = double(endTime - beginTime) / CLOCKS_PER_SEC;
	outList(insertSortList, numInRoster, "insertSortByOriginalGrade.txt");
	
	cout << "insertion sort by adjusted grade..." << endl;
	beginTime = clock();
	int insertCompares2 = insertSortByAdjustedGrade(insertSortList, numInRoster);
	endTime = clock();
	double insertSortTime2 = double(endTime - beginTime) / CLOCKS_PER_SEC;
	outList(insertSortList, numInRoster, "insertSortByAdjustedGrade.txt");
	
	cout << "quick sort by grade..." << endl;
	beginTime = clock();
	int quickCompares1 = quicksortByOriginalGrade(quickSortList, 0, numInRoster - 1);
	endTime = clock();
	double quickSortTime1 = double(endTime - beginTime) / CLOCKS_PER_SEC;
	outList(quickSortList, numInRoster, "quickSortByOriginalGrade.txt");
	
	cout << "quick sort by adjusted grade..." << endl;
	beginTime = clock();
	int quickCompares2 = quicksortByAdjustedGrade(quickSortList, 0, numInRoster - 1);
	endTime = clock();
	double quickSortTime2 = double(endTime - beginTime) / CLOCKS_PER_SEC;
	outList(quickSortList, numInRoster, "quickSortByAdjustedGrade.txt");
	
	cout << "merge sort by grade..." << endl;
	beginTime = clock();
	int mergeCompares1 = mergeSortByOriginalGrade(mergeSortList, 0, numInRoster - 1);
	endTime = clock();
	double mergeSortTime1 = double(endTime - beginTime) / CLOCKS_PER_SEC;
	outList(mergeSortList, numInRoster, "mergeSortByOriginalGrade.txt");
	
	cout << "merge sort by adjusted grade..." << endl;
	beginTime = clock();
	int mergeCompares2 = mergeSortByAdjustedGrade(mergeSortList, 0, numInRoster - 1);
	endTime = clock();
	double mergeSortTime2 = double(endTime - beginTime) / CLOCKS_PER_SEC;
	outList(mergeSortList, numInRoster, "mergeSortByAdjustedGrade.txt");
	
	/* do report */
	cout << "\n\nsort:\tgrade\ttime\tadjusted grade\ttime" << endl;
	cout << "bubble\t" << bubbleCompares1 << "\t" << bubbleSortTime1 << " s\t" << bubbleCompares2 << "\t" << bubbleSortTime2 << " s" << endl;
	cout << "select\t" << selectCompares1 << "\t" << selectSortTime1 << " s\t" << selectCompares2 << "\t" << selectSortTime2 << " s" << endl;
	cout << "insert\t" << insertCompares1 << "\t" << insertSortTime1 << " s\t" << insertCompares2 << "\t" << insertSortTime2 << " s" << endl;
	cout << "quick\t" << quickCompares1 << "\t" << quickSortTime1 << " s\t" << quickCompares2 << "\t" << quickSortTime2 << " s" << endl;
	cout << "merge\t" << mergeCompares1 << "\t" << mergeSortTime1 << " s\t" << mergeCompares2 << "\t" << mergeSortTime2 << " s" << endl;

	return 0;
} /* main */

/***************************************************/

void outList(Student lst[], int length, string fileName)
{
	/* output list to file */
	ofstream f;
	f.open(fileName);
	
	for(int i = 0; i < length; i++)
		f << lst[i].outFileString() << endl;
	f.close();
	
} /* out list */

/***************************************************/

void swap(Student lst[], int indexA, int indexB)
{
	Student temp = lst[indexA];
	lst[indexA] = lst[indexB];
	lst[indexB] = temp;
} /* swap */

/***************************************************/

int bubbleSortByOriginalGrade(Student lst[], int length)
{	
	int total_swaps = 0;
	int num_of_swaps = 0;
	int j = 1;
	bool unsorted = true;
	while(unsorted)
	{
		for(int i = 0; i < length; i++)
		{
			if(lst[i].calculateGrade() < lst[j].calculateGrade())
			{
				swap(lst, i, j);
				num_of_swaps++;
			}
			j++;
		}
		if(num_of_swaps == 0)
		{
			unsorted = false;
		}
		total_swaps+=num_of_swaps;
		num_of_swaps = 0;
		j = 1;
	}
	
	return total_swaps;
} /* bubble sort by grade */

/***************************************************/

int bubbleSortByAdjustedGrade(Student lst[], int length)
{	
	int total_swaps = 0;
	int num_of_swaps = 0;	// used to check when no swaps have been made meaning the list is sorted
	int j = 1;
	bool unsorted = true;
	while(unsorted)
	{
		for(int i = 0; i < length; i++)
		{
			if(lst[i].calculateAdjustedGrade() < lst[j].calculateAdjustedGrade())
			{
				swap(lst, i, j);
				num_of_swaps++;
			}
			j++;
		}
		if(num_of_swaps == 0)
		{
			unsorted = false;
		}
		total_swaps+=num_of_swaps;
		num_of_swaps = 0;
		j = 1;
	}

	return total_swaps;
} /* bubble sort by adjusted grade */

/***************************************************/

int selectionSortByOriginalGrade(Student lst[], int length)
{
	int total_swaps = 0;
	int position = 0;
	Student cursor;
	for(int i = 0; i < length; i++)
	{
		position = i;
		cursor = lst[i];
		for(int j = i+1; j < length; j++)
		{
			if(cursor.calculateGrade() < lst[j].calculateGrade())
			{
				cursor = lst[j];
				position = j;
			}
		}
		swap(lst, i, position);
		total_swaps++;
	}

	return total_swaps;
} /* selection sort by grade */

/***************************************************/

int selectionSortByAdjustedGrade(Student lst[], int length)
{
	int total_swaps = 0;
	int position = 0;
	Student cursor;
	for(int i = 0; i < length; i++)
	{
		position = i;
		cursor = lst[i];
		for(int j = i+1; j < length; j++)
		{
			if(cursor.calculateAdjustedGrade() < lst[j].calculateAdjustedGrade())
			{
				cursor = lst[j];
				position = j;
			}
		}
		swap(lst, i, position);
		total_swaps++;
	}

	return total_swaps;
} /* selection sort by adjusted grade */

/***************************************************/

int insertSortByOriginalGrade(Student lst[], int length)
{
	int total_swaps = 0;
	for(int index = 1; index < length; index++)
	{
		Student temp = lst[index];
		int j = index - 1;
		while(lst[j].calculateGrade() < temp.calculateGrade() && j >= 0)
		{
			lst[j+1] = lst[j];
			j--;
			total_swaps++;
		}
		lst[j+1] = temp;
	}

	return total_swaps;
} /* insert sort by grade */

/***************************************************/

int insertSortByAdjustedGrade(Student lst[], int length)
{
	int total_swaps = 0;
	for(int index = 1; index < length; index++)
	{
		Student temp = lst[index];
		int j = index - 1;
		while(lst[j].calculateAdjustedGrade() < temp.calculateAdjustedGrade() && j >= 0)
		{
			lst[j+1] = lst[j];
			j--;
			total_swaps++;
		}
		lst[j+1] = temp;
	}

	return total_swaps;
} /* insert sort by adjusted grade */

/***************************************************/

int quicksortByOriginalGrade(Student lst[], int first, int last)
{
	int total_swaps = 0;
	if(last - first < 1)
	{
		return total_swaps;
	}
	int pivotIndex = last;
	for(int i = 0; i < pivotIndex; i++)
	{
		for(int j = 0; j < pivotIndex; j++)
		{
			if(lst[j].calculateGrade() < lst[pivotIndex].calculateGrade())
			{
				swap(lst[j], lst[pivotIndex-1]);
				swap(lst[pivotIndex], lst[pivotIndex-1]);
				total_swaps += 2;
				pivotIndex--;
			}
		}
	}
	total_swaps += quicksortByOriginalGrade(lst, first, pivotIndex-1);
	total_swaps += quicksortByOriginalGrade(lst, pivotIndex+1, last);

	return total_swaps;
} /* quick sort by grade */

/***************************************************/

int quicksortByAdjustedGrade(Student lst[], int first, int last)
{
	int total_swaps = 0;
	if(last - first < 1)
	{
		return total_swaps;
	}
	int pivotIndex = last;
	for(int i = 0; i < pivotIndex; i++)
	{
		for(int j = 0; j < pivotIndex; j++)
		{
			if(lst[j].calculateAdjustedGrade() < lst[pivotIndex].calculateAdjustedGrade())
			{
				swap(lst[j], lst[pivotIndex-1]);
				swap(lst[pivotIndex], lst[pivotIndex-1]);
				total_swaps += 2;
				pivotIndex--;
			}
		}
	}
	total_swaps += quicksortByAdjustedGrade(lst, first, pivotIndex-1);
	total_swaps += quicksortByAdjustedGrade(lst, pivotIndex+1, last);

	return total_swaps;
} /* quick sort by adjusted grade */

/***************************************************/

int mergeByOriginalGrade(Student lst[], int firstA, int lastA, int lastB)
{
	int total_swaps = 0;
	int i = 0, j = 0, k = 0;
	int sizeA = lastA-firstA+1;
	int sizeB = lastB-lastA;
	Student lstA[sizeA], lstB[sizeB];
	for(i = 0; i < sizeA; i++)
	{
		lstA[i] = lst[firstA+i];
	}
	for(j = 0; j < sizeB; j++)
	{
		lstB[j] = lst[lastA+j+1];
	}
	i = 0, j = 0;

	for(k = firstA; i < sizeA && j < sizeB; k++)
	{
		if(lstA[i].calculateGrade() > lstB[j].calculateGrade())
		{
			lst[k] = lstA[i++];
			total_swaps++;
		}
		else
		{
			lst[k] = lstB[j++];
			total_swaps++;
		}
	}

	while(i < sizeA)
	{
		lst[k++] = lstA[i++];
	}
	while(j < sizeB)
	{
		lst[k++] = lstB[j++];
	}

	return total_swaps;
} /* merge by grade */

/***************************************************/

int mergeSortByOriginalGrade(Student lst[], int first, int last)
{
	int total_swaps = 0, mid = 0;
	if(first<last)
	{
		mid = (last+first)/2;
		total_swaps += mergeSortByOriginalGrade(lst, first, mid);
		total_swaps += mergeSortByOriginalGrade(lst, mid+1, last);
		total_swaps += mergeByOriginalGrade(lst, first, mid, last);
	}

	return total_swaps;
} /* merge sort by grade */

/***************************************************/

int mergeByAdjustedGrade(Student lst[], int firstA, int lastA, int lastB)
{
	int total_swaps = 0;
	int i = 0, j = 0, k = 0;
	int sizeA = lastA-firstA+1;
	int sizeB = lastB-lastA;
	Student lstA[sizeA], lstB[sizeB];
	for(i = 0; i < sizeA; i++)
	{
		lstA[i] = lst[firstA+i];
	}
	for(j = 0; j < sizeB; j++)
	{
		lstB[j] = lst[lastA+j+1];
	}
	i = 0, j = 0;

	for(k = firstA; i < sizeA && j < sizeB; k++)
	{
		if(lstA[i].calculateAdjustedGrade() > lstB[j].calculateAdjustedGrade())
		{
			lst[k] = lstA[i++];
			total_swaps++;
		}
		else
		{
			lst[k] = lstB[j++];
			total_swaps++;
		}
	}

	while(i < sizeA)
	{
		lst[k++] = lstA[i++];
	}
	while(j < sizeB)
	{
		lst[k++] = lstB[j++];
	}

	return total_swaps;
} /* merge by grade */

/***************************************************/

int mergeSortByAdjustedGrade(Student lst[], int first, int last)
{
	int total_swaps = 0, mid = 0;
	if(first<last)
	{
		mid = (last+first)/2;
		total_swaps += mergeSortByAdjustedGrade(lst, first, mid);
		total_swaps += mergeSortByAdjustedGrade(lst, mid+1, last);
		total_swaps += mergeByAdjustedGrade(lst, first, mid, last);
	}

	return total_swaps;
} /* merge sort by grade */

/***************************************************/
/***************************************************/
