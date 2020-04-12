#pragma once
#include "common.h"

BEGIN_NAMESPACE

class Object			// �淶 �Ѷ������Ϊ
{
public:
//	Object();

	void* operator new(unsigned int size) throw();
	void operator delete(void* p);

	void* operator new[](unsigned int size) throw();
	void operator delete[](void* p);

	virtual ~Object() = 0;
};

END_NAMESPACE