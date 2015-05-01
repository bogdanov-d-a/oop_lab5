#include "stdafx.h"
#include "Rational.h"

using namespace std;

CRational::CRational(int numerator, int denominator)
	:m_numerator(numerator)
	,m_denominator(denominator)
{
	if (m_denominator == 0)
	{
		m_numerator = 0;
		m_denominator = 1;
	}
	else if (m_denominator < 0)
	{
		m_numerator *= -1;
		m_denominator *= -1;
	}
	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

void CRational::Normalize()
{
	const int gcd = GCD(abs(m_numerator), m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

unsigned GCD(unsigned a, unsigned b)
{
	while (b != 0)
	{
		swap(a, b);
		b = b % a;
	}
	return (a != 0) ? a : 1;
}
