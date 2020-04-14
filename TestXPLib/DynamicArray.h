#pragma once

#include "common.h"
#include "Array.h"
#include "Exception.h"

BEGIN_NAMESPACE

template <typename T>
class DynamicArray : public Array<T>
{
public:
	DynamicArray(int length);
	~DynamicArray();

	DynamicArray(const DynamicArray<T>& obj);
	DynamicArray<T>& operator= (const DynamicArray<T>& obj);

	virtual int length() const { return m_length; }
	void resize(int length);

protected:
	T* copy(T* array, int len, int newLen);

	void update(T* array, int length);

	void init(T* array, int length)
	{
		if (nullptr != array)
		{
			this->m_array = array;
			this->m_length = length;
		}
		else
		{
			THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray object...");
		}
	}

protected:
	int m_length;
};

template<typename T>
inline DynamicArray<T>::DynamicArray(int length)
{
	init(new T[length], length);
	//this->m_array = new T[length];

	//if (nullptr != this->m_array)
	//{
	//	this->m_length = length;
	//}
	//else
	//{
	//	THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray object...");
	//}
}

template<typename T>
inline DynamicArray<T>::~DynamicArray()
{
	delete[] this->m_array;
}

template<typename T>
inline DynamicArray<T>::DynamicArray(const DynamicArray<T>& obj)
{
	init(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);

	//this->m_array = new T[obj.m_length];

	//if (nullptr != this->m_array)
	//{
	//	this->m_length = obj.m_length;

	//	for (int i = 0; i <obj.m_length; ++i)
	//	{
	//		this->m_array[i] = obj.m_array[i];
	//	}
	//}
	//else
	//{
	//	THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray object...");
	//}
}

template<typename T>
inline DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& obj)
{
	if (this != &obj)
	{
		update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
		//////////////////////////////////////////////////////////////////////////
		//T* array = new T[obj.m_length];

		//if (nullptr != array)
		//{

		//	for (int i = 0; i < obj.m_length; ++i)
		//	{
		//		array[i] = obj.m_array[i];
		//	}

		//	T* temp = this->m_array;

		//	this->m_array = array;
		//	this->m_length = obj.m_length;

		//	delete[] temp;
		//}
		//else
		//{
		//	THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create copy DynamicArray object...");
		//}
	}

	return *this;
}

template<typename T>
inline void DynamicArray<T>::resize(int length)
{
	if (m_length != length)
	{
		update(copy(this->m_array, m_length, length), length);

		/*T* array = new T[length];

		if (nullptr != array)
		{
			int size = (length < m_length) ? length : m_length;
			for (int i = 0; i < size; ++i)
			{
				array[i] = this->m_array[i];
			}

			T* temp = this->m_array;

			this->m_array = array;
			this->m_length = length;

			delete[] temp;
		}
		else
		{
			THROW_EXCEPTION(NoEnoughMemoryException, "No memory to resize object...");
		}*/
	}
}

template<typename T>
inline T * DynamicArray<T>::copy(T * array, int len, int newLen)
{
	T* ret = new T[newLen];

	if (nullptr != ret)
	{
		int size = (len < newLen) ? len : newLen;

		for (int i = 0; i < size; ++i)
		{
			ret[i] = array[i];
		}
	}
	
	return ret;
}

template<typename T>
inline void DynamicArray<T>::update(T * array, int length)
{
	if (nullptr != array)
	{
		T* temp = this->m_array;

		this->m_array = array;
		this->m_length = length;

		delete[] temp;
	}
	else
	{
		THROW_EXCEPTION(NoEnoughMemoryException, "No memory to update object...");
	}
}



END_NAMESPACE


