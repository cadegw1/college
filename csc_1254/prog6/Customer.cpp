/*
        Author: W. Douglas Lafield
        Customer.cpp
*/

#include "Customer.h"

using namespace std;

/***************************************************/

Customer::Customer(int i, int e, int d)
{ 
	id = i;
	timeEnteringTheBank = e;
	durationOfTellerInteraction = d;
	timeTheTellerSeesTheCustomer = -1;
	
} /* constructer */

/***************************************************/

Customer::Customer(int i, int e, int d, int s)
{ 
	id = i;
	timeEnteringTheBank = e;
	durationOfTellerInteraction = d;
	timeTheTellerSeesTheCustomer = s;
	
} /* constructer */

/***************************************************/

Customer::Customer() 
{ 
	id = timeEnteringTheBank = durationOfTellerInteraction = timeTheTellerSeesTheCustomer = -1;	
} /* constructer -- generic */

/***************************************************/

Customer::~Customer(){}

int	Customer::getDuration() const { return durationOfTellerInteraction; }
int Customer::getId() const { return id; }
int Customer::getEnteringTime() const { return timeEnteringTheBank; }
int Customer::getStartTime() const { return timeTheTellerSeesTheCustomer; }

/***************************************************/

void Customer::setStartTime(int t) { timeTheTellerSeesTheCustomer = t; }

/***************************************************/

int Customer::calculateWaitingTime()
{
	return timeTheTellerSeesTheCustomer - timeEnteringTheBank;
} /* calculate waiting time */

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
/***************************************************/
/***************************************************/
/***************************************************/
/***************************************************/
