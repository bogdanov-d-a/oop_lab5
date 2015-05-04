#pragma once

#include "DynamicArray.h"

class CMyString
{
public:
	CMyString();
	CMyString(char const* pString);
	CMyString(char const* pString, size_t length);

	size_t GetLength() const;
	char const* GetStringData() const;

private:
	CDynamicArray m_data;
};
