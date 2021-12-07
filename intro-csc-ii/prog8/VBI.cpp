// Author: Armando Castillo

#include <string>
#include <iostream>
#include <cstdio>
#include <cmath>

#include "VBI.h"

using namespace std;

/***************************************************/

VBI::VBI()
{
	digits = "0";
	isNeg = false;
}

/***************************************************/

VBI::VBI(int x)
{
	isNeg = x < 0;
	digits = to_string(x * (isNeg ? -1 : 1));
}

/***************************************************/
	
VBI::VBI(long long int x)
{
	isNeg = x < 0;
	digits = to_string(x * (isNeg ? -1 : 1));
}

/***************************************************/
	
VBI::VBI(unsigned long long int x)
{
	isNeg = false;
	digits = to_string(x * (isNeg ? -1 : 1));
}

/***************************************************/
	
VBI::VBI(string x)
{
	/* if string x has values that are not numeric, return prefix */
	int index = 0;
	if(x[index] == '-')
	{
		index++;
		isNeg = true;
	}
	else
		isNeg = false;
		
	digits = "";
	while(index < x.length())
	{
		if(x[index] < '0' || x[index] > '9')
			break;
		digits += x[index];
		index++;
	}
	if(digits == "")
	{
		isNeg = false;
		digits = "0";
	}
}

/***************************************************/
	
VBI::VBI(const VBI &x)
{
	isNeg = x.getIsNeg();
	digits = x.getDigits();
}

/***************************************************/
	
VBI::~VBI(){}
	
/***************************************************/

string VBI::toString(void) const
{
	return (isNeg ? "-" : "") + digits;
}

/***************************************************/

bool VBI::operator> (const VBI& rhs) const
{	
	/** Suggested algorithm: */
	/* check signs */	
	/* check lengths of digit strings */
	/* check digits individually until there is a difference */

	// cout<<this->getDigits()<<" "<<this->getIsNeg()<<" "<<rhs.getDigits()<<" "<<rhs.getIsNeg()<<endl;

	if((!this->getIsNeg() && !rhs.getIsNeg()) || (this->getIsNeg() && rhs.getIsNeg()))	// both negative or positive
	{	
		if(this->getIsNeg() && this->getDigits().length() < rhs.getDigits().length())
			return true;
		if(this->getIsNeg() && this->getDigits().length() > rhs.getDigits().length())
			return false;
		else if(!this->getIsNeg() && this->getDigits().length() > rhs.getDigits().length())
			return true;
		else if(!this->getIsNeg() && this->getDigits().length() < rhs.getDigits().length())
			return false;
		if(!this->getIsNeg())
		{
			for(int index = 0; index < this->getDigits().length(); index++)
			{
				if((int)this->getDigits()[index] > (int)rhs.getDigits()[index])
					return true;
				else if((int)this->getDigits()[index] < (int)rhs.getDigits()[index])
					return false;
				else
					continue;
			}
		}
		else
		{
			for(int index = 0; index < this->getDigits().length(); index++)
			{
				if((int)this->getDigits()[index] > (int)rhs.getDigits()[index])
					return false;
				else if((int)this->getDigits()[index] < (int)rhs.getDigits()[index])
					return true;
				else
					continue;
			}
		}		
	}	
	else
	{
		if(this->getIsNeg())
			return true;
		else
			return false;
	}
} /* greater than */

/***************************************************/

bool VBI::operator< (const VBI& rhs) const
{	
	return rhs > *this;
} /* less than */

/***************************************************/

bool VBI::operator>= (const VBI& rhs) const
{
	return (*this > rhs) || (*this == rhs);
} /* greater than or equal to */

/***************************************************/

bool VBI::operator<= (const VBI& rhs) const
{	
	return (*this < rhs) || (*this == rhs);
} /* less than or equal to */

/***************************************************/

bool VBI::operator== (const VBI& rhs) const
{	
	return !(rhs > *this) && !(rhs < *this);
} /* equal to */

/***************************************************/

bool VBI::operator!= (const VBI& rhs) const
{	
	return !(*this == rhs);	
} /* not equal */

/***************************************************/

VBI absoluteAdd(VBI a, VBI b)
{
	/* This function is optional.
	 * 
	 * Add the absolute values of a and b together
	 * and return the results.  Ignore isNeg for both
	 * a and b, and return a positive value.
	 * The function may be useful in operator+ and/or operator- */
	string absoluteSum = "";
	int i = a.getDigits().length() - 1;
	int j = b.getDigits().length() - 1;
	int carry = 0;
	int sumOfChar = 0;
	while(i > -1 || j > -1)
	{	
		sumOfChar = (i != -1 ? a.getDigits()[i] : 0) + (j != -1 ? b.getDigits()[j] : 0) - (((i != -1 && j != -1) ? 2 : 1) * '0'); 
		absoluteSum.append(1, char(((sumOfChar + carry) % 10) + '0'));
		if(sumOfChar >= 10)
			carry = sumOfChar / 10;
		if(i != -1)
			i--;
		if(j != -1)
			j--;
	}
	long long int x = absoluteSum.length();
	for(long long int index = 0; index < x / 2; index++)	// loop to reverse the string
	{
		swap(absoluteSum[index], absoluteSum[x - index - 1]);
	}
	VBI * result = new VBI(absoluteSum);
	return *result;
} /* absolute add */

