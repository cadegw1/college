/*
        Author: W. Douglas Lafield
        main.cpp
*/
#include <iostream>
#include <fstream>
#include "VBI.h"
#include "Stack.h"

#define BUFFER_LENGTH 100
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

using namespace std;

/***************************************************/

/* prototypes */
VBI expon(VBI b, VBI e);
VBI intRoot(VBI n);
bool isOperator(string s);
int letterToNum(string letter);
char numToLetter(int num);
int precedence(string oper);

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
	
	/* read file */
	ifstream f;
	f.open(argv[1]);
	if(!f)
	{
		cout << "File " << argv[1] << " does not exist." << endl;
		return 0;
	}
	
	int numOfLines;
	
	f >> numOfLines;
	
	VBI letters[26];
	for(int i = 0; i < 26; i++)
		letters[i] = VBI(0);
		
	for(int lineNum = 0; lineNum < numOfLines; lineNum++)
	{ /* for each line in the file */
		
		string command, letter;
		
		f >> command >> letter;
		
		if(command == "print")
		{ /* if command is print */
			
			cout << letter << " = " << letters[letterToNum(letter)].toString() << endl;

		} /* if command is print */
		
		if(command == "root")
		{ /* if command is root */
			
			if(letters[letterToNum(letter)] < VBI(0))
				cout << "Sqrt(" << letters[letterToNum(letter)].toString() << ") is undefined" << endl;
			else
			{
				VBI tempRoot = intRoot(letters[letterToNum(letter)]);
				cout << "Sqrt(" << letters[letterToNum(letter)].toString() << ") = " << tempRoot.toString() << endl;
			}
			
		} /* if command is root */
		
		if(command == "let")
		{ /* if command is let */
			
			string equalSign;
			string valueString;
			
			f >> equalSign >> valueString;
			
			letters[letterToNum(letter)] = VBI(valueString);
			
		} /* if command is let */
		
		if(command == "compare")
		{ /* if command is print */
			
			string compareSign;
			string secondLetter;
			bool compareIsTrue;
			
			f >> compareSign >> secondLetter;
			
			if(compareSign == "=")
				compareIsTrue = letters[letterToNum(letter)] == letters[letterToNum(secondLetter)];
			if(compareSign == "<")
				compareIsTrue = letters[letterToNum(letter)] < letters[letterToNum(secondLetter)];
			if(compareSign == ">")
				compareIsTrue = letters[letterToNum(letter)] > letters[letterToNum(secondLetter)];
			
			cout << (compareIsTrue ? "Yes" : "No") << endl;
			
		} /* if command is print */
		
		if(command == "calc")
		{ /* if command is calc */
			
			string equalSign;
			
			/** convert to postfix */
			Stack<string> *opStack = new Stack<string>();
			
			string token;
			f >> equalSign >> token;
			string buffer[BUFFER_LENGTH];
			int bufferLength = 0;
			
			while(token != ";")
			{ /* for each token */
				
				/* if token is ( */
				if(token == "(")
				
					/* push token on stack */
					opStack->push(token);
					
				else if(token == ")")
				{ /* else if token is ) */
					
					/* while top is not ( */
					while(opStack->top() != "(")
					
						/* pop from stack and add to buffer */
						buffer[bufferLength++] = opStack->pop();
						
					/* pop ( from stack */
					opStack->pop();
					
				} /* else if token is ) */
				
				else if(isOperator(token))
				{ /* else if token is an operator x */
					
					if(opStack->getLength() > 0)
					{ /* if there's anything on the stack */
						
						string y = opStack->top();
						while(opStack->getLength() > 0 && isOperator(y) && precedence(y) >= precedence(token))
						{/* while there is an operator y at the top of the 
						 * stack and its precedence <= x's precedence */
						 
							/* pop y and add to buffer */
							buffer[bufferLength++] = opStack->pop();
							
							if(opStack->getLength() > 0)
								y = opStack->top();
							
						} /* while there is an operator y at the top of the 
						 * stack and its precedence <= x's precedence */
					
					} /* if there's anything on the stack */
					
					/* push x onto the stack */
					opStack->push(token);
					
				} /* else if token is an operator x */
				
				else
				{ /* else, add token to buffer */
					
					buffer[bufferLength++] = token;
					
				} /* else, add token to buffer */
				
				f >> token;
				
			} /* for each token */

			/* while stack is not empty, pop and add to buffer */
			while(opStack->getLength() > 0)
				buffer[bufferLength++] = opStack->pop();
				
			/** interpret postfix */
			Stack<VBI*> *valStack = new Stack<VBI*>();

			for(int buffIndex = 0; buffIndex < bufferLength; buffIndex++)
			{ /* for each token in buffer */
				
				token = buffer[buffIndex];
				
				if(isOperator(token))
				{ /* if token is an operator */
					
					VBI *operand1, *operand2;
					
					/* pop stack into operand1 */
					operand2 = valStack->pop();
					
					/* pop stack into operand2 */
					operand1 = valStack->pop();
					
					/* evaluate operand1 token operand2 */
					VBI result;
					if(token == "+")
						result = *operand1 + *operand2;
					else if(token == "-")
						result = *operand1 - *operand2;
					else if(token == "*")
						result = *operand1 * *operand2;
					else if(token == "/")
						result = *operand1 / *operand2;
					else if(token == "%")
						result = *operand1 % *operand2;
					else if(token == "^")
						result = expon(*operand1, *operand2);
					else
						cout << "ERROR!!!" << endl;
					
					/* push result to stack */
					VBI *newValue = new VBI(result);
					valStack->push(newValue);

				} /* if token is an operator */
				
				else
				{ /* else (token is operand) */
					
					VBI *newValue = new VBI(letters[letterToNum(token)]);
					valStack->push(newValue);
				} /* else (token is operand) */
					
			} /* for each token in buffer */
					
			/* pop stack to letters[letterToNum(letter)] */		
			letters[letterToNum(letter)] = *(valStack->pop());
			
		} /* if command is calc */
		
	} /* for each line in the file */
	
	f.close();
	
	cout << "Done." << endl;
	
	return 0;
} /* main */

