#pragma once

#include "common.h"
#include "Object.h"
#include "Exception.h"

BEGIN_NAMESPACE
template <typename T>
class Array : public Object
{
public:
	virtual bool set(int i, const T& e);
	virtual bool get(int i, T& e) const;

	T& operator[] (int i);
	T operator[] (int i) const;

	virtual int length() const = 0;

protected:
	T* m_array;
};


template<typename T>
inline bool Array<T>::set(int i, const T & e)
{
	bool bRet = ((0 <= i) && (i < length()));
	if (bRet)
	{
		m_array[i] = e;
	}

	return bRet;
}

template<typename T>
inline bool Array<T>::get(int i, T & e) const
{
	bool bRet = ((0 <= i) && (i < length()));
	if (bRet)
	{
		e = m_array[i];
	}

	return bRet;
}

template<typename T>
inline T & Array<T>::operator[](int i)
{
	if ((0 <= i) && (i < length()))
	{
		return m_array[i];
	}
	else
	{
		THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");
	}
}

template<typename T>
inline T Array<T>::operator[](int i) const
{
	return (const_cast<Array<T>&>(*this))[i];
}





END_NAMESPACE


