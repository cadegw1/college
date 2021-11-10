/*
	Author: W. Douglas Lafield
	Customer.h
*/
#ifndef _CUSTOMER_GUARD
#define _CUSTOMER_GUARD 1

//#include <iostream>

using namespace std;

class Customer
{
	private:
		int id;
		int timeEnteringTheBank;
		int timeTheTellerSeesTheCustomer;
		int durationOfTellerInteraction;
	public:
		/* constructers */
		Customer(int i, int e, int d);
		Customer(int i, int e, int d, int s);
		
		/* generic constructer */
		Customer();
		
		/* destructer */
		~Customer();

		int	getDuration() const;
		/* returns how long the customer interacts with the teller */
		
		int getId() const;
		/* returns the task's id */
		
		int	getEnteringTime() const;
		/* returns the time that the customer entered the bank */
		
		int	getStartTime() const;
		/* returns the time that the customer started interacting with the teller */
		
		void setStartTime(int t);
		/* set the time that the customer started interacting with the teller */
		
		int	calculateWaitingTime();
		/* calculates waiting time (after start time is set) */

};

#endif
