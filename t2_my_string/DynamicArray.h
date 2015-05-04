#pragma once

class CDynamicArray
{
public:
	explicit CDynamicArray(size_t size = 0);
	CDynamicArray(CDynamicArray const& other);
	CDynamicArray(CDynamicArray &&other);
	~CDynamicArray();

	CDynamicArray& operator=(CDynamicArray const& other);
	CDynamicArray& operator=(CDynamicArray &&other);

	char const operator[](size_t index) const;
	char& operator[](size_t index);

	bool const operator==(CDynamicArray const& other) const;
	bool const operator!=(CDynamicArray const& other) const;

	size_t GetSize() const;
	void Assign(size_t size = 0);
	void Resize(size_t size);

	char const* GetData() const;
	char* GetData();

private:
	size_t m_size;
	char *m_data;

	void InitData();
};
