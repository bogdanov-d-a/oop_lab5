#include "stdafx.h"
#include "DynamicArray.h"

using namespace std;

CDynamicArray::CDynamicArray(size_t size)
	:m_size(size)
{
	InitData();
}

CDynamicArray::CDynamicArray(CDynamicArray const& other)
	:CDynamicArray(0)
{
	*this = other;
}

CDynamicArray::CDynamicArray(CDynamicArray &&other)
	:CDynamicArray(0)
{
	*this = move(other);
}

CDynamicArray::~CDynamicArray()
{
	free(m_data);
}

CDynamicArray& CDynamicArray::operator=(CDynamicArray const& other)
{
	if (this == &other)
	{
		return *this;
	}

	m_size = other.m_size;

	free(m_data);
	InitData();

	if (m_size != 0)
	{
		memcpy(m_data, other.m_data, m_size);
	}

	return *this;
}

CDynamicArray& CDynamicArray::operator=(CDynamicArray &&other)
{
	if (this == &other)
	{
		return *this;
	}

	m_size = other.m_size;

	free(m_data);
	m_data = other.m_data;

	other.m_size = 0;
	other.m_data = nullptr;

	return *this;
}

char const CDynamicArray::operator[](size_t index) const
{
	assert(index < m_size);
	return m_data[index];
}

char& CDynamicArray::operator[](size_t index)
{
	assert(index < m_size);
	return m_data[index];
}

bool const CDynamicArray::operator==(CDynamicArray const& other) const
{
	if (m_size != other.m_size)
	{
		return false;
	}

	if (m_size == 0)
	{
		return true;
	}

	return (memcmp(m_data, other.m_data, m_size) == 0);
}

bool const CDynamicArray::operator!=(CDynamicArray const& other) const
{
	return !(*this == other);
}

size_t CDynamicArray::GetSize() const
{
	return m_size;
}

char const* CDynamicArray::GetData() const
{
	return m_data;
}

char* CDynamicArray::GetData()
{
	return m_data;
}

void CDynamicArray::InitData()
{
	if (m_size != 0)
	{
		m_data = static_cast<char*>(malloc(m_size));
		if (m_data == nullptr)
		{
			throw runtime_error("CDynamicArray bad allocation");
		}
	}
	else
	{
		m_data = nullptr;
	}
}
