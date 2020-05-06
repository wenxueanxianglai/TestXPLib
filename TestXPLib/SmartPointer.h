#pragma once
#include "common.h"

#include "Object.h"
#include "Pointer.h"


BEGIN_NAMESPACE
	template<typename T>
	class CSmartPointer : public Pointer<T>
	{
	public:
		CSmartPointer(T* poniter = nullptr) : Pointer<T>(poniter) {}



		CSmartPointer(const CSmartPointer<T>& obj)
		{
			this->m_pointer = obj->m_pointer;

			const_cast<CSmartPointer<T>&>(obj).m_pointer = nullptr;
		}

		CSmartPointer<T>& operator = (const CSmartPointer<T>& obj)
		{
			if (*this != obj)
			{
				T* p = this->m_pointer;
				this->m_pointer = obj.m_pointer;
				const_cast<CSmartPointer<T>&>(obj).m_pointer = nullptr;

				delete p;
			}

			return *this;
		}

		~CSmartPointer()
		{
			if (this->m_pointer)
			{
				delete this->m_pointer;
			}
		}

	};
END_NAMESPACE
