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

bool const CMyString::operator==(CMyString const& other) const
{
	return (m_data == other.m_data);
}

bool const CMyString::operator!=(CMyString const& other) const
{
	return !(*this == other);
}
