#pragma once
#include "common.h"
#include "Object.h"
// �쳣
//�����쳣  Artihmetic
//��ָ��	NullPointer
//Խ��		IndexOutOfBounds
//�ڴ治��	NoEnoughMemory
//�������� InvalidParmeter

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

	virtual ~Exception() = 0;		//������������ �Ĺ��̾��� ����˵����ǰ����һ��������
									//�������������� ��Ҫʵ��

private:
	void init(const char* message, const char* file, int line);

private:
	char* m_message;
	char* m_location;

};

//�����쳣  Artihmetic
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

//��ָ��	NullPointer
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

//Խ��		IndexOutOfBounds
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

//�ڴ治��	NoEnoughMemory
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

//�������� InvalidParmeter
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

//��Ա��������ʱ��״̬����ȷ
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