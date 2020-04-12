#pragma once
#include "common.h"
#include "Object.h"
// 异常
//计算异常  Artihmetic
//空指针	NullPointer
//越界		IndexOutOfBounds
//内存不足	NoEnoughMemory
//参数错误 InvalidParmeter

//#define THROW_EXCEPTION(e, m) (throw e(m, __FILE__, __LINE__))

BEGIN_NAMESPACE
 
class Exception : public Object
{
public:
	Exception();
	Exception(const char* message);
	Exception(const char* file, int line);
	Exception(const char* message, const char* file, int line);

	Exception(const Exception& e);
	Exception& operator= (const Exception& e);

	virtual const char* message() const;
	virtual const char* location() const;

	virtual ~Exception() = 0;		//纯虚析构函数 的工程经验 仅仅说明当前类是一个抽象类
									//纯虚析构函数， 都要实现

private:
	void init(const char* message, const char* file, int line);

private:
	char* m_message;
	char* m_location;

};

//计算异常  Artihmetic
class ArtihmeticException : public Exception
{
public:
	ArtihmeticException() : Exception(nullptr) {}
	ArtihmeticException(const char* message) : Exception(message) {}
	ArtihmeticException(const char* file, int line) : Exception(file, line) {}
	ArtihmeticException(const char* message, const char* file, int line) : Exception(message, file, line) {}

	ArtihmeticException(const ArtihmeticException& e) : Exception(e) {}
	ArtihmeticException& operator = (const ArtihmeticException& e) 
	{
		Exception::operator=(e);

		return *this;
	}
};

//空指针	NullPointer
class NullPointerException : public Exception
{
public:
	using Exception::Exception;

	NullPointerException& operator= (const NullPointerException& e)
	{
		Exception::operator=(e);

		return *this;
	}
};

//越界		IndexOutOfBounds
class IndexOutOfBoundsException : public Exception
{
public:
	using Exception::Exception;

	IndexOutOfBoundsException& operator= (const IndexOutOfBoundsException& e)
	{
		Exception::operator=(e);

		return *this;
	}
};

//内存不足	NoEnoughMemory
class NoEnoughMemoryException : public Exception
{
public:
	using Exception::Exception;

	NoEnoughMemoryException& operator= (const NoEnoughMemoryException& e)
	{
		Exception::operator=(e);

		return *this;
	}
};

//参数错误 InvalidParmeter
class InvalidParmeterException : public Exception
{
public:
	using Exception::Exception;

	InvalidParmeterException& operator= (const InvalidParmeterException& e)
	{
		Exception::operator=(e);

		return *this;
	}
};

//成员函数调用时，状态不正确
class InvalidOperationException : public Exception
{
	using Exception::Exception;

	InvalidOperationException& operator= (const InvalidOperationException& e)
	{
		Exception::operator=(e);

		return *this;
	}
};


END_NAMESPACE