#pragma once
#include "common.h"

#include "Object.h"


BEGIN_NAMESPACE
	template<typename T>
	class CSmartPointer : public Object
	{
	public:
		CSmartPointer(T* poniter = nullptr) : m_pointer(poniter) {}



		CSmartPointer(const CSmartPointer<T>& obj) : m_pointer(obj.m_pointer)
		{
			const_cast<CSmartPointer<T>&>(obj).m_pointer = nullptr;
		}

		CSmartPointer<T>& operator = (const CSmartPointer<T>& obj)
		{
			if (*this != obj)
			{
				m_pointer = obj.m_pointer;
				const_cast<CSmartPointer<T>&>(obj).m_pointer = nullptr;
			}

			return *this;
		}

		~CSmartPointer()
		{
			if (m_pointer)
			{
				delete m_pointer;
			}
		}

		T* operator -> ()
		{
			return m_pointer;
		}

		T& operator* ()
		{
			return *m_pointer;
		}

		bool isNull() const
		{
			return (m_pointer == nullptr);
		}

		T* get() const
		{
			return m_pointer;
		}
	private:
		T* m_pointer;
	};
END_NAMESPACE
