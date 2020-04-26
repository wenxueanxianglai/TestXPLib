#pragma once

#include "common.h"
#include "LinkList.h"

BEGIN_NAMESPACE


template<typename T, int N>
class StaticLinkList : public LinkList<T>
{
	using Node = LinkList<T>::Node;   //typename LinkList<T>::Node

	struct SNode : public Node
	{
		void* operator new(unsigned int size, void* loc)
		{
			return loc;
		}
	};

public:
	StaticLinkList()
	{
		for (auto& i : m_used)
		{
			i = 0;
		}
	}

	int capacity()
	{
		return N;
	}


	Node* create()
	{
		SNode* ret = nullptr;
		for (int i = 0; i < N; ++i)
		{
			if (!m_used[i])
			{
				ret = reinterpret_cast<SNode*>(m_space) + i;
				ret = new(ret) SNode();
				m_used[i] = 1;
				break;
			}
		}
		return nullptr;
	}

	virtual void destroy(Node* pn)
	{
		//delete pn;
		SNode* space = reinterpret_cast<SNode*>(m_space);
		SNode* psn = dynamic_cast<SNode*>(pn);

		for (int i = 0; i < N; ++i)
		{
			if (psn == (space + i))
			{
				m_used[i] = 0;
				psn->~SNode();
			}
		}
	}

protected:
	unsigned char m_space[sizeof(SNode) * N];
	int m_used[N];


};




END_NAMESPACE