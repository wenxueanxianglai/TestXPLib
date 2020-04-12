#pragma once
#include "common.h"
#include "SeqList.h"
#include "Exception.h"

BEGIN_NAMESPACE

template <typename T>
class DynamicList : public SeqList<T>
{
public:
	DynamicList(int nCapacity);	//申请空间
	~DynamicList();				//归还空间

	virtual int capacity() const;

	// 重新设置顺序存储空间的大小
	void resize(int nCapacity);

protected:
	int m_capacity;		//顺序存储空间的大小
};

template<typename T>
 DynamicList<T>::DynamicList(int nCapacity)
{
	this->m_array = new T[nCapacity];
	if (nullptr != this->m_array)
	{
		this->m_length = 0;
		this->m_capacity = nCapacity;
	}
	else
	{
		THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicList object...");
	}
}

template<typename T>
 DynamicList<T>::~DynamicList<T>()
{
	delete[] this->m_array;
}

template<typename T>
int DynamicList<T>::capacity() const
{
	return m_capacity;
}

template<typename T>
void DynamicList<T>::resize(int nCapacity)
{
	if ( nCapacity != m_capacity)
	{
		T* arr = new T[nCapacity];

		if (nullptr != arr)
		{
			int length = (this->m_length < nCapacity) ? this->m_length : nCapacity;

			for (int i = 0; i< length; ++i)
			{
				arr[i] = this->m_array[i];
			}

			T* temp = this->m_array;

			this->m_array = arr;
			this->m_length = length;
			this->m_capacity = nCapacity;

			delete[] temp;
		}
		else
		{
			THROW_EXCEPTION(NoEnoughMemoryException, "No memory to resize DynamicList...");
		}
	}
}



END_NAMESPACE