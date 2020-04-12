#include <iostream>
#include "SmartPointer.h"
#include "Exception.h"
#include "Object.h"
#include "List.h"
#include "SeqList.h"

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
	
	SeqList<int>* l;
	

	return 0;
}


void testList()
{

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