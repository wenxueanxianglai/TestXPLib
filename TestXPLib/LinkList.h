#pragma once

#include "common.h"

BEGIN_NAMESPACE

template <typename T>
class LinkList : public List<T>
{
protected:
	struct Node : public Object
	{
		T value;
		Node* next{ nullptr };
	};

public:
	LinkList(){}
	~LinkList() { clear(); }
public:
	virtual bool insert(const T& e);			//不知情况下，则插入尾部
	virtual bool insert(int i, const T& e);
	virtual bool remove(int i);

	virtual bool set(int i, const T& e);
	virtual bool get(int i, T& e) const;
	T get(int i) const;

	virtual int find(const T& e) const;


	virtual int length() const { return m_length; }

	virtual void clear();



public:
	bool move(int nPos, int step = 1);
	bool end();
	T current();
	bool next();


public:
	virtual Node* create()
	{
		return new Node();
	}

	virtual void destroy(Node* pn)
	{
		delete pn;
	}
protected:
	Node* position(int i) const
	{
		Node* ret = reinterpret_cast<Node*>(&m_header);
		for (int p = 0; p < i; ++p)
		{
			ret = ret->next;
		}

		return ret;
	}

	mutable struct : public Object {
		char reserved[sizeof(T)];
		Node* next{ nullptr };
	} m_header;

	int m_length{0};


	Node* m_current;
	int m_step;

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
			Node* current = position(i);

			node->value = e;
			node->next = current->next;
			current->next = node;

			++m_length;
		}
		else
		{
			THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new element...");
		}
	}

	return bRet;
}

template<typename T>
inline bool LinkList<T>::remove(int i)
{
	bool bRet = ((0 <= i) && (i <= m_length));
	if (bRet)
	{
		Node* current = position(i);

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
		Node* current = position(i);

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
		Node* current = position(i);

		e = current->next->value;

	}

	return bRet;
}

template<typename T>
inline T LinkList<T>::get(int i) const
{
	T ret; 
	if (get(i, ret))
	{
		return ret;
	}
	else
	{
		THROW_EXCEPTION(IndexOutOfBoundsException, "Invalid parameter i to get element...");
	}
	return ret;
}

template<typename T>
inline int LinkList<T>::find(const T & e) const
{
	int nRet = -1;
	int i = 0;

	Node* node = m_header.next;

	while (node)
	{
		if (node->value == e)
		{
			nRet = i;
			break;
		}
		else
		{
			node = node->next;
			++i;
		}
	}

	return nRet;
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

template<typename T>
inline bool LinkList<T>::move(int nPos, int step)
{
	bool ret = (nPos >=0 ) && (nPos < m_length) && (step>0);
	if (ret)
	{
		m_current = position(nPos)->next;
		m_step = step;
	}

	return ret;
}

template<typename T>
inline bool LinkList<T>::end()
{
	return (m_current == nullptr);
}

template<typename T>
inline T LinkList<T>::current()
{
	if (!end())
	{
		return m_current->value;
	}
	else
	{
		THROW_EXCEPTION(InvalidOperationException, "No valude at current position");
	}
}

template<typename T>
inline bool LinkList<T>::next()
{
	int i = 0;
	while((i < m_step) && (!end()))
	{
		m_current = m_current->next;
		++i;
	}

	return (i == m_step);
}



END_NAMESPACE

