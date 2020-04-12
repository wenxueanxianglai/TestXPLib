#pragma once
#include "common.h"
#include "Object.h"

BEGIN_NAMESPACE

template<typename T>
class List : public Object
{
public:
	virtual bool insert(int i, const T& e) = 0;
	virtual bool remove(int i) = 0;
	
	virtual bool set(int i, const T& e) = 0;
	virtual bool get(int i, T& e) const = 0;

	virtual int length() const = 0;

	virtual void clear() = 0;
};

END_NAMESPACE