// MetaProgTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <time.h>
#include <windows.h>
#include <iostream>

template <int i> class A {
public:
	enum p { a = A<i - 1>::p::a };
	constexpr static inline const int test() {
		return 10;
	}
};

template <> class A<1> {
public:
	enum p { a = 13 };
};

// e(x) = 1 + x + x^2/2! + x^3/3!
// e(x) = 1 + x * 1/1 * (1 + x * 1/2 * (1 + x * 1/3 * (1 + x * 1/4 * (1+x * 1/5 * (1 + x) )))) )
// sin(x) = x - x^3/3! + x^5/5! - ..... = x * (1 - x^2/3! + x^4/5! - ...)

double expRuntime(float x, int n, int k)
{
	if (k == 0) return 1;
	else return 1 + 1.0 / (n - k) * x * expRuntime(x, n, k - 2);
}

template <int a, int b, int n, int k> class expSeries { //x = a/b
public:
	enum { go = (k != 1) };
	static float f()
	{
		return 1.0 + 1.0 / (n - k) * (n-k+1) * (float)a / b * expSeries<a*go, b*go, n*go, k - 1>::f();
	}

	//static const float e = 
	//	1 + 1 / (n - k) * (float)a / b * expSeries<a, b, n, k - 1>::e;
};

template <> class expSeries<0, 0, 0, 0> {
public:
	//static const int e = 1;
	static float f() {
		return 1.0;
	}
};

/*
exp(x, 2, 1)
1 + 1 * x * exp(x, 2, 0) = 1 + 1 * x

exp(x, 3, 2)

1 + 1 * x * exp(x, 3, 1) = 1 + 1 * x * (1 + 1/2 * x  * exp(x,3,0)) = 1 + 1 * x * (1 + 1/2 * x ) = 1 + x + x^2/2
*/

#ifndef LAST
#define LAST 10
#endif
int k22test()
{
	//std::cout<<expRuntime(5, 1000, 999)<< std::endl;

	LARGE_INTEGER tm1, tm2;

	const int a = 1;
	const int b = 1;

	const int n = 2000;

	float res, t;
	int i;
	auto t1 = clock();
	QueryPerformanceCounter(&tm1);

	//res = expSeries<a, b, n, n-1>::f();	
	for (i = 0;i < 1000000;i++)
	{
		res = expSeries<a, b, n, n - 1>::f();
		//res = expRuntime((float)(a / b), n, n - 1);
		t += (res - i);
	}
	QueryPerformanceCounter(&tm2);
	t1 = clock() - t1;

	std::cout << "Result: " << res << ";" << t << std::endl;
	std::cout << "Time: " << tm2.QuadPart - tm1.QuadPart << "; " << tm2.QuadPart << ":" << tm1.QuadPart << std::endl;

	return 0;

	//const int f = 5;
	//enum r {a1 = A<100>::test(), b1};
	//double b[r::a1] = { 0 };
	//double a[A<100>::p::a] = { 0 };
	//std::cout << f << std::endl;
	//Prime_print<LAST> a;
	//a.f();
}