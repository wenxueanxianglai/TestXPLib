#pragma once
#include "common.h"

BEGIN_NAMESPACE

class Object			// 规范 堆对象的行为
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