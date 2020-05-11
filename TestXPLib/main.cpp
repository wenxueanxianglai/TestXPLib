#include <iostream>
#include "SmartPointer.h"
#include "Exception.h"
#include "Object.h"
#include "List.h"
#include "SeqList.h"
#include "StaticList.h"
#include "DynamicList.h"
#include "StaticArray.h"
#include "DynamicArray.h"
#include "LinkList.h"
#include "StaticLinkList.h"
#include "SharedPointer.h"
#include "CircleList.h"

using namespace XPLib;
using namespace std;

class Test : public Object
{
	
public:
	Test() {
		cout << "Test::Test()" << endl;
	}
	~Test() {
		cout << "Test::~Test()" << endl;
	}

	bool operator == (const Test& t) {
		return i == t.i;
	}

	int value{ 0 };

	int j;
	int i;

};


void testPointer();

void josephus(int n, int s, int m)
{
	CircleList<int> lst;
	for (int i = 1; i <= n; i++)
	{
		lst.insert(i);
	}

	lst.move(s - 1, m - 1);

	while (lst.length() > 0)
	{
		lst.next();

		cout << lst.current() << endl;

		lst.remove(lst.find(lst.current()));

	}
}


int main()
{
	josephus(41, 1, 3);
	
	//lst.last();
	//StaticLinkList<int, 8> list;

	//for (int i = 0; i < 5; ++i)
	//{
	//	list.insert(i);
	//}

	//for (list.move(0, 2); !list.end(); list.next())
	//{
	//	cout << list.current() << endl;
	//}
	
	return 0;
}

void testSharedPointer()
{
	SharedPointer<Test> sp = new Test();

	SharedPointer<Test> sp1 = sp;
	SharedPointer<Test> sp2 = nullptr;

	sp2 = sp;

	sp2->value = 100;
	cout << sp->value << endl;
	cout << sp1->value << endl;
	cout << sp2->value << endl;

	cout << (sp == sp2) << endl;

}

void testfind()
{
	LinkList<int> list;
	for (int i = 0; i < 5; ++i)
	{
		list.insert(i);

	}

	cout << list.find(3) << endl;
	cout << list.find(8) << endl;
}



void testLinkList()
{

	
	LinkList<int> list;

	for (int i = 0; i < 5; ++i)
	{
		list.insert(i);
		list.set(i, i*i);
	}

	for (int i = 0; i < list.length(); ++i)
	{
		//int v = 0;
		//list.get(i, v);

		cout << list.get(i) << endl;
	}

	list.remove(2);

	for (int i = 0; i < list.length(); ++i)
	{
		cout << list.get(i) << endl;
	}

}


void testDynamicArray()
{
	DynamicArray<int> sl(5);

	for (int i = 0; i < sl.length(); ++i)
	{
		sl[i] = i * i;
	}

	for (int i = 0; i < sl.length(); ++i)
	{
		cout << sl[i] << endl;
	}

	DynamicArray<int> s2(10);
	s2 = sl;
	s2.resize(8);
	s2.resize(3);
	for (int i = 0; i < s2.length(); ++i)
	{
		cout << s2[i] << endl;
	}

	s2[4] = 11;
}

void testArray()
{
	StaticArray<int, 5> sl;

	for (int i = 0; i < sl.length(); ++i)
	{
		sl[i] = i * i;
	}

	for (int i = 0; i < sl.length(); ++i)
	{
		cout << sl[i] << endl;
	}

	StaticArray<int, 5> s2;
	s2 = sl;
	for (int i = 0; i < sl.length(); ++i)
	{
		cout << s2[i] << endl;
	}

	s2[6] = 222;

}

void testDynamicList()
{

	// 实例化
	DynamicList<int> l(5);

	// 增
	for (int i = 0; i < l.capacity(); i++)
	{
		l.insert(0, i);
	}

	// 查
	for (int i = 0; i < l.length(); ++i)
	{
		cout << l[i] << endl;
	}

	l[0] *= l[0];

	cout << "--------------------------------------------------" << endl;
	for (int i = 0; i < l.length(); ++i)
	{
		cout << l[i] << endl;
	}

	try
	{
		l[5] = 5;
	}
	catch (const Exception& e)
	{
		cout << e.message() << endl;
		cout << e.location() << endl;

		l.resize(10);
		l.insert(5, 333);
	}
	cout << "--------------------------------------------------" << endl;
	for (int i = 0; i < l.length(); ++i)
	{
		cout << l[i] << endl;
	}


	l.resize(3);
	cout << "--------------------------------------------------" << endl;
	for (int i = 0; i < l.length(); ++i)
	{
		cout << l[i] << endl;
	}



	//DynamicList<int> l(5);
	//for (int i = 0; i < l.capacity(); i++)
	//{
	//	l.insert(i);
	//}

	//for (int i = 0; i < l.capacity(); i++)
	//{
	//	cout << l[i] << endl;
	//}
}

void testStaticList()
{
	StaticList<int, 5> l;

	// 增
	for (int i = 0; i < l.capacity(); i++)
	{
		l.insert(0, i);
	}

	// 查
	for (int i = 0; i < l.length(); ++i)
	{
		cout << l[i] << endl;
	}

	l[0] *= l[0];

	cout << "--------------------------------------------------" << endl;
	for (int i = 0; i < l.length(); ++i)
	{
		cout << l[i] << endl;
	}

	try
	{
		l[5] = 5;
	}
	catch (const Exception& e)
	{
		cout << e.message() << endl;
		cout << e.location() << endl;
	}
}

void testPointer()
{
	CSmartPointer<int>* mp = new CSmartPointer<int>;

	auto dd = mp;

	cout << mp->isNull() << endl;
	cout << dd->isNull() << endl;

	CSmartPointer<Test> pTest = new Test();
}

void testException()
{
	InvalidOperationException* pe = new InvalidOperationException();

	try
	{
		THROW_EXCEPTION(NullPointerException, "test");
	}
	catch (const ArtihmeticException& e)
	{
		cout << "catch (const ArtihmeticException& e)" << endl;
		cout << e.message() << endl;
		cout << e.location() << endl;
	}
	catch (const NullPointerException& e)
	{
		cout << "catch (const NullPointerException& e)" << endl;
		cout << e.message() << endl;
		cout << e.location() << endl;
	}

	catch (const Exception& e)
	{
		cout << "catch (const Exception& e)" << endl;
		cout << e.message() << endl;
		cout << e.location() << endl;
	}
}