/***************************************************/

char numToLetter(int num)
{
	return 'A' + num;
} /* num to letter */

/***************************************************/

int letterToNum(string letter)
{
	return letter[0] - 'A';
} /* letter to num */

/***************************************************/

int precedence(string oper)
{
	if(oper[0] == '+' || oper[0] == '-')
		return 2;
	if(oper[0] == '*' || oper[0] == '/' || oper[0] == '%')
		return 3;
	if(oper[0] == '^')
		return 4;
	cout << "ERROR" << endl;
	return -1;
	
} /* precedence */

/***************************************************/

VBI expon(VBI b, VBI e)
{
	if(e < VBI(0))
		return VBI(0);
	if(e == VBI(0))
		return VBI(1);
	if(e == VBI(1))
		return b;
	if(e % VBI(2) == VBI(1))
		return b * expon(b, e - VBI(1));
	return expon(b * b, e / VBI(2));
} /* exponent */

/***************************************************/

bool isOperator(string s)
{
	return (s == "+" || s == "-" || s == "*" || s == "/" || s == "%" || s == "^");
} /* is operator */

/***************************************************/

VBI intRoot(VBI n)
{
	if(n == VBI(0) || n == VBI(1))
		return n;
		
	VBI estimate = VBI(1);
	VBI estimate2 = VBI(1);
	while(estimate2 < n)
	{ /* while estimate squared is less than n, double estimate */
		
		estimate.doubleVBI();
		estimate2.doubleVBI();
		estimate2.doubleVBI();
		
	} /* while estimate squared is less than n, double estimate */
	
	/* apply newton's method */
	VBI diff = (estimate * estimate - n) / (VBI(2) * estimate);
	while(diff > VBI(0))
	{
		estimate = estimate - diff;
		diff = (estimate * estimate - n) / (VBI(2) * estimate);
	}
	
	/* decrease until guess^2 <= n */
	while(estimate * estimate > n)
		estimate--;

	/* increase until (guess + 1)^2 >= n */
	while((estimate + VBI(1)) * (estimate + VBI(1)) < n)
		estimate++;
		
	return estimate;
} /* int root */

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
