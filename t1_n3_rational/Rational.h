#pragma once

class CRational
{
public:
	CRational(int numerator = 0, int denominator = 1);
	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;
	CRational const operator+() const;
	CRational const operator-() const;
	CRational& operator+=(CRational const& other);
	CRational& operator-=(CRational const& other);
	CRational& operator*=(CRational const& other);
	CRational& operator/=(CRational const& other);
	std::pair<int, CRational> ToCompoundFraction() const;

private:
	int m_numerator, m_denominator;
	void Normalize();
};

unsigned GCD(unsigned a, unsigned b);
unsigned LCM(unsigned a, unsigned b);
bool const operator==(CRational const& a, CRational const& b);
bool const operator!=(CRational const& a, CRational const& b);
CRational const operator+(CRational const& a, CRational const& b);
CRational const operator-(CRational const& a, CRational const& b);
CRational const operator*(CRational const& a, CRational const& b);
CRational const operator/(CRational const& a, CRational const& b);
bool const operator<(CRational const& a, CRational const& b);
bool const operator<=(CRational const& a, CRational const& b);
bool const operator>(CRational const& a, CRational const& b);
bool const operator>=(CRational const& a, CRational const& b);
std::ostream& operator<<(std::ostream &out, CRational const& num);
std::istream& operator>>(std::istream &in, CRational &num);
