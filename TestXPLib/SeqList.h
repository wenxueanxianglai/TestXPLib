#pragma once
#include "common.h"
#include "List.h"
#include "Exception.h"

BEGIN_NAMESPACE

template <typename T>
class SeqList : List<T>
{
public:
	virtual bool insert(const T& e);
	virtual bool insert(int i, const T& e);
	virtual bool remove(int i);

	virtual bool set(int i, const T& e);
	virtual bool get(int i, T& e) const;

	virtual int find(const T& e) const;


	virtual int length() const;

	virtual void clear();

	T& operator[](int i);
	T  operator[](int i) const;

public:
	virtual int capacity() const = 0;

protected:
	T* m_array;		//顺序存储空间
	int m_length;	// 当前线性表长度
};

template<typename T>
inline bool SeqList<T>::insert(const T & e)
{
	return insert(m_length, e);
}

template <typename T>
bool SeqList<T>::insert(int i, const T& e)
{
	bool bRet = ((0 <= i) && (i <= m_length));

	bRet = bRet && (m_length < capacity());

	if (bRet)
	{
		for (int p = m_length - 1; p >= i; p--)			// O(n)		最坏情况，插入在头部
		{
			m_array[p + 1] = m_array[p];
		}

		m_array[i] = e;
		m_length++;
	}

	return bRet;
}

template <typename T>
bool SeqList<T>::remove(int i)
{
	bool bRet = ((0 <= i) && (i < m_length));

	if (bRet)
	{
		for (int p = i; p < m_length-1; p++)				//O(n)
		{
			m_array[p] = m_array[p + 1];
		}

		m_length--;
	}

	return bRet;
}

template<typename T>
inline bool SeqList<T>::set(int i, const T & e)
{
	bool bRet = ((0 <= i) && (i < m_length));

	if (bRet)
	{
		m_array[i] = e;
	}

	return bRet;
}

template <typename T>
bool SeqList<T>::get(int i, T& e) const
{
	bool bRet = ((0 <= i) && (i < m_length));

	if (bRet)
	{
		e = m_array[i];
	}

	return bRet;
}

template<typename T>
inline int SeqList<T>::find(const T & e) const
{
	int nRet = -1;

	for (int i = 0; i < m_length; ++i)				//O(n)
	{
		if (m_array[i] == e)
		{
			nRet = i;
			break;
		}
	}

	return nRet;
}

template <typename T>
int SeqList<T>::length() const
{
	return m_length;
}

template<typename T>
inline void SeqList<T>::clear()
{
	m_length = 0;
}

template<typename T>
inline T & SeqList<T>::operator[](int i)
{
	if ((0 <= i) && (i < m_length))
	{
		return m_array[i];
	}
	else
	{
		THROW_EXCEPTION(IndexOutOfBoundsException, "Paramter i is invalid...");
	}
}

template<typename T>
inline T SeqList<T>::operator[](int i) const
{
	return const_cast<SeqList<T>&>(*this)[i];
//	return T();
}


END_NAMESPACE