#include <iostream>
#include <fstream>
#include <string>
#include "Student.h"
#include "OrderedList.h"

using namespace std;

int main()
{
    OrderedList *l = new OrderedList;
    Student newItem = Student(string lastName, string firstName)
    l->insert(newItem);
    cout<<l->getSize()<<endl;

    return 0;
}