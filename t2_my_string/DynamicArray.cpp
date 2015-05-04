#include "stdafx.h"
#include "DynamicArray.h"

using namespace std;

CDynamicArray::CDynamicArray(size_t size)
	:m_size(size)
{
	InitData();
}

CDynamicArray::CDynamicArray(CDynamicArray const& other)
{
	m_size = other.m_size;
	InitData();

	if (m_size != 0)
	{
		memcpy(m_data, other.m_data, m_size);
	}
}

CDynamicArray::CDynamicArray(CDynamicArray &&other)
{
	m_size = other.m_size;
	m_data = other.m_data;

	other.m_size = 0;
	other.m_data = nullptr;
}

CDynamicArray::~CDynamicArray()
{
	free(m_data);
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
