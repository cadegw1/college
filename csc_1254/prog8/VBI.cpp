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
	
	/* your code goes here */
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
	 
	 /* your code goes here if you choose to write this function. */
	
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
	 
	 
	/* Your code goes here */
	
} /* plus */

/***************************************************/

VBI VBI::operator- (const VBI& rhs) const
{
	/** Suggested algorithm: */
	/* Create alternativeRhs which is -rhs
	 * return (*this) + alternativeRhs
	 * */
	 
	/* Your code goes here */

} /* minus */

/***************************************************/

void VBI::doubleVBI()
{
	/* This function is optional.
	 * 
	 * Double the value of *this.
	 * The function may be useful in operator* and/or operator/
	 * */
	
	/* Your code goes here */

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

	/* Your code goes here */
	
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
	
} /* increment */

/***************************************************/

VBI VBI::operator-- (void) /* prefix -- operator */
{
	/* Your code goes here */
	
} /* decrement */

/***************************************************/

VBI VBI::operator++ (int) /* postfix ++ operator */
{
	/* Your code goes here */

} /* increment */

/***************************************************/

VBI VBI::operator-- (int) /* postfix -- operator */
{
	/* Your code goes here */
	
} /* decrement */

/***************************************************/
/***************************************************/
/***************************************************/
