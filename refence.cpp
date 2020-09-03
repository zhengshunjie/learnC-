#include "refence.h"
#include <string.h>
BigInt::BigInt(unsigned u)
{
	unsigned v = u;

	for (ndigits = 1; (v /= 10) > 0; ++ndigits)
	{
		;
	}
	digits = new char[size = ndigits];

	for (unsigned i = 0; i < ndigits; ++i)
	{
		digits[i] = u % 10;
		u /= 10;
	}
}

BigInt::BigInt(const char* s)
{
	if (s[0] == '\0')
	{
		s = "0";
	}
	size = ndigits = strlen(s);
	digits = new char[size];
	for (unsigned i = 0; i < ndigits; ++i)
	{
		digits[i] = s[ndigits - 1 - i] - '0';
	}
}

BigInt::~BigInt()
{
	delete[] digits;
}

BigInt& BigInt::operator=(const BigInt& rhs)
{
	if (this == &rhs) return *this;
	ndigits = rhs.ndigits;
	if (ndigits > size)
	{
		delete[] digits;
		digits = new char[size = ndigits];
	}

	for (unsigned i = 0; i < ndigits; ++i)
	{
		digits[i] = rhs.digits[i];
	}

	return *this;
}

