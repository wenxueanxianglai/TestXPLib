#include "Exception.h"
#include <cstring>
#include <cstdlib>
#include <string.h>

BEGIN_NAMESPACE

Exception::Exception(const char* message)
{
	init(message, nullptr, 0);
}

Exception::Exception(const char* file, int line)
{
	init(nullptr, file, line);
}

Exception::Exception(const char* message, const char* file, int line)
{
	init(message, file, line);
}

Exception::Exception(const Exception& e)
{
	m_message = _strdup(e.m_message);
	m_location = _strdup(e.m_location);
}

XPLib::Exception::Exception() : Exception(nullptr)
{

}

const char* Exception::message() const
{
	return m_message;
}

const char* Exception::location() const
{
	return m_location;
}

Exception::~Exception()
{
	free(m_message);
	free(m_location);
}

Exception& Exception::operator=(const Exception& e)
{
	if (this  != &e)
	{
		free(m_message);
		free(m_location);
		
		m_message = _strdup(e.m_message);
		m_location = _strdup(e.m_location);
	}

	return *this;
}

void Exception::init(const char* message, const char* file, int line)
{
	m_message = _strdup(message);

	if (nullptr != file)
	{
		char sl[16]{ 0 };
		_itoa_s(line, sl, 10);
		m_location = static_cast<char*>(malloc(strlen(file) + strlen(sl) + 2));
		if (m_location != nullptr)
		{
			m_location = strcpy(m_location, file);
			m_location = strcat(m_location, ":");
			m_location = strcat(m_location, sl);
		}
		else
		{
			//这里最好这样，原因  这是Exception类，是Exception的父类，不管抛出什么异常都会再次运行得到这个函数
		}


	}
	else
	{
		m_location = nullptr;
	}
}

END_NAMESPACE