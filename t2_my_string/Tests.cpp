#include "stdafx.h"
#include "DynamicArray.h"
#include "MyString.h"

using namespace std;

BOOST_AUTO_TEST_CASE(CreateEmptyDynamicArray)
{
	CDynamicArray a;
	BOOST_CHECK_EQUAL(a.GetSize(), 0);
}

BOOST_AUTO_TEST_CASE(DynamicArrayBasicUsage)
{
	CDynamicArray a(4);
	BOOST_CHECK_EQUAL(a.GetSize(), 4);

	a[0] = 'a';
	a[1] = 'b';
	a[2] = 'c';
	a[3] = 'd';

	BOOST_CHECK_EQUAL(a[0], 'a');
	BOOST_CHECK_EQUAL(a[1], 'b');
	BOOST_CHECK_EQUAL(a[2], 'c');
	BOOST_CHECK_EQUAL(a[3], 'd');
}

BOOST_AUTO_TEST_CASE(TestDynamicArrayEquality)
{
	{
		CDynamicArray a(2);
		a[0] = 'a';
		a[1] = 'b';

		CDynamicArray b(2);
		b[0] = 'a';
		b[1] = 'b';

		BOOST_CHECK(a == b);
	}
	{
		CDynamicArray a(2);
		a[0] = 'a';
		a[1] = 'b';

		CDynamicArray b(2);
		b[0] = 'a';
		b[1] = 'c';

		BOOST_CHECK(a != b);
	}
	{
		CDynamicArray a(2);
		a[0] = 'a';
		a[1] = 'b';

		CDynamicArray b(3);
		b[0] = 'a';
		b[1] = 'b';
		b[2] = 'c';

		BOOST_CHECK(a != b);
	}
	BOOST_CHECK(CDynamicArray() == CDynamicArray());
}

BOOST_AUTO_TEST_CASE(DynamicArrayCanBeCopied)
{
	CDynamicArray a(2);
	a[0] = 'a';
	a[1] = 'b';

	CDynamicArray b(a);
	BOOST_CHECK(a == b);
}

BOOST_AUTO_TEST_CASE(DynamicArrayCanBeMoved)
{
	CDynamicArray a(2);
	a[0] = 'a';
	a[1] = 'b';

	CDynamicArray b(a);
	CDynamicArray c(move(b));

	BOOST_CHECK_EQUAL(b.GetSize(), 0);
	BOOST_CHECK(a == c);
}

BOOST_AUTO_TEST_CASE(TestDynamicArrayCopyAssignment)
{
	CDynamicArray a(2);
	a[0] = 'a';
	a[1] = 'b';

	CDynamicArray b(1);
	b[0] = 'c';

	b = a;
	BOOST_CHECK(a == b);
}

BOOST_AUTO_TEST_CASE(TestDynamicArrayMoveAssignment)
{
	CDynamicArray a(2);
	a[0] = 'a';
	a[1] = 'b';

	CDynamicArray b(a);

	CDynamicArray c(1);
	c[0] = 'c';

	c = move(b);

	BOOST_CHECK_EQUAL(b.GetSize(), 0);
	BOOST_CHECK(a == c);
}

BOOST_AUTO_TEST_CASE(TestDynamicArraySelfAssignment)
{
	CDynamicArray a(2);
	a[0] = 'a';
	a[1] = 'b';

	CDynamicArray b(a);

	b = b;
	BOOST_CHECK(a == b);

	b = move(b);
	BOOST_CHECK(a == b);
}

BOOST_AUTO_TEST_CASE(CanCreateEmptyString)
{
	CMyString s;
	BOOST_CHECK_EQUAL(s.GetLength(), 0);
	BOOST_CHECK_EQUAL(strlen(s.GetStringData()), 0);
}

BOOST_AUTO_TEST_CASE(StringCanBeCreatedByPString)
{
	char const* testStr = "test string";
	CMyString s(testStr);

	BOOST_CHECK_EQUAL(s.GetLength(), 11);
	BOOST_CHECK(strcmp(s.GetStringData(), testStr) == 0);
}

BOOST_AUTO_TEST_CASE(StringCanBeCreatedByPStringWithLength)
{
	char const* testStr = "str1\0str2";
	CMyString s(testStr, 9);

	BOOST_CHECK_EQUAL(s.GetLength(), 9);
	BOOST_CHECK(memcmp(s.GetStringData(), testStr, 10) == 0);
}
