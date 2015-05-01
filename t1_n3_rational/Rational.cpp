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

double CRational::ToDouble() const
{
	return (1.0 * m_numerator / m_denominator);
}

CRational const CRational::operator+() const
{
	return *this;
}

CRational const CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational& CRational::operator+=(CRational const& other)
{
	*this = *this + other;
	return *this;
}

CRational& CRational::operator-=(CRational const& other)
{
	*this = *this - other;
	return *this;
}

CRational& CRational::operator*=(CRational const& other)
{
	*this = *this * other;
	return *this;
}

CRational& CRational::operator/=(CRational const& other)
{
	*this = *this / other;
	return *this;
}

pair<int, CRational> CRational::ToCompoundFraction() const
{
	int const signMultiplier = (m_numerator < 0) ? -1 : 1;

	return pair<int, CRational>(signMultiplier * (abs(m_numerator) / m_denominator),
		CRational(signMultiplier * (abs(m_numerator) % m_denominator), m_denominator));
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

unsigned LCM(unsigned a, unsigned b)
{
	return (a / GCD(a, b) * b);
}

bool const operator==(CRational const& a, CRational const& b)
{
	return (a.GetNumerator() == b.GetNumerator() &&
		a.GetDenominator() == b.GetDenominator());
}

bool const operator!=(CRational const& a, CRational const& b)
{
	return !(a == b);
}

CRational const operator+(CRational const& a, CRational const& b)
{
	unsigned const lcm = LCM(a.GetDenominator(), b.GetDenominator());
	return CRational(a.GetNumerator() * (lcm / a.GetDenominator()) + b.GetNumerator() * (lcm / b.GetDenominator()), lcm);
}

CRational const operator-(CRational const& a, CRational const& b)
{
	return (a + (-b));
}

CRational const operator*(CRational const& a, CRational const& b)
{
	return CRational(a.GetNumerator() * b.GetNumerator(), a.GetDenominator() * b.GetDenominator());
}

CRational const operator/(CRational const& a, CRational const& b)
{
	if (b.GetNumerator() == 0)
	{
		throw invalid_argument("Can't divide by zero");
	}

	return CRational(a.GetNumerator() * b.GetDenominator(), a.GetDenominator() * b.GetNumerator());
}

bool const operator<(CRational const& a, CRational const& b)
{
	return (a.ToDouble() < b.ToDouble());
}

bool const operator<=(CRational const& a, CRational const& b)
{
	return (a == b || a < b);
}

bool const operator>(CRational const& a, CRational const& b)
{
	return (a.ToDouble() > b.ToDouble());
}

bool const operator>=(CRational const& a, CRational const& b)
{
	return (a == b || a > b);
}

ostream& operator<<(ostream &out, CRational const& num)
{
	return (out << num.GetNumerator() << "/" << num.GetDenominator());
}

istream& operator>>(istream &in, CRational &num)
{
	streamoff const startPos = in.tellg();

	int numerator, denominator;
	if ((in >> numerator) && (in.get() == '/') && (in >> denominator))
	{
		num = CRational(numerator, denominator);
	}
	else
	{
		in.seekg(startPos);
		in.setstate(in.rdstate() | ios_base::failbit);
	}

	return in;
}
