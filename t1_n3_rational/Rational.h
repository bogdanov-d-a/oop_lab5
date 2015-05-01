#pragma once

class CRational
{
public:
	CRational(int numerator = 0, int denominator = 1);
	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;

private:
	int m_numerator, m_denominator;
	void Normalize();
};

unsigned GCD(unsigned a, unsigned b);
