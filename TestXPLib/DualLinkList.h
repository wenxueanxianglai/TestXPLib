#pragma once
#include "common.h"
#include "List.h"

BEGIN_NAMESPACE

template <typename T>
class DualLinkList : public List<T>
{
public:
	struct Node : public Object
	{
		T value;
		Node* next{ nullptr };
		Node* pre{ nullptr };
	};

	
public:
	DualLinkList() {}
	~DualLinkList() { clear(); }

public:
	virtual bool insert(const T& e);			//不知情况下，则插入尾部
	virtual bool insert(int i, const T& e);
	virtual bool remove(int i);

	virtual bool set(int i, const T& e);
	virtual bool get(int i, T& e) const;
	virtual T get(int i) const;

	virtual int find(const T& e) const;


	virtual int length() const { return m_length; }

	virtual void clear();

public:
	virtual bool move(int nPos, int step = 1);
	virtual bool end();
	virtual T current();
	virtual bool next();
	virtual bool pre();

public:
	virtual Node* create() {return new Node();}
	virtual void destroy(Node* pn){	delete pn;}

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


protected:
	mutable struct : public Object
	{
		char reserved[sizeof(T)];
		Node* next{nullptr};
		Node* pre{nullptr};
	} m_header;

	int m_length{ 0 };


	Node* m_current{nullptr};
	int m_step{1};
};

template<typename T>
inline bool DualLinkList<T>::insert(const T & e)
{
	return insert(m_length, e);
}

template<typename T>
inline bool DualLinkList<T>::insert(int i, const T & e)
{
	bool bRet = ((0 <= i) && (i <= m_length));

	if (bRet)
	{
		Node* node = create(); //new Node();
		if (nullptr != node)
		{
			Node* current = position(i);

			Node* next = current->next;


			node->value = e;

			node->next = next;
			current->next = node;

			if (current != reinterpret_cast<Node*>(&m_header))
			{
				node->pre = current;
			}
			else
			{
				node->pre = nullptr;
			}

			if (next != nullptr)
			{
				next->pre = node;
			}

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
inline bool DualLinkList<T>::remove(int i)
{
	bool bRet = ((0 <= i) && (i <= m_length));
	if (bRet)
	{
		Node* current = position(i);
		Node* ptoDel = current->next;
		Node* next = ptoDel->next;

		if (m_current == ptoDel)
		{
			m_current = next;
		}


		current->next = next;
		
		if (next != nullptr)
		{
			next->pre = ptoDel->pre;
		}
		

		m_length--;

		destroy(ptoDel);
	}

	return bRet;
}

template<typename T>
inline bool DualLinkList<T>::set(int i, const T & e)
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
inline bool DualLinkList<T>::get(int i, T & e) const
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
inline T DualLinkList<T>::get(int i) const
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
inline int DualLinkList<T>::find(const T & e) const
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
inline void DualLinkList<T>::clear()
{
	while (m_length)
	{
		remove(0);
	}

}

template<typename T>
inline bool DualLinkList<T>::move(int nPos, int step)
{
	bool ret = (nPos >= 0) && (nPos < m_length) && (step > 0);
	if (ret)
	{
		m_current = position(nPos)->next;
		m_step = step;
	}

	return ret;
}

template<typename T>
inline bool DualLinkList<T>::end()
{
	return (m_current == nullptr);
}

template<typename T>
inline T DualLinkList<T>::current()
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
inline bool DualLinkList<T>::next()
{
	int i = 0;
	while ((i < m_step) && (!end()))
	{
		m_current = m_current->next;
		++i;
	}

	return (i == m_step);
}

template<typename T>
inline bool DualLinkList<T>::pre()
{
	int i = 0;
	while ((i < m_step) && (!end()))
	{
		m_current = m_current->pre;
		++i;
	}

	return (i == m_step);
}



END_NAMESPACE

