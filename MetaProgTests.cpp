// MetaProgTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <iostream>

template <int i> class A {
public:	
	enum p {a = A<i-1>::p::a};
	constexpr static inline const int test() {
		return 10;
	}
};

template <> class A<1> {
public:
	enum p { a = 13 };
};

// e(x) = 1 + x + x^2/2 + x^3/6
// e(x) = 1 + x * 1/1 * (1 + x * 1/2 * (1 + x * 1/3 * (1 + x))) )

double expRuntime(float x, int n, int k)
{
	if (k == 0) return 1;
	else return 1 + 1.0 / (n-k) * x * expRuntime(x, n, k-1);
}

template <int a, int b, int n, int k> class expSeries { //x = a/b
public:	
	static const int e = 
		1 + 1 / (n - k) * (float)a / b * expSeries<a, b, n, k - 1>::e;
};

template <int a, int b, int n> class expSeries<a,b,n,0> {
public:
	static const int e = 1;
};

/*
exp(x, 2, 1)
1 + 1 * x * exp(x, 2, 0) = 1 + 1 * x

exp(x, 3, 2)

1 + 1 * x * exp(x, 3, 1) = 1 + 1 * x * (1 + 1/2 * x * exp(x,3,0)) = 1 + 1 * x * (1 + 1/2 * x ) = 1 + x + x^2/2
*/

#ifndef LAST
#define LAST 10
#endif
int main()
{
	//std::cout<<expRuntime(5, 1000, 999)<< std::endl;
	
	const int a = 1;
	const int b = 1;
	const int n = 20;

	std::cout << expSeries<a, b, n, n-1>::e;

	return 0;

	//const int f = 5;
	//enum r {a1 = A<100>::test(), b1};
	//double b[r::a1] = { 0 };
	//double a[A<100>::p::a] = { 0 };
	//std::cout << f << std::endl;
	//Prime_print<LAST> a;
	//a.f();
}