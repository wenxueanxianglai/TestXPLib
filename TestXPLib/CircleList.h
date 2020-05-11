#pragma once

#include "common.h"
#include "LinkList.h"


BEGIN_NAMESPACE

template<typename T>
using Node = typename LinkList<T>::Node;

template<typename T>
class CircleList : public LinkList<T>
{
public:
	bool insert(const T & e);
	bool insert(int i, const T& e);

	bool remove(int i);

	bool set(int i, const T& e);

	T get(int i) const;
	bool get(int i, const T & e) const;

	int find(const T& e) const;

	void clear();

	~CircleList()
	{
		clear();
	}

public:
	virtual bool move(int nPos, int step = 1);
	virtual bool end();
	

protected:
	Node<T>* last() const;

	void last_to_first() const;

	int mod(int i) const;
};

template<typename T>
inline bool CircleList<T>::insert(const T & e)
{
	return insert(this->m_length, e);
}

template<typename T>
inline bool CircleList<T>::insert(int i, const T & e)
{
	bool ret = true;

	i = i % (this->m_length + 1);

	ret = LinkList<T>::insert(i, e);

	if (ret && (i ==0))
	{
		last_to_first();
	}

	return false;
}

template<typename T>
inline bool CircleList<T>::remove(int i)
{
	bool ret = true;
	i = mod(i);

	if (i == 0)
	{
		Node<T>* toDel = this->m_header.next;

		if (toDel != nullptr)
		{
			this->m_header.next = toDel->next;
			this->m_length--;

			if (this->m_length > 0)
			{
				last_to_first();

				if (this->m_current == toDel)
				{
					this->m_current = toDel->next;
				}
			}
			else
			{
				this->m_header.next = nullptr;
				this->m_current = nullptr;
			}

			this->destroy(toDel);
		}
		else
		{
			ret = false;
		}
	}
	else
	{
		ret = LinkList<T>::remove(i);
	}


	return false;
}

template<typename T>
inline bool CircleList<T>::set(int i, const T & e)
{
	return LinkList<T>::set(mod(i), e);
	return false;
}

template<typename T>
inline T CircleList<T>::get(int i) const
{
	return LinkList<T>::get(mod(i));
}

template<typename T>
inline bool CircleList<T>::get(int i, const T & e) const
{
	return LinkList<T>::get(mod(i), e);
}

template<typename T>
inline int CircleList<T>::find(const T & e) const
{
	int ret = -1;
	Node<T>* slider = this->m_header.next;

	for (int i = 0; i < this->m_length; ++i)
	{
		if (slider->value == e)
		{
			ret = i;
			break;
		}

		slider = slider->next;
	}

	return ret;


	return ret;
}

template<typename T>
inline void CircleList<T>::clear()
{
	while (this->m_length > 1)
	{
		remove(1);
	}
	if (this->m_length == 1)
	{
		Node<T>* toDel = this->m_header.next;

		this->m_header.next = nullptr;
		this->m_length = 0;
		this->m_current = nullptr;

		this->destroy(toDel);
	}
}

template<typename T>
inline bool CircleList<T>::move(int nPos, int step)
{
	return LinkList<T>::move(mod(nPos), step);
}

template<typename T>
inline bool CircleList<T>::end()
{
	return (this->m_length == 0) || (this->m_current == nullptr);
}

template<typename T>
inline Node<T> * CircleList<T>::last() const
{
	return this->position(this->m_length - 1)->next;
}

template<typename T>
inline void CircleList<T>::last_to_first() const
{
	last()->next = this->m_header.next;
}

template<typename T>
inline int CircleList<T>::mod(int i) const
{
	return (this->m_length == 0) ? 0 : (i % this->m_length);
	return 0;
}



END_NAMESPACE

