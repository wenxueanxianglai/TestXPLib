#pragma once
#include "common.h"
#include "Queue.h"
#include "Exception.h"

BEGIN_NAMESPACE

template <typename T, int N>
class StaticQueue : public Queue<T>
{
public:
	StaticQueue() {	}
	int capacity() const {
		return N;
	}

	void add(const T& e) {
		if (m_length < N)
		{
			m_space[m_rear] = e;
			m_rear = (m_rear+1) % N;
			m_length++;
		}
		else
		{
			THROW_EXCEPTION(InvalidOperationException, "No space in current queue");
		}
	}

	void remove() {
		if (m_length > 0)
		{
			m_front = (m_front + 1) % N;
			m_length--;
		}
		else
		{
			THROW_EXCEPTION(InvalidOperationException, "No element in current queue...");
		}
	}

	T front() const {
		if (m_length > 0)
		{
			return m_space[m_front];
		}
		else
		{
			THROW_EXCEPTION(InvalidOperationException, "No element in current queue...");
		}
	}

	void clear() {
		m_front = 0;
		m_rear = 0;
		m_length = 0;
	}
	
	int length() const {
		return m_length;
	}

protected:
	T m_space[N];
	int m_front{ 0 };
	int m_rear{ 0 };
	int m_length{ 0 };
};


END_NAMESPACE