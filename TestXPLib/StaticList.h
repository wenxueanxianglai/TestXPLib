#pragma once
#include "common.h"
#include "SeqList.h"

BEGIN_NAMESPACE

template <typename T, int N>
class StaticList : public SeqList<T>
{
public:
	StaticList()
	{
		this->m_array = m_space;
		this->m_length = 0;
	}
	virtual int capacity() const
	{
		return N;
	}

protected:
	T m_space[N];
};


END_NAMESPACE