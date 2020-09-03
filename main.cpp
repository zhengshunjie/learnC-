#include<iostream>
#include<windows.h>
#include"refence.h"

void testRCBigIntAssign(int n)
{
	RCBigInt a, b, c;
	RCBigInt d = 1;
	
	for (int i = 0; i < n; ++i)
	{
		a = b = c = d;
	}
}

void testBigIntAssign(int n)
{
	BigInt a, b, c;
	BigInt d = 1;
	
	for (int i = 0; i < n; ++i)
	{
		a = b = c = d;
	}
}

void testRCBigIntCreate(int n)
{
	for (int i = 0; i < n; ++i)
	{
		RCBigInt a = i;
		RCBigInt b = i + 1;
		RCBigInt c = i + 2;
		RCBigInt d = i + 3;
	}
}

void testBigIntCreate(int n)
{
	for (int i = 0; i < n; ++i)
	{
		BigInt a = i;
		BigInt b = i + 1;
		BigInt c = i + 2;
		BigInt d = i + 3;
	}
}

int main()
{
	int n = 1000000;
	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;
	LARGE_INTEGER frequency;
	double elapsed;
	QueryPerformanceFrequency(&frequency);
	double quadpart = (double)frequency.QuadPart;

	QueryPerformanceCounter(&timeStart);
	testBigIntCreate(n);
	QueryPerformanceCounter(&timeEnd);
	
	elapsed = (timeEnd.QuadPart - timeStart.QuadPart) / quadpart;
	std::cout << "testBigIntCreate:" << elapsed << " s" << std::endl;

	QueryPerformanceCounter(&timeStart);
	testRCBigIntCreate(n);
	QueryPerformanceCounter(&timeEnd);

	elapsed = (timeEnd.QuadPart - timeStart.QuadPart) / quadpart;
	std::cout << "testRCBigIntCreate:" << elapsed << " s" << std::endl;

	QueryPerformanceCounter(&timeStart);
	testBigIntAssign(n);
	QueryPerformanceCounter(&timeEnd);

	elapsed = (timeEnd.QuadPart - timeStart.QuadPart) / quadpart;
	std::cout << "testBigIntAssign:" << elapsed << " s" << std::endl;

	QueryPerformanceCounter(&timeStart);
	testRCBigIntAssign(n);
	QueryPerformanceCounter(&timeEnd);

	elapsed = (timeEnd.QuadPart - timeStart.QuadPart) / quadpart;
	std::cout << "testRCBigIntAssign:" << elapsed<< " s" << std::endl;

	system("pause");
	return 0;
}

