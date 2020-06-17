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
#include "DualLinkList.h"
#include "StaticStack.h"
#include "LinkStack.h"
#include "StaticQueue.h"
#include "LinkQueue.h"
#include "XPString.h"

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

bool isLeft(char ch) {
	return ((ch == '<') || (ch == '(') || (ch == '[') || (ch == '{'));
}

bool isRight(char ch) {
	return ((ch == '>') || (ch == ')') || (ch == ']') || (ch == '}'));
}

bool isQuot(char ch)
{
	return (ch == '\'') || (ch == '\"');
}

bool isMatch(char lch, char rch)
{
	return ((lch == '(') && (rch == ')'))
		|| ((lch == '<') && (rch == '>'))
		|| ((lch == '[') && (rch == ']'))
		|| ((lch == '{') && (rch == '}'))
		|| ((lch == '\'') && (rch == '\''))
		|| ((lch == '\"') && (rch == '\"'));
}

bool scan(const char* code) {
	LinkStack<char> stack;
	int i = 0;
	bool ret = true;

	code = (code == nullptr) ? "" : code;

	while (ret && code[i] != '\0')
	{
		if (isLeft(code[i]))
		{
			stack.push(code[i]);
		}
		if (isRight(code[i]))
		{
			if ((stack.size() > 0) && isMatch(stack.top(), code[i]))
			{
				stack.pop();
			}
			else
			{
				ret = false;
			}
		}
		else if (isQuot(code[i]))
		{
			if ((stack.size() == 0) || !(isMatch(stack.top(), code[i])))
			{
				stack.push(code[i]);
			}
			else if (isMatch(stack.top(), code[i]))
			{
				stack.pop();
			}
		}

		++i;
	}

	return ret && (stack.size() == 0);
}

int* make_pmt(const char* p)
{
	int len = strlen(p);
	int* ret = static_cast<int*>(malloc(sizeof(int)* len));

	if (ret != nullptr)
	{
		int ll = 0;

		ret[0] = 0;

		for (int i = 1; i < len; ++i)
		{
			while( (p[ll] != p[i] ) && (ll > 0) )
			{
				ll = ret[ll - 1];
			}

			if (p[ll] == p[i])
			{
				ll++;
			}

			ret[i] = ll;
		}
	}

	return ret;
}

int kmp(const char* s, const char* p)
{
	int ret = -1;
	int sl = strlen(s);
	int pl = strlen(p);
	int* pmt = make_pmt(p);


	if ((pmt != nullptr) && (0 < pl) && (pl <= sl))
	{
		for (int i=0, j = 0; i< sl; ++i)
		{
			while ((j > 0) && (s[i] != p[j]))
			{
				j = pmt[j - 1];
			}

			if (s[i] == p[j])
			{
				j++;
			}

			if (j == pl)
			{
				ret = i + 1 - pl;
				break;
			}
		}

	}

	free(pmt);

	return ret;
}

int main()
{
	int * pmt = make_pmt("ababax");

	for (int i = 0; i < strlen("ababax"); ++i)
	{
		cout << i << " : " << pmt[i] << endl;
	}
	

	return 0;
}

void testMyString()
{
	XPString s;

	s = '  D';

	cout << s.str() << endl;
	cout << s.length() << endl;
	cout << (s == "D") << endl;

	s += " zhang xiao pin";

	cout << s.str() << endl;
	cout << s.length() << endl;
	cout << (s == "D zhang xiao pin") << endl;


	cout << "-------------------------------\n";

	for (int i = 0; i < s.length(); ++i)
	{
		cout << s[i] << endl;
	}

	cout << "-------------------------------\n";
	cout << s.startWith("D ") << endl;
	cout << s.endOf("pin") << endl;


	cout << "-------------------------------\n";
	s.trim().insert(0, "XIAO");
	cout << s.str() << endl;

}

void testLinkQueue()
{
	LinkQueue<int> queue;
	for (int i = 0; i < 5; ++i)
	{
		queue.add(i);
	}

	while (queue.length() > 0)
	{
		cout << queue.front() << endl;
		queue.remove();
	}


}

void testStaticQueue()
{
	StaticQueue<int, 5> queue;
	for (int i = 0; i < 5; ++i)
	{
		queue.add(i);
	}

	while (queue.length() > 0)
	{
		cout << queue.front() << endl;
		queue.remove();
	}

}

void testLinkStack()
{
	LinkStack<int> stack;

	for (int i = 0; i < 5; ++i)
	{
		stack.push(i);
	}

	while (stack.size() > 0)
	{
		cout << stack.top() << endl;
		stack.pop();

	}
}

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


void testDualLinkList()
{
	DualLinkList<int> lst;
	for (int i = 0; i < 5; ++i)
	{
		lst.insert(0, i);
		lst.insert(0, 5);
	}

	for (int i = 0; i < lst.length(); ++i)
	{
		cout << lst.get(i) << endl;
	}


	for (lst.move(lst.length() - 1); !lst.end(); lst.pre())
	{
		cout << lst.current() << endl;
	}

	cout << "begin--------" << endl;

	lst.move(lst.length() - 1);
	while (!lst.end())
	{
		if (lst.current() == 5)
		{
			cout << lst.current() << endl;
			lst.remove(lst.find(lst.current()));
		}
		else
		{
			lst.pre();
		}
	}

	cout << "end----------" << endl;
	for (lst.move(lst.length() - 1); !lst.end(); lst.pre())
	{
		cout << lst.current() << endl;
	}
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