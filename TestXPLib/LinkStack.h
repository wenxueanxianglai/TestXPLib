#pragma once

#include "common.h"
#include "LinkList.h"

BEGIN_NAMESPACE

template<typename T>
class LinkStack : public Stack<T>
{
public:
	void push(const T& e) {
		m_list.insert(0, e);
	}

	void pop()
	{
		if (m_list.length() > 0)
		{
			m_list.remove(0);
		}
		else
		{
			THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
		}
	}

	T top() const {
		if (m_list.length() > 0)
		{
			return m_list.get(0);
		}
		else
		{
			THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
		}
	}

	void clear() {
		m_list.clear();
	}

	int size() const {
		return m_list.length();
	}

protected:
	LinkList<T> m_list;
};


END_NAMESPACE