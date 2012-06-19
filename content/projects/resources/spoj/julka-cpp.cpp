//======================================================================
/* BigInt.h
 *
 * 07/13/10
 *
 * Zeb Fross
 *
 * Defines an arbitrary precision integer datatype that can be treated
 * almost identically to other built-in numeric types.
 */
//======================================================================

#include <iostream>
using std::ostream;
using std::istream;
using std::cout;
using std::cin;

#include <string>
using std::string;

#include <list>
using std::list;

#include <math.h>

typedef unsigned long	ulong;
typedef unsigned short	ushort;
typedef unsigned int	uint;

typedef list<ushort>::iterator IT;
typedef list<ushort>::const_iterator IT_c;

class BigInt
{
private:
	list< ushort > digits;

	// disable default constructor. Why? Do ints have
	// default constructors?
	BigInt( void );
public:
	explicit BigInt( const ulong );
	// pre: string must contain only numbers
	// pst: a BigInt is created from the digits in the string
	explicit BigInt( const string & );
			 BigInt( const BigInt & );
			 BigInt( IT_c, IT_c );

	BigInt & operator=( const BigInt & );

	// define logical operators for BigInt
	bool operator==( const BigInt & ) const;
	bool operator!=( const BigInt & ) const;
	bool operator<=( const BigInt & ) const;
	bool operator <( const BigInt & ) const;
	bool operator>=( const BigInt & ) const;
	bool operator >( const BigInt & ) const;

	// unary function to compute factorial of this BigInt
	const BigInt operator!( void ) const;
	// unary prefix increment
	BigInt & operator++();
	// unary postfix increment
	const BigInt operator++( int );
	// unary prefix decrement
	BigInt & operator--();
	// unary postfix decrement
	const BigInt operator--( int );

	// define simple arithmetic operators for BigInt
	const BigInt operator+( const BigInt & ) const;
	const BigInt operator-( const BigInt & ) const;
	const BigInt operator*( const BigInt & ) const;
	// throws a div_by_zero error if the parameter passed is
	// equal to zero
	const BigInt operator/( const BigInt & ) const;

	BigInt & operator+=( const BigInt & );
	BigInt & operator-=( const BigInt & );
	BigInt & operator*=( const BigInt & );
	// throws a divide by zero error if the parameter passed is
	// equal to zero
	BigInt & operator/=( const BigInt & );

	// conversion functions
	// throws an int_too_big error if the BigInt cannot fit
	// inside an unsigned long
	ulong toUlong() const;

	// output BigInt to ostream
	friend ostream & operator<<( ostream &, const BigInt &);
	// convert a string read from an istream to a BigInt
	friend istream & operator>>( istream &, BigInt &);

private:
	// returns: -1 if this is less than the parameter
	//			 0 if this is equal to the parameter
	//			 1 if this is greater than the parameter
	const int comp( const BigInt & ) const;
	
	// a slow but necessary implementation of slow divide
	// pre: parameter should not be zero
	BigInt & slow_divide( const BigInt & );

	// removes all trailing zeroes from the digits list
	void trim_zeroes();
};

//======================================================================
/* BigInt.cpp
 *
 * 07/13/10
 *
 * Zeb Fross
 *
 * Defines an arbitrary precision integer datatype that can be treated
 * almost identically to other built-in numeric types.
 */
//======================================================================

BigInt::BigInt( void ) {	}

BigInt::BigInt( const ulong num ) {
	ulong n = num;
	while (n > 0) {
		digits.push_back(n % 10);
		n /= 10;
	}
}

BigInt::BigInt( const string & str ) {
	for (uint i(str.length()); i > 0; --i) {
		digits.push_back(str[i-1]-48);
	}
	IT ind(digits.end());
	// there may be trailing zeros that we need to erase
	while (ind != digits.begin() && *--ind == 0) {	}
	digits.erase(++ind, digits.end());
}

BigInt::BigInt( const BigInt & right ) {
	for (IT_c i(right.digits.begin()); i != right.digits.end(); ++i) {
		digits.push_back(*i);
	}
}

BigInt::BigInt( IT_c start, IT_c end ) : digits(start, end) {	}

BigInt & BigInt::operator=( const BigInt & right ) {
	if (this != &right) {
		digits.clear();
		for (IT_c i(right.digits.begin()); i != right.digits.end(); ++i) {
			digits.push_back(*i);
		}
	}
	return *this;
}

bool BigInt::operator==( const BigInt & right ) const {
	return (this->comp(right) == 0);
}

bool BigInt::operator<=( const BigInt & right ) const {
	return (this->comp(right) != 1);
}

bool BigInt::operator!=( const BigInt & right ) const {
	return (this->comp(right) != 0);
}

bool BigInt::operator <( const BigInt & right ) const {
	return (this->comp(right) == -1);
}

bool BigInt::operator>=( const BigInt & right ) const {
	return (this->comp(right) != -1);
}

bool BigInt::operator >( const BigInt & right ) const {
	return (this->comp(right) == 1);
}

const int BigInt::comp( const BigInt & right ) const {
	if (this == &right) return 0;
	if (digits.size() < right.digits.size()) return -1;
	if (digits.size() > right.digits.size()) return 1;

	IT_c lft(digits.end()), rgt(right.digits.end());
	while (lft != digits.begin()) {
		if (*--lft < *--rgt) return -1;
		if (  *lft >   *rgt) return  1;
	}
	return 0;
}

const BigInt BigInt::operator!( void ) const {
	BigInt fact(0);
	if ( *this != fact ) {
		++fact; // fact = 1
		for (BigInt i(2); i <= *this; ++i) {
			fact *= i;
		}
	}
	return fact;
}

