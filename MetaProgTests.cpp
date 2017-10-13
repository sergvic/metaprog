// MetaProgTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <time.h>
#include <windows.h>
#include <iostream>

template <int N, int I>
class Exp {
public:
	static float exponenta()
	{
		return float(I / N)*ExpSeries<N, I, 200, 1>::sum();
	}
};

// Обчислюємо J членів ряду Тейлора, використовуючи параметр K
// як лічильник циклу.
// Аргумент x представляється у вигляді дробу I/N
template<int N, int I, int J, int K>
class ExpSeries {
public:
	enum { go = (K + 1 != J) };
	static float sum()
	{
		//std::cout << K << std::endl;
		return 1 + float(I / N) / K*ExpSeries<N*go, I*go,
			J*go, (K + 1)*go>::sum();
	}
};

// Спеціалізація бази рекурсії
template<> class ExpSeries<0, 0, 0, 0> {
public:
	static float sum()
	{
		return 0;
	}
};

double expRuntimeTest(float x, int n, int k)
{
	if (k == 0) return 1;
	else return 1 + 1.0 / (n - k) * x * expRuntimeTest(x, n, k - 1);
}

#ifndef LAST
#define LAST 10
#endif
int main()
{
	//std::cout<<expRuntime(5, 1000, 999)<< std::endl;

	LARGE_INTEGER tm1, tm2;
	
	const int a = 1;
	const int b = 1;

	const int n = 200;

	float res, t;
	int i;
	auto t1 = clock();

	QueryPerformanceCounter(&tm1);

	//res = expSeries<a, b, n, n-1>::f();	
	for (i = 0;i < 10000000;i++)
	{
		res = 17;
		//res = expRuntime((float)(a / b), n, n - 1);
		t += (res - i);
	}
	QueryPerformanceCounter(&tm2);
	auto d1 = tm2.QuadPart - tm1.QuadPart;
	std::cout << "Empty time: " << d1 << std::endl;

	QueryPerformanceCounter(&tm1);
	
	//res = expSeries<a, b, n, n-1>::f();	
	for (i = 0;i < 10000000;i++)
	{
		res = Exp<a, b>::exponenta();
		//res = expRuntimeTest((float)(a / b), n, n - 1);
		t += (res - i);
	}
	QueryPerformanceCounter(&tm2);
	t1 = clock() - t1;

	std::cout << "Result: " << res << ";"<<t << std::endl;
	std::cout << "Time: " << tm2.QuadPart - tm1.QuadPart << "; " <<tm2.QuadPart<<":"<<tm1.QuadPart<< std::endl;

	return 0;

	//const int f = 5;
	//enum r {a1 = A<100>::test(), b1};
	//double b[r::a1] = { 0 };
	//double a[A<100>::p::a] = { 0 };
	//std::cout << f << std::endl;
	//Prime_print<LAST> a;
	//a.f();
}