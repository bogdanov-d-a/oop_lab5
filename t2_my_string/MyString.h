#pragma once

#include "DynamicArray.h"

class CMyString
{
public:
	class CConstIterator;
	class CIterator;
	typedef std::reverse_iterator<CConstIterator> CConstReverseIterator;
	typedef std::reverse_iterator<CIterator> CReverseIterator;

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

	CIterator begin();
	CIterator end();

	CConstReverseIterator rbegin() const;
	CConstReverseIterator rend() const;

	CReverseIterator rbegin();
	CReverseIterator rend();

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
	typedef char const& reference;

	CConstIterator()
		:m_ptr(nullptr)
	{}

	CConstIterator(char const* ptr)
		:m_ptr(ptr)
	{}

	virtual ~CConstIterator()
	{}

	bool const operator==(CConstIterator const& other) const
	{
		return (m_ptr == other.m_ptr);
	}

	bool const operator!=(CConstIterator const& other) const
	{
		return !(*this == other);
	}

	reference operator*() const
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

	friend int operator-(CConstIterator const& a, CConstIterator const& b)
	{
		return (a.m_ptr - b.m_ptr);
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

	reference operator[](int n) const
	{
		return m_ptr[n];
	}

protected:
	char const* m_ptr;
};

class CMyString::CIterator
	:public CConstIterator
{
public:
	typedef char& reference;

	CIterator()
	{}

	CIterator(char *ptr)
		:CConstIterator(ptr)
	{}

	reference operator*() const
	{
		return *GetPtr();
	}

	CIterator& operator++()
	{
		CConstIterator::operator++();
		return *this;
	}

	CIterator operator++(int)
	{
		CIterator old(*this);
		CConstIterator::operator++();
		return old;
	}

	CIterator& operator--()
	{
		CConstIterator::operator--();
		return *this;
	}

	CIterator operator--(int)
	{
		CIterator old(*this);
		CConstIterator::operator--();
		return old;
	}

	CIterator operator+(int n) const
	{
		return CIterator(GetPtr() + n);
	}

	friend CIterator operator+(int n, CIterator const& it)
	{
		return CIterator(it.GetPtr() + n);
	}

	CIterator operator-(int n) const
	{
		return CIterator(GetPtr() - n);
	}

	CIterator& operator+=(int n)
	{
		CConstIterator::operator+=(n);
		return *this;
	}

	CIterator& operator-=(int n)
	{
		CConstIterator::operator-=(n);
		return *this;
	}

	reference operator[](int n) const
	{
		return GetPtr()[n];
	}

private:
	char* GetPtr() const
	{
		return const_cast<char*>(m_ptr);
	}
};
