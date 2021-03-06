// Program.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Rational.h"

using namespace std;

BOOST_AUTO_TEST_CASE(IsEqualToZeroByDefault)
{
	CRational r;
	BOOST_CHECK_EQUAL(r.GetNumerator(), 0);
	BOOST_CHECK_EQUAL(r.GetDenominator(), 1);
}

BOOST_AUTO_TEST_CASE(CanBeConstructedFromInteger)
{
	{
		CRational positive(10);
		BOOST_CHECK_EQUAL(positive.GetNumerator(), 10);
		BOOST_CHECK_EQUAL(positive.GetDenominator(), 1);
	}
	{
		CRational negative(-10);
		BOOST_CHECK_EQUAL(negative.GetNumerator(), -10);
		BOOST_CHECK_EQUAL(negative.GetDenominator(), 1);
	}
	{
		CRational zero(0);
		BOOST_CHECK_EQUAL(zero.GetNumerator(), 0);
		BOOST_CHECK_EQUAL(zero.GetDenominator(), 1);
	}
}

BOOST_AUTO_TEST_CASE(CanBeDefinedByNumeratorAndDenominator)
{
	{
		CRational r(5, 2);
		BOOST_CHECK_EQUAL(r.GetNumerator(), 5);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 2);
	}
	{
		CRational r(-5, 2);
		BOOST_CHECK_EQUAL(r.GetNumerator(), -5);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 2);
	}
	{
		CRational r(5, -2);
		BOOST_CHECK_EQUAL(r.GetNumerator(), -5);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 2);
	}
	{
		CRational r(-5, -2);
		BOOST_CHECK_EQUAL(r.GetNumerator(), 5);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 2);
	}
	{
		CRational r(42, 0);
		BOOST_CHECK_EQUAL(r.GetNumerator(), 0);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 1);
	}
}

BOOST_AUTO_TEST_CASE(TestGCD)
{
	BOOST_CHECK_EQUAL(GCD(2, 3), 1u);
	BOOST_CHECK_EQUAL(GCD(3, 2), 1u);
	BOOST_CHECK_EQUAL(GCD(12, 8), 4u);
	BOOST_CHECK_EQUAL(GCD(8, 12), 4u);
	BOOST_CHECK_EQUAL(GCD(0, 2), 2u);
	BOOST_CHECK_EQUAL(GCD(2, 0), 2u);
	BOOST_CHECK_EQUAL(GCD(0, 0), 1u);
}

BOOST_AUTO_TEST_CASE(TestLCM)
{
	BOOST_CHECK_EQUAL(LCM(2, 3), 6u);
	BOOST_CHECK_EQUAL(LCM(3, 2), 6u);
	BOOST_CHECK_EQUAL(LCM(12, 8), 24u);
	BOOST_CHECK_EQUAL(LCM(8, 12), 24u);
	BOOST_CHECK_EQUAL(LCM(0, 2), 0u);
	BOOST_CHECK_EQUAL(LCM(2, 0), 0u);
	BOOST_CHECK_EQUAL(LCM(0, 0), 0u);
}

BOOST_AUTO_TEST_CASE(RationalsAreNormalizedAfterCreation)
{
	{
		CRational r(6, 8);
		BOOST_CHECK_EQUAL(r.GetNumerator(), 3);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 4);
	}
	{
		CRational r(6, -8);
		BOOST_CHECK_EQUAL(r.GetNumerator(), -3);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 4);
	}
	{
		CRational r(-6, 8);
		BOOST_CHECK_EQUAL(r.GetNumerator(), -3);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 4);
	}
	{
		CRational r(-6, -8);
		BOOST_CHECK_EQUAL(r.GetNumerator(), 3);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 4);
	}
	{
		CRational r(-10, 20);
		BOOST_CHECK_EQUAL(r.GetNumerator(), -1);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 2);
	}
}

BOOST_AUTO_TEST_CASE(CanReturnDecimal)
{
	BOOST_CHECK_CLOSE(CRational(3, 5).ToDouble(), 0.6, DBL_EPSILON);
}

BOOST_AUTO_TEST_CASE(TestEquality)
{
	{
		CRational const a(1, 2);
		CRational const b(a);
		BOOST_CHECK(a == b);
		BOOST_CHECK(!(a != b));
	}
	{
		CRational const a(1, 4);
		CRational const b(4, 16);
		BOOST_CHECK(a == b);
		BOOST_CHECK(!(a != b));
	}
	{
		CRational const r(1, 4);
		BOOST_CHECK(!(r == 2));
		BOOST_CHECK(r != 2);
	}
	{
		CRational const r(3);
		BOOST_CHECK(3 == r);
		BOOST_CHECK(!(3 != r));
	}
}

BOOST_AUTO_TEST_CASE(TestUnaryPlus)
{
	{
		CRational const a(3, 5);
		CRational const b(+a);
		BOOST_CHECK(a == b);
	}
	{
		CRational const a(-4, 7);
		CRational const b(+a);
		BOOST_CHECK(a == b);
	}
}

