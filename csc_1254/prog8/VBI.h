#ifndef _VBI
#define _VBI 1

using namespace std;

#include <cstdlib>
#include <string>

class VBI
{

private:
	string digits;
	bool isNeg;

public:
	VBI();
	VBI(int x);
	VBI(long long int x);
	VBI(unsigned long long int x);
	VBI(string x);
	VBI(const VBI &x);
	~VBI();
	
	string getDigits() const { return digits; }
	bool getIsNeg() const { return isNeg; }
	
	void setIsNeg(bool x) { isNeg = x; }
	void toggleIsNeg() { isNeg = !(isNeg); }
	
	void doubleVBI();
	void halfVBI();
	
	//bool operator> (const VBI& lhs, const VBI& rhs);
	bool operator> (const VBI& rhs) const;
	bool operator< (const VBI& rhs) const;
	bool operator>= (const VBI& rhs) const;
	bool operator<= (const VBI& rhs) const;
	bool operator== (const VBI& rhs) const;
	bool operator!= (const VBI& rhs) const;
	
	VBI operator+ (const VBI& rhs) const;
	VBI operator- (const VBI& rhs) const;
	VBI operator* (const VBI& rhs) const;
	VBI operator/ (const VBI& rhs) const;
	VBI operator% (const VBI& rhs) const;
	
	VBI operator= (const VBI& rhs);
	VBI operator++ (void);
	VBI operator-- (void);
	VBI operator++ (int);
	VBI operator-- (int);
	
	string toString(void) const;
};

#endif
