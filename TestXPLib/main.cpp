#include <iostream>
#include "SmartPointer.h"
#include "Exception.h"
#include "Object.h"
#include "List.h"
#include "SeqList.h"
#include "StaticList.h"
#include "DynamicList.h"

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

	int j;
	int i;

};


void testPointer();


int main()
{

	//testPointer();

	//Object* obj1 = new Test();

	//delete obj1;

	//SeqList<int>* l;


	return 0;
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