BOOST_AUTO_TEST_CASE(TestUnaryMinus)
{
	BOOST_CHECK(-CRational(3, 5) == CRational(-3, 5));
	BOOST_CHECK(-CRational(4, 7) == CRational(-4, 7));
}

BOOST_AUTO_TEST_CASE(TestBinaryPlus)
{
	BOOST_CHECK(CRational(1, 2) + CRational(1, 6) == CRational(2, 3));
	BOOST_CHECK(CRational(1, 4) + 2 == CRational(9, 4));
	BOOST_CHECK(1 + CRational(1, 2) == CRational(3, 2));
	BOOST_CHECK(CRational(1, 2) + CRational(-1, 3) == CRational(1, 6));
}

BOOST_AUTO_TEST_CASE(TestBinaryMinus)
{
	BOOST_CHECK(CRational(1, 2) - CRational(1, 6) == CRational(1, 3));
	BOOST_CHECK(CRational(1, 2) - 1 == CRational(-1, 2));
	BOOST_CHECK(1 - CRational(1, 2) == CRational(1, 2));
}

BOOST_AUTO_TEST_CASE(TestAssigningAddition)
{
	{
		CRational r(1, 2);
		r += CRational(1, 6);
		BOOST_CHECK(r == CRational(2, 3));
	}
	{
		CRational r(1, 2);
		r += 1;
		BOOST_CHECK(r == CRational(3, 2));
	}
}

BOOST_AUTO_TEST_CASE(TestAssigningSubtraction)
{
	{
		CRational r(1, 2);
		r -= CRational(1, 6);
		BOOST_CHECK(r == CRational(1, 3));
	}
	{
		CRational r(1, 2);
		r -= 1;
		BOOST_CHECK(r == CRational(-1, 2));
	}
}

BOOST_AUTO_TEST_CASE(TestMultiplication)
{
	BOOST_CHECK(CRational(1, 2) * CRational(2, 3) == CRational(1, 3));
	BOOST_CHECK(CRational(1, 2) * -3 == CRational(-3, 2));
	BOOST_CHECK(7 * CRational(2, 3) == CRational(14, 3));
}

BOOST_AUTO_TEST_CASE(TestDivision)
{
	BOOST_CHECK(CRational(1, 2) / CRational(2, 3) == CRational(3, 4));
	BOOST_CHECK(CRational(1, 2) / 5 == CRational(1, 10));
	BOOST_CHECK(7 / CRational(2, 3) == CRational(21, 2));
}

BOOST_AUTO_TEST_CASE(TestAssigningMultiplication)
{
	{
		CRational r(1, 2);
		r *= CRational(2, 3);
		BOOST_CHECK(r == CRational(1, 3));
	}
	{
		CRational r(1, 2);
		r *= 3;
		BOOST_CHECK(r == CRational(3, 2));
	}
}

BOOST_AUTO_TEST_CASE(TestAssigningDivision)
{
	{
		CRational r(1, 2);
		r /= CRational(2, 3);
		BOOST_CHECK(r == CRational(3, 4));
	}
	{
		CRational r(1, 2);
		r /= 3;
		BOOST_CHECK(r == CRational(1, 6));
	}
}

BOOST_AUTO_TEST_CASE(TestComparison)
{
	BOOST_CHECK(CRational(1, 2) >= CRational(1, 3));
	BOOST_CHECK(!(CRational(1, 2) <= CRational(1, 3)));
	BOOST_CHECK(CRational(3, 1) >= 2);
	BOOST_CHECK(CRational(1, 2) < 7);
	BOOST_CHECK(3 <= CRational(7, 2));
	BOOST_CHECK(!(3 >= CRational(8, 2)));
}

BOOST_AUTO_TEST_CASE(TestOutputStream)
{
	{
		ostringstream oss;
		oss << CRational(2, 45);
		BOOST_CHECK_EQUAL(oss.str(), "2/45");
	}
	{
		ostringstream oss;
		oss << CRational(-2, 3);
		BOOST_CHECK_EQUAL(oss.str(), "-2/3");
	}
}

BOOST_AUTO_TEST_CASE(TestInputStream)
{
	{
		istringstream iss("7/15");
		CRational r;
		iss >> r;
		BOOST_CHECK(r == CRational(7, 15));
	}
	{
		istringstream iss("-1/3");
		CRational r;
		iss >> r;
		BOOST_CHECK(r == CRational(-1, 3));
	}
}

BOOST_AUTO_TEST_CASE(TestMixedNumbers)
{
	BOOST_CHECK(CRational(9, 4).ToCompoundFraction() ==
		(pair<int, CRational>(2, CRational(1, 4))));

	BOOST_CHECK(CRational(-9, 4).ToCompoundFraction() ==
		(pair<int, CRational>(-2, CRational(-1, 4))));

	BOOST_CHECK(CRational(33, 11).ToCompoundFraction() ==
		(pair<int, CRational>(3, CRational(0, 1))));

	BOOST_CHECK(CRational(-1, 13).ToCompoundFraction() ==
		(pair<int, CRational>(0, CRational(-1, 13))));

	BOOST_CHECK(CRational(0, 1).ToCompoundFraction() ==
		(pair<int, CRational>(0, CRational(0, 1))));
}
