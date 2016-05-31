/*
 * Shawn Stern, #0921475
 *
 * Implementation of rational number type
 * CSE 374 HW7, Winter 2013
 */

#include "rational.h"
// cmath included to enable the abs() function 
// so we can find gcd of negatives
#include <cmath>
using namespace std;

// Helper function prototype
int gcd(int a, int b);


// Construct Rational 0/1
Rational::Rational() {
	num = 0;
	denom = 1;
}

// Construct Rational n/1
Rational::Rational(int n) {
	num = n;
	denom = 1;
}

// Construct Rational n/d
Rational::Rational(int n, int d) {
	num = n;
	denom = d;
}

// Return numerator in lowest terms.
// Negate as necessary to keep negative signs away from denominator.
int Rational::n() {
	if (denom == 0) {
		return num;
	} else if (denom < 0){
		return -1 * (num / gcd(num, denom));
	} else {
		return num / gcd(num, denom);
	}
}

// Return denominator in lowest terms, never allowed to be displayed
// as negative.
int Rational::d() {
	if (denom == 0) {
		return denom;
	} else if (denom < 0) {
		return -1 * (denom / gcd(num, denom));
	} else {
		return denom / gcd(num, denom);
	}
}

// = this + other
Rational Rational::plus(Rational other) {
	int new_num = (num * other.denom) + (denom * other.num);
	int new_denom = denom * other.denom;
		
	return Rational(new_num, new_denom);
}

// = this - other
Rational Rational::minus(Rational other) {
	int new_num = (num * other.denom) - (denom * other.num);
	int new_denom = denom * other.denom;
	
	return Rational(new_num, new_denom);
}

// = this * other
Rational Rational::times(Rational other) {
	int new_num = num * other.num;
	int new_denom = denom * other.denom;	
	
	return Rational(new_num, new_denom);
}

// = this / other
Rational Rational::div(Rational other) {
	int new_num = num * other.denom;
	int new_denom = denom * other.num;
	
	return Rational(new_num, new_denom);
}

// Find greatest common denominator between inputs a and b
// Source: http://en.wikipedia.org/wiki/Euclidean_algorithm#Implementations
// Modified to deal with negative values.
int gcd(int a, int b) {
	if (b==0) {
		return a;
	} else {
		return gcd((int)abs(b), (int)abs(a) % (int)abs(b));
	}
}
