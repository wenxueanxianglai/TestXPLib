#pragma once

#include "Object.h"
#include "common.h"

BEGIN_NAMESPACE


class XPString : public Object
{
public:
	XPString();
	XPString(const char* s);
	XPString(const XPString& s);
	XPString(char c);
	int length() const;
	const char* str() const;

	~XPString();
	
	XPString& insert(int i, const char* s);
	XPString& insert(int i, const XPString& s);

	bool startWith(const char* s) const;
	bool startWith(const XPString& s) const;

	bool endOf(const char* s) const;
	bool endOf(const XPString& s) const;

	XPString& trim();


	XPString& operator = (const XPString& s);
	XPString& operator = (const char* s);
	XPString& operator = (char s);

	char& operator [](int i);
	char operator[](int i) const;
	 

	bool operator == (const XPString& s) const;
	bool operator == (const char* s) const;

	bool operator != (const XPString& s) const;
	bool operator != (const char* s) const;

	bool operator < (const XPString& s) const;
	bool operator < (const char* s) const;

	bool operator > (const XPString& s) const;
	bool operator > (const char* s) const;

	bool operator <= (const XPString& s) const;
	bool operator <= (const char* s) const;

	bool operator >= (const XPString& s) const;
	bool operator >= (const char* s) const;


	XPString operator + (const XPString& s) const;
	XPString operator + (const char* s) const;
	XPString operator += (const XPString& s);
	XPString operator += (const char* s);


private:
	void init(const char* s);
	bool equal(const char* l, const char* r, int len) const;

private:
	char* m_string;
	int m_length;
};



END_NAMESPACE
