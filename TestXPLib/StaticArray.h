#pragma once
#include "common.h"
#include "Array.h"

BEGIN_NAMESPACE

template <typename T, int N>
class StaticArray : public Array<T>
{
public:
	StaticArray();

	StaticArray(const StaticArray<T, N>& obj);
	StaticArray<T, N>& operator= (const StaticArray<T, N>& obj);

	virtual int length() const { return N; }
protected:
	T m_space[N];
};

template<typename T, int N>
inline StaticArray<T, N>::StaticArray()
{
	this->m_array = m_space;
}

template<typename T, int N>
inline StaticArray<T, N>::StaticArray(const StaticArray<T, N>& obj)
{
	this->m_array = m_space;

	for (int i = 0; i < N; ++i)
	{
		m_space[i] = obj.m_space[i];
	}
}

template<typename T, int N>
inline StaticArray<T, N>& StaticArray<T, N>::operator=(const StaticArray<T, N>& obj)
{
	if (this != &obj)
	{
		for (int i = 0; i < N; ++i)
		{
			m_space[i] = obj.m_space[i];
		}
	}
	return *this;
}



END_NAMESPACE


