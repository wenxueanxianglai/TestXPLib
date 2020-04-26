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


	bool operator == (const Object& object);
	bool operator != (const Object& object);
	virtual ~Object() = 0;
};

END_NAMESPACE