/***************************************************/

VBI absoluteSub(VBI a, VBI b)
{
	/* This function is optional.
	 * 
	 * Calculate the difference between a and b.  Ignore isNeg for both
	 * a and b, and return a positive value.
	 * The function may be useful in operator+ and/or operator- */
	 
	 /* your code goes here if you choose to write this function. */

	 // Didn't have the time to figure it out
	string A = "";
	string B = "";
	a.setIsNeg(false);
	b.setIsNeg(false);
	if(a > b)
	{
		A = a.getDigits();
		B = b.getDigits();
	}
	else
	{
		A = b.getDigits();
		B = a.getDigits();
	}
	string absoluteSum = "";
	int i = A.length() - 1;
	int j = B.length() - 1;
	int flag = 0;
	int carry = 0;
	int sumOfChar = 0;
	while (i > -1 || j > -1)
	{
		carry = 0;
		if(i == 0)
			NULL;
		else if(A[i] == '0' && i != 0)
		{
			int index = i;
			while(A[index]=='0')
			{
				A.replace(index--, 1, "9");
			}
			char x = A[index];
			x--;
			string replacement = string(&x);
			A.replace(index, 1, replacement);
		}

		if(flag == 1)
		{
			NULL;
		}
		else if (A[i]-B[j] < 0)
		{
			carry += 10;
			flag = 1;
		}
		sumOfChar = (i != -1 ? A[i] + carry - '0': 0) - (j != -1 ? B[j] - '0' : 0);
		absoluteSum.append(1, char(sumOfChar + '0'));
		if (i != -1)
			i--;
		if (j != -1)
			j--;
	}
	long long int x = absoluteSum.length();
	for (long long int index = 0; index < x / 2; index++)	// loop to reverse the string
	{
		swap(absoluteSum[index], absoluteSum[x - index - 1]);
	}
	while (absoluteSum[0] == '0')
	{
		absoluteSum.erase(0, 1);
	}
	VBI* result = new VBI(absoluteSum);
	return *result;
} /* absolute sub */

/***************************************************/

VBI VBI::operator+ (const VBI& rhs) const
{
	/** Suggested algorithm: */
	/* if isNeg is the same for *this and rhs, 
	 * 		run absoluteAdd
	 * otherwise,
	 * 		run absoluteSub
	 * */
	VBI absoluteSum;
	if((this->isNeg && rhs.getIsNeg()) || (!this->isNeg && !rhs.getIsNeg()))
	{
		absoluteSum = absoluteAdd(*this, rhs);
		if(absoluteSum.getDigits() == "0")
			return absoluteSum;
		else if(this->isNeg)
			absoluteSum.setIsNeg(true);
		return absoluteSum;
	}
	else
	{
		absoluteSum = absoluteSub(*this, rhs);
		VBI tempThis = VBI(this->getDigits());
		VBI tempRhs = VBI(rhs.getDigits());
		if(absoluteSum.getDigits() == "0")
			return absoluteSum;
		if(tempThis > tempRhs && this->getIsNeg())
			absoluteSum.setIsNeg(true);
		else if(tempThis < tempRhs && rhs.getIsNeg())
			absoluteSum.setIsNeg(true);
		return absoluteSum;
	}
} /* plus */

/***************************************************/

VBI VBI::operator- (const VBI& rhs) const
{
	/** Suggested algorithm: */
	/* Create alternativeRhs which is -rhs
	 * return (*this) + alternativeRhs
	 * */
	VBI * alternativeRhs = new VBI(rhs.getDigits());
	alternativeRhs->setIsNeg(!rhs.getIsNeg());
	return (*this) + *alternativeRhs;
} /* minus */

/***************************************************/

void VBI::doubleVBI()
{
	/* This function is optional.
	 * 
	 * Double the value of *this.
	 * The function may be useful in operator* and/or operator/
	 * */
	VBI temp = absoluteAdd(*this, *this);
	this->digits = temp.getDigits();
} /* double */
	
/***************************************************/

void VBI::halfVBI()
{
	/* This function is optional.
	 * 
	 * Cut the value of *this in half, rounding down to
	 * the nearest whole number if *this is odd.
	 * The function may be useful in operator* and/or operator/
	 * */
	 
	/* Your code goes here */
	VBI counter = VBI(0);
	VBI Two = VBI(2);
	VBI One = VBI(1);
	VBI Temp = VBI(*this);
	while (true)
	{

		if (Temp < Two)
		{
			break;
		}
		counter = absoluteAdd(counter, One);
		Temp = Temp - Two;
	}
	this->digits = counter.getDigits();

} /* half */

