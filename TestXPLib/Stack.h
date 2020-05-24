#pragma once

#include "common.h"
#include "Object.h"

BEGIN_NAMESPACE

template <typename T>
class Stack : Object
{
public:
	virtual void push(const T& e) = 0;
	virtual void pop() = 0;
	virtual void T top() const = 0;
	virtual void clear() = 0;
	virtual int size() const = 0;

};

END_NAMESPACE