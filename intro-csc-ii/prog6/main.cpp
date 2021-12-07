/*
        Author: W. Douglas Lafield
        main.cpp
*/
#include <iostream>
#include <fstream>
#include "Customer.h"
#include "Queue.h"
#include "OrderedList.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

using namespace std;

/***************************************************/

/* prototypes */
bool allTellersAreIdle(bool idles[], int length);
int compareCustomers(Customer *a, Customer *b);

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
	
	Queue<Customer *> *q = new Queue<Customer *>();
	
	/* read file */
	ifstream f;
	ofstream log;
	f.open(argv[1]);
	if(!f)
	{
		cout << "File " << argv[1] << " does not exist." << endl;
		return 0;
	}
	
	int numOfTellers, numOfCustomers, time, id, enterTime, dur;
	
	f >> numOfTellers >> numOfCustomers;
	Customer tellers[numOfTellers];
	bool tellerIsIdle[numOfTellers];
	int tellerRemainTime[numOfTellers];
	time = 0;
	
	for(int x = 0; x < numOfTellers; x++)
		tellerIsIdle[x] = true;
		
	OrderedList<Customer *> *customerList = new OrderedList<Customer *>(compareCustomers);
	
	cout << "loading customers to list..." << endl;
	for(int x = 0; x < numOfCustomers; x++)
	{ /* get all the customers into the list of customers */
		
		f >> id >> enterTime >> dur;
		Customer *nextCustomer = new Customer(id, enterTime, dur);
		customerList->insert(nextCustomer);
		
	} /* get all the customers into the list of customers */
	
	cout << "Customers loaded." << endl;
	f.close();
		
	int customerIndex = 0;
	Customer *nextCustomer = customerList->getNode(customerIndex);
	bool unenteredCustomersExist = true;
	cout << "While there are unrequested customers..." << endl;
	
	log.open("log.txt");
	
	int tellerIdleTime = 0;
	int totalWaitingTime = 0;
	
	while(customerIndex < customerList->getLength() || q->getLength() != 0 || !allTellersAreIdle(tellerIsIdle, numOfTellers))
	{ /* while there is at least 1 unsatisfied customer */

		/* for each new customer, enqueue the customer */
		while(unenteredCustomersExist && time >= nextCustomer->getEnteringTime())
		{
			log << "Customer " << nextCustomer->getId() << " entered the bank at time " << time << endl;
			q->enqueue(nextCustomer);
			customerIndex++;
			if(customerIndex < customerList->getLength())
				nextCustomer = customerList->getNode(customerIndex);
			else
				unenteredCustomersExist = false;			
		}

		for(int x = 0; x < numOfTellers; x++)
		{ /* for each teller */
			
			if(!tellerIsIdle[x])
			{ /* if teller is not idle (teller is serving a customer) */
				
				/* decrement remaining time */
				tellerRemainTime[x]--;
				
				if(tellerRemainTime[x] == 0)
				{ /* if out of time, make idle */
					
					tellerIsIdle[x] = true;
					log << "Customer " << tellers[x].getId() << " finished with teller" << x << " at time " << time << endl;
					
				} /* if out of time, make idle */
				
			}  /* if teller is not idle */
			
			if(tellerIsIdle[x])
			{ /* if teller is idle    (not else of previous if statement) */
				
				if(q->getLength() != 0)
				{ /* if q is not empty */
					
					/* assign new customer to teller */
					Customer *newActiveCustomer = *(q->front());
					q->dequeue();
					
					newActiveCustomer->setStartTime(time);
					totalWaitingTime += newActiveCustomer->calculateWaitingTime();
					log << "Customer " << newActiveCustomer->getId() << " began with teller" << x << " at time " << time << " after a wait of " << newActiveCustomer->calculateWaitingTime() << endl;
					tellers[x] = *newActiveCustomer;
					
					/* make teller not idle */
					tellerIsIdle[x] = false;
					tellerRemainTime[x] = newActiveCustomer->getDuration();
					
				} /* if q is not empty */
				else /* else (q is empty), increment teller idle time */
					tellerIdleTime++;
				
			} /* if teller is idle    (not else of previous if statement) */
			
		} /* for each teller */
		
		/* clock tick */
		time++;
		
	} /* while there are unrequested customers */
	
	log << endl << "Total customer waiting time = " << totalWaitingTime << endl;
	log << "Average customer waiting time = " << 1.0 * totalWaitingTime / numOfCustomers << endl;
	log << "Total teller idle time = " << tellerIdleTime << endl;
	log << "Average idle time per teller = " << 1.0 * tellerIdleTime / numOfTellers << endl;	
	
	log.close();
	
	cout << "Done." << endl;
	
	delete q;
	
	return 0;
} /* main */

/***************************************************/

int compareCustomers(Customer *a, Customer *b)
{
	if(a->getId() < b->getId())
		return -1;
	if(a->getId() > b->getId())
		return 1;
	return 0;	
} /* compare customers */

/***************************************************/

bool allTellersAreIdle(bool idles[], int length)
{
	for(int i = 0; i < length; i++)
		if(!idles[i])
			return false;
	return true;
} /* all tellers are idle */

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