/***************************************************/

VBI VBI::operator* (const VBI& rhs) const
{
	/** Suggested algorithm: */
	/* if either is zero, then return zero */
	/* if either is 1, then return the other value */
	/* retVal = absolute value of this */
	/* r = absolute value of rhs */
	/* while r > 1 */
		/* if r is even */
			/* halve r */
			/* double retVal */
		/* else */
			/* return retVal + retVal * (r-1) */
	/* set retVal.isNeg */
	/* return retVal */
	VBI Zero = VBI(0);
	VBI One = VBI(1);
	VBI Two = VBI(2);
	if (rhs.getDigits() == "0" || this->digits == "0")
			return Zero;
	else if (this->digits == "1")
		return rhs;
	else if (rhs.getDigits() == "1") 
		return *this;
	VBI retVal = VBI(this->getDigits());
	VBI r = VBI(rhs.getDigits());
	while (r > One)
	{
		if (r % Two == Zero)
		{
			r.halfVBI();
			retVal.doubleVBI();
		}
		else
		{
			return retVal + retVal * (r - One);
		}
	}
	if (!this->isNeg)
	{
		if (rhs.getIsNeg())
			retVal.toggleIsNeg();
	}
	else if (this->isNeg)
	{
		if (!rhs.getIsNeg())
			retVal.toggleIsNeg();
	}
	return retVal;
} /* multiply */

/***************************************************/

VBI VBI::operator/ (const VBI& rhs) const
{
	/** Suggested algorithm: */
	/* set absLeft and absRight to the absolute values of *this and rhs respectively */
	/* if absLeft < absRight, then return zero */
	/* calculate return value's isNeg */
	/* if absLeft == absRight, return 1 or -1 depending on return value's isNeg */
	/* while absRight is even */
		/* cut absRight and absLeft each in half */
	/* use binary search between 1 and absLeft to find a value such that
	 * 		absRight * retVal >= absLeft and absRight * (retVal - 1) < absLeft */
	/* set retVal's isNeg */
	/* return retVal */
	
	/* Your code goes here */
	VBI One = VBI(1);
	VBI Zero = VBI(0);
	VBI Two = VBI(2);
	VBI absLeft = VBI(this->getDigits());
	VBI absRight = VBI(rhs.getDigits());
	VBI retVal = VBI(this->getDigits());
	if (absLeft < absRight)
		return Zero;
	else if (absLeft == absRight)
	{
		if (!this->isNeg)
		{
			if (rhs.getIsNeg())
				One.toggleIsNeg();
		}
		else if (this->isNeg)
		{
			if (!rhs.getIsNeg())
				One.toggleIsNeg();
		}
		return One;
	}
	while (absRight % Two == Zero)
	{
		absRight.halfVBI();
		absLeft.halfVBI();
	}

} /* divide */

/***************************************************/

VBI VBI::operator% (const VBI& rhs) const
{
	/* I've just decided to write this function for you.
	 * You're welcome. */
	return *this - (*this / rhs) * rhs;
} /* mod */

/***************************************************/

VBI VBI::operator= (const VBI& rhs)
{
	/* This one, too. */
	this->digits = rhs.getDigits();
	this->isNeg = rhs.getIsNeg();
	return *this;
} /* assignment */
	
/***************************************************/

VBI VBI::operator++ (void) /* prefix ++ operator */
{
	/* Your code goes here */
	string temp = this->getDigits();
	temp[temp.length()-1] = char(temp[temp.length()-1]+'1'-'0');
	this->digits = VBI(temp).getDigits();
	return *this;
} /* increment */

/***************************************************/

VBI VBI::operator-- (void) /* prefix -- operator */
{
	/* Your code goes here */
	string temp = this->getDigits();
	temp[temp.length()-1] = char(temp[temp.length()-1]-'1'+'0');
	this->digits = VBI(temp).getDigits();
	return *this;
} /* decrement */

/***************************************************/

VBI VBI::operator++ (int) /* postfix ++ operator */
{
	/* Your code goes here */
	string temp = this->getDigits();
	temp[temp.length()-1] = char(temp[temp.length()-1]+'1'-'0');
	this->digits = VBI(temp).getDigits();
	return *this;
} /* increment */

/***************************************************/

VBI VBI::operator-- (int) /* postfix -- operator */
{
	/* Your code goes here */
	string temp = this->getDigits();
	temp[temp.length()-1] = char(temp[temp.length()-1]-'1'+'0');
	this->digits = VBI(temp).getDigits();
	return *this;
} /* decrement */

/***************************************************/
/***************************************************/
/***************************************************/
