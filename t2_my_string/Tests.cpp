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

BOOST_AUTO_TEST_CASE(StringCanBeCreatedByStlString)
{
	string testStr("str1");
	testStr.push_back('\0');
	testStr += "str2";

	CMyString s(testStr);

	BOOST_CHECK_EQUAL(s.GetLength(), 9);
	BOOST_CHECK(memcmp(s.GetStringData(), testStr.c_str(), 10) == 0);
}

BOOST_AUTO_TEST_CASE(TestStringEquality)
{
	BOOST_CHECK(CMyString() == CMyString());
	BOOST_CHECK(CMyString("test") == CMyString("test"));
	BOOST_CHECK(CMyString("test1") != CMyString("test2"));
}

BOOST_AUTO_TEST_CASE(TestSubstringGeneration)
{
	BOOST_CHECK(CMyString("abcde").SubString(2) == CMyString("cde"));
	BOOST_CHECK(CMyString("abcde").SubString(0, 0) == CMyString());
	BOOST_CHECK(CMyString("abcde").SubString(4) == CMyString("e"));
	BOOST_CHECK(CMyString("abcde").SubString(0) == CMyString("abcde"));
	BOOST_CHECK(CMyString("abcde").SubString(1, 2) == CMyString("bc"));
}

BOOST_AUTO_TEST_CASE(TestClearString)
{
	CMyString a("test");
	a.Clear();
	BOOST_CHECK_EQUAL(a.GetLength(), 0);
}

BOOST_AUTO_TEST_CASE(TestAssigningConcatenation)
{
	{
		CMyString s("abc");
		s += "def";
		BOOST_CHECK(s == "abcdef");
	}
	{
		CMyString s("abc");
		s += "";
		BOOST_CHECK(s == "abc");
	}
	{
		CMyString s;
		s += "def";
		BOOST_CHECK(s == "def");
	}
}

BOOST_AUTO_TEST_CASE(TestConcatenation)
{
	BOOST_CHECK(CMyString("abc") + CMyString("def") == CMyString("abcdef"));
	BOOST_CHECK("abc" + CMyString("def") == CMyString("abcdef"));
	BOOST_CHECK(string("abc") + CMyString("def") == CMyString("abcdef"));
}

BOOST_AUTO_TEST_CASE(TestStringComparison)
{
	BOOST_CHECK(CMyString("abc") < CMyString("abd"));
	BOOST_CHECK(CMyString("abcd") >= CMyString("abc"));
	BOOST_CHECK(CMyString("abc") > CMyString());
	BOOST_CHECK(CMyString("abc") <= CMyString("abcd"));
}

BOOST_AUTO_TEST_CASE(TestReadStringFromStream)
{
	istringstream iss("test string");
	CMyString s;
	iss >> s;
	BOOST_CHECK(s == "test string");
}

BOOST_AUTO_TEST_CASE(TestWriteStringToStream)
{
	ostringstream oss;
	oss << CMyString("test string");
	BOOST_CHECK(oss.str() == "test string");
}

struct ConstIteratorFixture
{
	CMyString const str;
	CMyString::CConstIterator it;

	ConstIteratorFixture()
		:str("test string")
		,it(str.begin())
	{}

	ConstIteratorFixture& operator=(ConstIteratorFixture const& other) = delete;
};

BOOST_FIXTURE_TEST_SUITE(ConstIterator, ConstIteratorFixture)

BOOST_AUTO_TEST_CASE(TestConstIteratorEquality)
{
	{
		CMyString::CConstIterator it2(it);
		BOOST_CHECK(it == it2);
		BOOST_CHECK(!(it != it2));
	}
	{
		CMyString::CConstIterator empty;
		BOOST_CHECK(it != empty);
		BOOST_CHECK(!(it == empty));
	}
}

BOOST_AUTO_TEST_CASE(TestConstIteratorDereference)
{
	BOOST_CHECK_EQUAL(*it, 't');
}

BOOST_AUTO_TEST_CASE(TestConstIteratorPredIncrement)
{
	auto retIt = ++it;
	BOOST_CHECK_EQUAL(*retIt, 'e');
	BOOST_CHECK_EQUAL(*it, 'e');
}

BOOST_AUTO_TEST_CASE(TestConstIteratorPostIncrement)
{
	auto oldIt = it++;
	BOOST_CHECK_EQUAL(*oldIt, 't');
	BOOST_CHECK_EQUAL(*it, 'e');
}

BOOST_AUTO_TEST_CASE(TestConstIteratorPredDecrement)
{
	++it;

	auto retIt = --it;
	BOOST_CHECK_EQUAL(*retIt, 't');
	BOOST_CHECK_EQUAL(*it, 't');
}

BOOST_AUTO_TEST_CASE(TestConstIteratorPostDecrement)
{
	++it;

	auto oldIt = it--;
	BOOST_CHECK_EQUAL(*oldIt, 'e');
	BOOST_CHECK_EQUAL(*it, 't');
}

BOOST_AUTO_TEST_CASE(TestConstIteratorAddition)
{
	BOOST_CHECK_EQUAL(*(it + 4), ' ');
	BOOST_CHECK_EQUAL(*((-1) + (it + 2)), 'e');
	BOOST_CHECK((it + 0) == it);

	it += 7;
	BOOST_CHECK_EQUAL(*it, 'r');
}

BOOST_AUTO_TEST_CASE(TestConstIteratorSubtraction)
{
	it = str.end();
	--it;

	BOOST_CHECK_EQUAL(*(it - 2), 'i');
	BOOST_CHECK_EQUAL(*((it - 5) - (-2)), 'r');
	BOOST_CHECK((it - 0) == it);
	
	BOOST_CHECK_EQUAL((it - 2) - (it - 5), 3);
	BOOST_CHECK_EQUAL((it - 5) - (it - 2), -3);

	it -= 6;
	BOOST_CHECK_EQUAL(*it, ' ');
}

BOOST_AUTO_TEST_CASE(TestConstIteratorComarison)
{
	BOOST_CHECK(it < it + 3);
	BOOST_CHECK(!(it >= it + 3));

	BOOST_CHECK(it <= it + 1);
	BOOST_CHECK(!(it > it + 1));

	BOOST_CHECK(it + 6 > it + 5);
	BOOST_CHECK(!(it + 6 <= it + 5));

	BOOST_CHECK(it + 2 >= it);
	BOOST_CHECK(!(it + 2 < it));

	BOOST_CHECK(it >= it);
	BOOST_CHECK(it <= it);
	BOOST_CHECK(!(it > it));
	BOOST_CHECK(!(it < it));
}

BOOST_AUTO_TEST_CASE(TestConstIteratorOffsetDereference)
{
	BOOST_CHECK_EQUAL(it[2], 's');
	BOOST_CHECK_EQUAL(it[4], ' ');
	BOOST_CHECK_EQUAL(it[0], 't');
	BOOST_CHECK_EQUAL((it + 10)[-3], 'r');
}

BOOST_AUTO_TEST_SUITE_END()
