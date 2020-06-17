#include "XPString.h"
#include "Exception.h"
#include <cstring>
#include <cstdlib>
#include <string.h>


BEGIN_NAMESPACE

XPString::XPString()
{
	init("");
}

XPString::XPString(const char * s)
{
	init(s ? s : "");
}

XPString::XPString(const XPString & s)
{
	init(s.m_string);
}

XPString::XPString(char c)
{
	char s[] = { c, '\0' };
	init(s);
}

int XPString::length() const
{
	return m_length;
}

const char * XPString::str() const
{
	return m_string;
}

XPString::~XPString()
{
	free(m_string);

}

XPString & XPString::insert(int i, const char * s)
{
	if ((0 <= i) && (i <= m_length))
	{
		if ( (nullptr != s) && ('\0' != s[0]))
		{
			int len = strlen(s);
			char* str = reinterpret_cast<char*>(malloc(m_length + len + 1));
			if (nullptr != str)
			{
				strncpy(str, m_string, i);
				strncpy(str + i, s, len);
				strncpy(str + i + len, m_string + i, m_length - i);
				str[m_length + len] = '\0';

				free(m_string);
				m_string = str;

				m_length = m_length + len;
			}
			else
			{
				THROW_EXCEPTION(NoEnoughMemoryException, "Nomemory to insert string value...");
			}
		}
	}
	else
	{
		THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invvalid...");
	}

	return *this;
}

XPString & XPString::insert(int i, const XPString & s)
{
	return insert(i, s.m_string);
}

void XPString::init(const char * s)
{
	m_string = _strdup(s);

	if (m_string)
	{
		m_length = strlen(m_string);
	}
	else
	{
		THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create String Object");
	}
}

bool XPString::equal(const char * l, const char * r, int len) const
{
	bool ret = true;

	for (int i = 0; i< len && ret; ++i)
	{
		ret = ret && (l[i] == r[i]);
	}

	return ret;
}

bool XPString::startWith(const char * s) const
{
	bool ret = (nullptr != s);

	if (ret)
	{
		int len = strlen(s);

		ret = (len < m_length) && equal(m_string, s, len);
	}

	return ret;
}

bool XPString::startWith(const XPString & s) const
{
	return startWith(s.m_string);
}

bool XPString::endOf(const char * s) const
{
	bool ret = (nullptr != s);
	
	if (ret)
	{
		int len = strlen(s);
		char* str = m_string + (m_length - len);	//获取最后的指针下标

		ret = (len < m_length) && equal(str, s, len);
	}

	return ret;
}

bool XPString::endOf(const XPString & s) const
{
	return endOf(s.m_string);
}

XPString & XPString::trim()
{
	int b = 0;
	int e = m_length - 1;

	while (m_string[b] == ' ') ++b;
	while (m_string[e] == ' ') --e;

	if (b == 0)
	{
		m_string[e + 1] = '\0';
		m_length = e + 1;
	}
	else
	{
		for (int i = 0, j = b; j <= e; i++, j++)
		{
			m_string[i] = m_string[j];
		}

		m_string[e - b + 1] = '\0';
		m_length = e - b + 1;

	}


	return *this;
}

XPString & XPString::operator=(const XPString & s)
{
	return (*this = s.m_string);
}

XPString & XPString::operator=(const char * s)
{
	if (m_string != s)
	{
		char* str = _strdup(s ? s : "");
		if (str)
		{
			free(m_string);
			m_string = str;
			m_length = strlen(m_string);
		}
		else
		{
			THROW_EXCEPTION(NoEnoughMemoryException, "");
		}
	}

	return *this;
}

XPString & XPString::operator=(char c)
{
	char s[] = { c, '\0' };

	return (*this = s);
}

char & XPString::operator[](int i)
{
	if ((0 <= i) && (i < m_length))
	{
		return m_string[i];
	}
	else
	{
		THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invvalid...");
	}
}

char XPString::operator[](int i) const
{
	return (const_cast<XPString&>(*this))[i];
}

bool XPString::operator==(const XPString & s) const
{
	return (strcmp(m_string, s.m_string) == 0);
}

bool XPString::operator==(const char * s) const
{
	return (strcmp(m_string, s ? s : "") == 0);
}

bool XPString::operator!=(const XPString & s) const
{
	return !(*this == s);
}

bool XPString::operator!=(const char * s) const
{
	return !(*this == s);
}

bool XPString::operator<(const XPString & s) const
{
	return (strcmp(m_string, s.m_string) < 0);
}

bool XPString::operator<(const char * s) const
{
	return (strcmp(m_string, s ? s : "") < 0);
}

bool XPString::operator>(const XPString & s) const
{
	return (strcmp(m_string, s.m_string) > 0);
}

bool XPString::operator>(const char * s) const
{
	return (strcmp(m_string, s ? s : "") > 0);
}

bool XPString::operator<=(const XPString & s) const
{
	return (strcmp(m_string, s.m_string) <= 0);
}

bool XPString::operator<=(const char * s) const
{
	return (strcmp(m_string, s ? s : "") <= 0);
}

bool XPString::operator>=(const XPString & s) const
{
	return (strcmp(m_string, s.m_string) >= 0);
}

bool XPString::operator>=(const char * s) const
{
	return (strcmp(m_string, s ? s : "") >= 0);
}

XPString XPString::operator+(const XPString & s) const
{
	return(*this + s.m_string);
}

XPString XPString::operator+(const char * s) const
{
	XPString ret;
	int len = m_length + strlen(s ? s : "");
	char* str = reinterpret_cast<char*>(malloc(len + 1));

	if (str)
	{
		strcpy(str, m_string);
		strcat(str, s ? s : "");

		free(ret.m_string);

		ret.m_string = str;
		ret.m_length = len;
	}
	else
	{
		THROW_EXCEPTION(NoEnoughMemoryException, "No memory to add String values...");
	}

	return ret;
}

XPString XPString::operator+=(const XPString & s)
{
	return (*this = *this + s);
}

XPString XPString::operator+=(const char * s) 
{
	return (*this = *this + s);
}


END_NAMESPACE