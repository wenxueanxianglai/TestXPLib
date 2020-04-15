#pragma once

#include "common.h"

BEGIN_NAMESPACE

template <typename T>
class LinkList : public List<T>
{
public:
	LinkList() : m_header.next(nullptr), m_length(0){}
	~LinkList() { clear(); }
public:
	virtual bool insert(const T& e);			//不知情况下，则插入尾部
	virtual bool insert(int i, const T& e);
	virtual bool remove(int i);

	virtual bool set(int i, const T& e);
	virtual bool get(int i, T& e) const;

	virtual int length() const { return m_length; }

	virtual void clear();
protected:
	struct Node : public Object 
	{
		T value;
		Node* next;
	};

	Node m_header;
	int m_length;
};

template<typename T>
inline bool LinkList<T>::insert(const T & e)
{
	return insert(m_length, e);
}

template<typename T>
inline bool LinkList<T>::insert(int i, const T & e)
{
	bool bRet = ((0 <= i) && (i <= m_length));

	if (bRet)
	{
		Node* node = new Node();
		if (nullptr != node)
		{
			Node* current = &m_header;

			for (int pos = 0; pos< i; ++pos)
			{
				current = current->next;
			}

			node->value = e;
			node->next = current->next;
			current->next = node;

			++m_length;
		}
		else
		{
			THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert element...");
		}
	}
	//else
	//{

	//}


	return bRet;
}

template<typename T>
inline bool LinkList<T>::remove(int i)
{
	bool bRet = ((0 <= i) && (i <= m_length));
	if (bRet)
	{
		Node* current = &m_header;

		for (int pos = 0; pos < i; ++pos)
		{
			current = current->next;
		}

		Node* ptoDel = current->next;
		current->next = ptoDel->next;
		delete ptoDel;

		m_length--;
		
	}

	return bRet;
}

template<typename T>
inline bool LinkList<T>::set(int i, const T & e)
{
	bool bRet = ((0 <= i) && (i <= m_length));
	if (bRet)
	{
		Node* current = &m_header;

		for (int pos = 0; pos < i; ++pos)
		{
			current = current->next;
		}

		current->next->value = e;

	}

	return bRet;
}

template<typename T>
inline bool LinkList<T>::get(int i, T & e) const
{
	bool bRet = ((0 <= i) && (i <= m_length));
	if (bRet)
	{
		Node* current = &m_header;

		for (int pos = 0; pos < i; ++pos)
		{
			current = current->next;
		}

		e = current->next->value;

	}

	return bRet;
}

template<typename T>
inline void LinkList<T>::clear()
{
	while (m_header.next)
	{
		Node* toDel = m_header.next;
		m_header.next = toDel->next;

		delete toDel;
	}

	m_length = 0;
}



END_NAMESPACE

