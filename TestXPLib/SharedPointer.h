#pragma once

#include <cstdlib>
#include "common.h"
#include "Pointer.h"
#include "Exception.h"

BEGIN_NAMESPACE

template <typename T>
class SharedPointer : public Pointer<T>
{
public:
	SharedPointer(T* p = nullptr);
	SharedPointer(const SharedPointer<T>& obj);
	SharedPointer<T>& operator= (const SharedPointer<T>& obj);
	~SharedPointer();


	void clear();		//将当前指针置空

protected:
	void assign(const SharedPointer<T>& obj);

protected:
	int* m_ref;			//计数机制成员指针
};

template<typename T>
bool operator == (const SharedPointer<T>& l, const SharedPointer<T>& r)
{
	return (l.get() == r.get());
}

template<typename T>
bool operator != (const SharedPointer<T>& l, const SharedPointer<T>& r)
{
	return !(l.get() == r.get());
}


template<typename T>
inline SharedPointer<T>::SharedPointer(T * p) : m_ref(nullptr)
{
	if (p)
	{
		this->m_ref = static_cast<int*>(malloc(sizeof(int)));
		if (this->m_ref)
		{
			*(this->m_ref) = 1;
			this->m_pointer = p;
		}
		else
		{
			THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create SharedPointer object...");
		}
	}
}

template<typename T>
inline SharedPointer<T>::SharedPointer(const SharedPointer<T>& obj)
{
	assign(obj);

}

template<typename T>
inline SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<T>& obj)
{
	
	if (this != &obj)
	{
		clear();
		assign(obj);
	}

	return *this;
}

template<typename T>
inline SharedPointer<T>::~SharedPointer()
{
	clear();
}

template<typename T>
inline void SharedPointer<T>::clear()
{
	T* toDel = this->m_pointer;
	int* ref = this->m_ref;

	this->m_pointer = nullptr;
	this->m_ref = nullptr;

	if (ref)
	{
		(*ref)--;
		if (*ref == 0)
		{
			free(ref);
			delete toDel;
		}
	}
}

template<typename T>
inline void SharedPointer<T>::assign(const SharedPointer<T>& obj)
{
	this->m_ref = obj.m_ref;
	this->m_pointer = obj.m_pointer;

	if (this->m_ref)
	{
		(*this->m_ref)++;
	}
}


END_NAMESPACE


