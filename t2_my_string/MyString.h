#pragma once

#include "DynamicArray.h"

class CMyString
{
public:
	class CConstIterator;

	CMyString();
	CMyString(char const* pString);
	CMyString(char const* pString, size_t length);
	CMyString(std::string const& stlString);

	size_t GetLength() const;
	char const* GetStringData() const;
	CMyString const SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();
	CMyString& operator+=(CMyString const& other);

	friend bool const operator==(CMyString const& a, CMyString const& b);
	friend bool const operator!=(CMyString const& a, CMyString const& b);

	char const operator[](size_t index) const;
	char& operator[](size_t index);

	CConstIterator begin() const;
	CConstIterator end() const;

private:
	CDynamicArray m_data;
};

CMyString const operator+(CMyString const& a, CMyString const& b);

bool const operator<(CMyString const& a, CMyString const& b);
bool const operator>(CMyString const& a, CMyString const& b);
bool const operator<=(CMyString const& a, CMyString const& b);
bool const operator>=(CMyString const& a, CMyString const& b);

std::ostream& operator<<(std::ostream &out, CMyString const& str);
std::istream& operator>>(std::istream &in, CMyString &str);

class CMyString::CConstIterator
	:public std::iterator<std::random_access_iterator_tag, char>
{
public:
	CConstIterator()
		:m_ptr(nullptr)
	{}

	CConstIterator(char const* ptr)
		:m_ptr(ptr)
	{}

	bool const operator==(CConstIterator const& other) const
	{
		return (m_ptr == other.m_ptr);
	}

	bool const operator!=(CConstIterator const& other) const
	{
		return !(*this == other);
	}

	char const& operator*() const
	{
		return *m_ptr;
	}

	CConstIterator& operator++()
	{
		++m_ptr;
		return *this;
	}

	CConstIterator operator++(int)
	{
		CConstIterator old(*this);
		++m_ptr;
		return old;
	}

	CConstIterator& operator--()
	{
		--m_ptr;
		return *this;
	}

	CConstIterator operator--(int)
	{
		CConstIterator old(*this);
		--m_ptr;
		return old;
	}

	CConstIterator operator+(int n) const
	{
		return CConstIterator(m_ptr + n);
	}

	friend CConstIterator operator+(int n, CConstIterator const& it)
	{
		return CConstIterator(it.m_ptr + n);
	}

	CConstIterator operator-(int n) const
	{
		return CConstIterator(m_ptr - n);
	}

	int operator-(CConstIterator const& other) const
	{
		return (m_ptr - other.m_ptr);
	}

	bool const operator<(CConstIterator const& other) const
	{
		return (m_ptr < other.m_ptr);
	}

	bool const operator>(CConstIterator const& other) const
	{
		return (m_ptr > other.m_ptr);
	}

	bool const operator<=(CConstIterator const& other) const
	{
		return !(*this > other);
	}

	bool const operator>=(CConstIterator const& other) const
	{
		return !(*this < other);
	}

	CConstIterator& operator+=(int n)
	{
		m_ptr += n;
		return *this;
	}

	CConstIterator& operator-=(int n)
	{
		m_ptr -= n;
		return *this;
	}

	char const& operator[](int n) const
	{
		return m_ptr[n];
	}

private:
	char const* m_ptr;
};
