#pragma once

#include "common.h"
#include "Stack.h"

BEGIN_NAMESPACE


template <typename T, int N>
class StaticStack : public Stack<T>
{
public:
	StaticStack() {
		m_top = -1;
		m_size = 0;
	}


	int capacity() const
	{
		return N;
	}

	void push(const T& e) {
		if (m_size < N)
		{
			m_space[m_top + 1] = e;
			
			m_top++;
			m_size++;
		}
		else
		{
			THROW_EXCEPTION(InvalidOperationException, "No Space in current stack.....");
		}
	}

	void pop()
	{
		if (m_size>0)
		{
			m_top--;
			m_size--;
		}
		else
		{
			THROW_EXCEPTION(InvalidOperationException, "No element in current stack...");
		}
	}

	T top() const
	{
		if (m_size > 0)
		{
			return m_space[m_top];
		}
		else
		{
			THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
		}
	}

	void clear()
	{
		m_top = -1;
		m_size = 0;
	}

	int size() const
	{
		return m_size;
	}

protected:
	T m_space[N];
	int m_top;
	int m_size;
};


END_NAMESPACE