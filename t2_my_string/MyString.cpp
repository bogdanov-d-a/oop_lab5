#include "stdafx.h"
#include "MyString.h"

CMyString::CMyString()
	:m_data(1)
{
	m_data[0] = '\0';
}

CMyString::CMyString(char const* pString)
	:CMyString(pString, strlen(pString))
{}

CMyString::CMyString(char const* pString, size_t length)
	:m_data(length + 1)
{
	memcpy(m_data.GetData(), pString, length);
	m_data[length] = '\0';
}

size_t CMyString::GetLength() const
{
	assert(m_data.GetSize() != 0);
	return (m_data.GetSize() - 1);
}

char const* CMyString::GetStringData() const
{
	return m_data.GetData();
}
