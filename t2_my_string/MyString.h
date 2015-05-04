#pragma once

#include "DynamicArray.h"

class CMyString
{
public:
	CMyString();
	CMyString(char const* pString);
	CMyString(char const* pString, size_t length);
	CMyString(std::string const& stlString);

	size_t GetLength() const;
	char const* GetStringData() const;
	CMyString const SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();

	bool const operator==(CMyString const& other) const;
	bool const operator!=(CMyString const& other) const;

private:
	CDynamicArray m_data;
};
