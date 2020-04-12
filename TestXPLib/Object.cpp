#include "Object.h"
#include <cstdlib>
#include <iostream>
using namespace std;

BEGIN_NAMESPACE

void* Object::operator new(unsigned int size) throw()
{
	//cout << "void* Object::operator new(unsigned int size) : " << size << endl;
	return malloc(size);
}

void Object::operator delete(void* p)
{
	//cout << "void Object::operator delete(void* p): " << p << endl;
	free(p);
}

void* Object::operator new[](unsigned int size) throw()
{
	//cout << "void* Object::operator new[](unsigned int size): " << size << endl;
	return malloc(size);
}

void Object::operator delete[](void* p)
{
	//cout << "void Object::operator delete[](void* p): " << p << endl;
	free(p);
}

Object::~Object()
{
}

END_NAMESPACE