BigInt & BigInt::operator++() {
	return (*this += BigInt(1));
}

const BigInt BigInt::operator++( int ) {
	BigInt ret(*this);
	++*this;
	return ret;
}

BigInt & BigInt::operator--() {
	return (*this -= BigInt(1));
}

const BigInt BigInt::operator--( int ) {
	BigInt ret(*this);
	--*this;
	return ret;
}

const BigInt BigInt::operator+( const BigInt & right ) const {
	BigInt left(*this);
	left += right;
	return left;
}

const BigInt BigInt::operator-( const BigInt & right ) const {
	BigInt left(*this);
	left -= right;
	return left;
}

const BigInt BigInt::operator*( const BigInt & right ) const {
	BigInt left(*this);
	left *= right;
	return left;
}

const BigInt BigInt::operator/( const BigInt & right ) const {
	BigInt left(*this);
	left /= right;
	return left;
}

BigInt & BigInt::operator+=( const BigInt & right ) {
	ushort carry = 0;
	IT_c rgt(right.digits.begin());
	IT lft(digits.begin());
	for ( rgt; rgt != right.digits.end(); ++rgt ) {
		if (lft == digits.end()) {
			digits.push_back((*rgt+carry)%10);
			carry = ((*rgt+carry) > 9) ? 1 : 0;
			lft = digits.end();
		} else {
			uint c = ((*lft+*rgt+carry) > 9) ? 1 : 0;
			*lft = (*lft+*rgt+carry)%10;
			carry = c;
			++lft;
		}
	}
	while (lft != digits.end() && carry > 0) {
		uint c = ((*lft+carry) > 9) ? 1 : 0;
		*lft = (*lft+carry)%10;
		carry = c;
		++lft;
	}
	if (carry > 0) {
		digits.push_back(carry);
	}

	return *this;
}

BigInt & BigInt::operator-=( const BigInt & right ) {
	// TODO: remove this temp variable
	BigInt sub(right);
	while (sub.digits.size() < digits.size()) {
		sub.digits.push_back(0);
	}
	
	IT rgt(sub.digits.begin());
	IT lft(digits.begin());
	for (rgt; rgt != sub.digits.end(); ++rgt) {
		if (*rgt > *lft) {
		// handle carry
			*lft = (10-*rgt)+*lft;
			IT carry(++lft);
			while (carry != digits.end() && *carry == 0) {
				*carry = 9;
				++carry;
			}
			--(*carry);
		} else {
		// no need to carry - subtraction is easy
			*lft = *lft-*rgt;
			++lft;
		}
	}
	trim_zeroes();

	return *this;
}

BigInt & BigInt::operator*=( const BigInt & right ) {
	if (right == BigInt(0)) {
		*this = BigInt(0);
		return *this;
	}
	BigInt r = right;
	BigInt l = *this;
	for ( BigInt j(1); j < r; ++j ) {
		*this += l;
	}
	return *this;
}

BigInt & BigInt::operator/=( const BigInt & right ) {
	if (*this < right) {
		*this = BigInt(0);
		return *this;
	}
	if (*this - right < BigInt(5000)) return slow_divide(right);

	BigInt div1(0); // temp variables
	BigInt res(0);
	for (IT i(digits.end()); i != digits.begin(); i) {
		div1.digits.push_front(*--i);
		ulong tmp = (div1/right).toUlong();
		res.digits.push_front(tmp);
		div1 -= right*BigInt(tmp);
	}
	*this = res;
	trim_zeroes();
	return *this;
}

BigInt & BigInt::slow_divide( const BigInt & right ) {
	BigInt div(*this);
	*this = BigInt(0);
	while (div >= right) {
		div -= right;
		++(*this);
		if (*this > BigInt(999)) {
			int a = 3;
		}
	}
	return *this;
}

ulong BigInt::toUlong() const {
	// convert BigInt to ulong
	ulong res;
	if (digits.size() > 0) {
		IT_c ind(digits.end());
		res = *--ind;
		while (ind != digits.begin()) {
			res *= 10;
			res += *--ind;
		}
	} else {
		res = 0;
	}
	return res;
}

ostream & operator<<( ostream & out, const BigInt & big ) {
	if (big.digits.size() == 0) {
		out << '0';
		return out;
	}
	// the digits are stored backwards in the list
	IT_c i(big.digits.end());
	while (i != big.digits.begin()) {
		out << *--i;
	}
	return out; 
}

istream & operator>>( istream & in, BigInt & big ) {
	string str;
	in >> str;
	big = BigInt(str);

	return in;
}

void BigInt::trim_zeroes() {
	if (digits.size() == 0) return;
	IT z(digits.end());
	while (z != digits.begin() && *--z == 0) {	}
	if (*z == 0) {
		digits.erase(z, digits.end());
	} else {
		digits.erase(++z, digits.end());
	}
}

//======================================================================
/* driver.cpp
 *
 * 07/13/10
 *
 * Zeb Fross
 *
 * Driver program to test BigInt class.
 */
//======================================================================

int main( int iN, const char **ppchArgs )
{
	
	try {
		BigInt total(0), more(0), girl1(0), temp(0);
		for (uint i(0); i < 10; ++i) {
			cin >> total;
			cin >> more;

			temp = total - more;
			temp /= BigInt(2);

			girl1 = temp + more;
			cout << girl1 << "\n";
			cout << temp << "\n";
		}
	} catch (std::exception & e) {
		std::cerr << "ERROR!\n";
	}

	return 0;
}
