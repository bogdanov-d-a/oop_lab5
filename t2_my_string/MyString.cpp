#include "stdafx.h"
#include "MyString.h"

using namespace std;

CMyString::CMyString()
{
	Clear();
}

CMyString::CMyString(char const* pString)
	:CMyString(pString, strlen(pString))
{}

CMyString::CMyString(char const* pString, size_t length)
	:m_data(length + 1)
{
	if (length != 0)
	{
		memcpy(m_data.GetData(), pString, length);
	}

	m_data[length] = '\0';
}

CMyString::CMyString(string const& stlString)
	:CMyString(stlString.c_str(), stlString.length())
{}

size_t CMyString::GetLength() const
{
	assert(m_data.GetSize() != 0);
	return (m_data.GetSize() - 1);
}

char const* CMyString::GetStringData() const
{
	return m_data.GetData();
}

CMyString const CMyString::SubString(size_t start, size_t length) const
{
	if (start >= GetLength())
	{
		throw invalid_argument("CMyString::SubString start index out of bounds");
	}

	return CMyString(GetStringData() + start, min(length, GetLength() - start));
}

void CMyString::Clear()
{
	m_data.Assign(1);
	m_data[0] = '\0';
}

CMyString& CMyString::operator+=(CMyString const& other)
{
	if (other.GetLength() == 0)
	{
		return *this;
	}

	size_t const oldLength = GetLength();
	m_data.Resize(GetLength() + other.GetLength() + 1);
	memcpy(m_data.GetData() + oldLength, other.GetStringData(), other.GetLength() + 1);

	return *this;
}

bool const operator==(CMyString const& a, CMyString const& b)
{
	return (a.m_data == b.m_data);
}

bool const operator!=(CMyString const& a, CMyString const& b)
{
	return !(a == b);
}

char const CMyString::operator[](size_t index) const
{
	return m_data[index];
}

char& CMyString::operator[](size_t index)
{
	return m_data[index];
}

CMyString const operator+(CMyString const& a, CMyString const& b)
{
	CMyString result(a);
	result += b;
	return result;
}

bool const operator<(CMyString const& a, CMyString const& b)
{
	int const result = memcmp(a.GetStringData(), b.GetStringData(), min(a.GetLength(), b.GetLength()));

	if (result != 0)
	{
		return (result < 0);
	}

	return (a.GetLength() < b.GetLength());
}

bool const operator>(CMyString const& a, CMyString const& b)
{
	int const result = memcmp(a.GetStringData(), b.GetStringData(), min(a.GetLength(), b.GetLength()));

	if (result != 0)
	{
		return (result > 0);
	}

	return (a.GetLength() > b.GetLength());
}

bool const operator<=(CMyString const& a, CMyString const& b)
{
	return !(a > b);
}

bool const operator>=(CMyString const& a, CMyString const& b)
{
	return !(a < b);
}

ostream& operator<<(ostream &out, CMyString const& str)
{
	for (size_t i = 0; i < str.GetLength(); ++i)
	{
		out.put(str[i]);
	}

	return out;
}

istream& operator>>(istream &in, CMyString &str)
{
	str.Clear();

	char curStr[2];
	curStr[1] = '\0';

	while (in.get(curStr[0]))
	{
		str += curStr;
	}

	return in;
}
