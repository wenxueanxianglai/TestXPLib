/*
* Pointer  
*/
#pragma once

#include "common.h"
#include "Object.h"

BEGIN_NAMESPACE

template<typename T>
class Pointer : public Object
{
public:
	Pointer(T* p = nullptr);
	
	T* operator->();
	T& operator* ();
	
	const T* operator->() const;
	const T& operator* () const;

	bool isNull() const;

	T* get() const;

protected:
	T* m_pointer;
};


template<typename T>
inline Pointer<T>::Pointer(T * p)
{
	m_pointer = p;
}

template<typename T>
inline T * Pointer<T>::operator->()
{
	return m_pointer;
}

template<typename T>
inline T & Pointer<T>::operator*()
{
	return *m_pointer;
}

template<typename T>
inline const T * Pointer<T>::operator->() const
{
	return m_pointer;
}

template<typename T>
inline const T & Pointer<T>::operator*() const
{
	return *m_pointer;
}

template<typename T>
inline bool Pointer<T>::isNull() const
{
	return (m_pointer == nullptr);
}

template<typename T>
inline T * Pointer<T>::get() const
{
	return m_pointer;
}



END_NAMESPACE


