#include <pch.hpp>
#include <Util/Time.hpp>

template class ::xrn::util::BasicTime<double>;

#include <boost/test/unit_test.hpp>
BOOST_AUTO_TEST_SUITE(xrn)
BOOST_AUTO_TEST_SUITE(util)
BOOST_AUTO_TEST_SUITE(TimeTests)

BOOST_AUTO_TEST_CASE(Basic)
{
    using ::xrn::util::literal::operator""_ns;
    auto t1{ ::xrn::Time::createAsSeconds(0.1) };
    auto t2{ t1.getAsMilliseconds() }; // 100ms
    ::xrn::Time t3{ 30 };
    auto t4{ t3.getAsMicroseconds() }; // 30000ms
    auto t5{ ::xrn::Time::createAsNanoseconds(-800000) }; // -0.8
    auto t6{ t5.getAsSeconds() }; // -0.0008ms
    auto t7{ t1 + ::xrn::Time::createAsSeconds(t6) }; // 99.2ms
    auto t8{ t1 + -800000_ns }; // 99.2ms
    auto t9{ t1 + t5 }; // 99.2ms
    auto t10{ t1 + 55 }; // 155ms
    auto t11{ 55 + t1 }; // 155ms

    BOOST_TEST((t1 == 100));
    BOOST_TEST((t2 == 100));
    BOOST_TEST((t3 == 30));
    BOOST_TEST((t4 == 30000));
    BOOST_TEST((t5 == -0.8));
    BOOST_TEST((t6 == -0.0008));
    BOOST_TEST((t7 == 99.2));
    BOOST_TEST((t8 == 99.2));
    BOOST_TEST((t9 == 99.2));
    BOOST_TEST((t10 == 155));
    BOOST_TEST((t11 == 155));
}

BOOST_AUTO_TEST_CASE(Creates)
{
    auto t1{ ::xrn::Time::createAsSeconds(30) };
    auto t2{ ::xrn::Time::createAsMilliseconds(30) };
    auto t3{ ::xrn::Time::createAsMicroseconds(30) };
    auto t4{ ::xrn::Time::createAsNanoseconds(30) };

    BOOST_TEST((t1 == 30000));
    BOOST_TEST((t2 == 30));
    BOOST_TEST((t3 == 0.03));
    BOOST_TEST((t4 == 0.00003));
}

BOOST_AUTO_TEST_CASE(Compares)
{
    auto t1{ ::xrn::Time::createAsSeconds(30) };
    auto t2{ ::xrn::Time::createAsMilliseconds(30000) };
    auto t3{ ::xrn::Time::createAsMicroseconds(30000000) };
    auto t4{ ::xrn::Time::createAsNanoseconds(30000000000) };
    auto t5{ ::xrn::Time::createAsNanoseconds(20000000000) };
    auto t6{ 30000 };

    BOOST_TEST((t1 == t2));
    BOOST_TEST((t1 == t3));
    BOOST_TEST((t1 == t4));
    BOOST_TEST((t1 >= t5));
    BOOST_TEST((t1 > t5));
    BOOST_TEST((t5 <= t1));
    BOOST_TEST((t5 < t1));
    BOOST_TEST((t5 != t1));

    BOOST_TEST((t1 == t6));
    BOOST_TEST((t6 >= t5));
    BOOST_TEST((t6 > t5));
    BOOST_TEST((t5 <= t6));
    BOOST_TEST((t5 < t6));
    BOOST_TEST((t5 != t6));
}

BOOST_AUTO_TEST_CASE(GettersSetters)
{
    auto t1{ ::xrn::Time::createAsSeconds(30) };
    BOOST_TEST((t1 == 30000));
    BOOST_TEST((t1.get() == 30000));
    BOOST_TEST((static_cast<double>(t1) == 30000));
    BOOST_TEST((t1.getAsSeconds() == 30));
    BOOST_TEST((t1.getAsMilliseconds() == 30000));
    BOOST_TEST((t1.getAsMicroseconds() == 30000000));
    BOOST_TEST((t1.getAsNanoseconds() == 30000000000));

    t1 = ::xrn::Time::createAsSeconds(40);
    BOOST_TEST((t1.get() == 40000));
    BOOST_TEST((static_cast<double>(t1) == 40000));
    BOOST_TEST((t1.getAsSeconds() == 40));
    BOOST_TEST((t1.getAsMilliseconds() == 40000));
    BOOST_TEST((t1.getAsMicroseconds() == 40000000));
    BOOST_TEST((t1.getAsNanoseconds() == 40000000000));

    t1.set(::xrn::Time::createAsSeconds(50));
    BOOST_TEST((t1.get() == 50000));
    BOOST_TEST((static_cast<double>(t1) == 50000));
    BOOST_TEST((t1.getAsSeconds() == 50));
    BOOST_TEST((t1.getAsMilliseconds() == 50000));
    BOOST_TEST((t1.getAsMicroseconds() == 50000000));
    BOOST_TEST((t1.getAsNanoseconds() == 50000000000));

    t1.set(60000);
    BOOST_TEST((t1.get() == 60000));
    BOOST_TEST((static_cast<double>(t1) == 60000));
    BOOST_TEST((t1.getAsSeconds() == 60));
    BOOST_TEST((t1.getAsMilliseconds() == 60000));
    BOOST_TEST((t1.getAsMicroseconds() == 60000000));
    BOOST_TEST((t1.getAsNanoseconds() == 60000000000));
}

BOOST_AUTO_TEST_CASE(Add)
{
    auto t1{ ::xrn::Time::createAsSeconds(3) };
    auto t2{ ::xrn::Time::createAsSeconds(3) };

    t1 += t2;
    BOOST_TEST((t1 == 6000));
    t1 = t1 + t2;
    BOOST_TEST((t1 == 9000));
    t1 += 3000;
    BOOST_TEST((t1 == 12000));
    t1 = t2 + 3000;
    BOOST_TEST((t1 == 6000));
    t1.add(t2);
    BOOST_TEST((t1 == 9000));
    t1.add(3000);
    BOOST_TEST((t1 == 12000));
}

BOOST_AUTO_TEST_CASE(Sub)
{
    auto t1{ ::xrn::Time::createAsSeconds(3) };
    auto t2{ ::xrn::Time::createAsSeconds(3) };

    t1 -= t2;
    BOOST_TEST((t1 == 0));
    t1 = t1 - t2;
    BOOST_TEST((t1 == -3000));
    t1 -= 3000;
    BOOST_TEST((t1 == -6000));
    t1 = t2 - 3000;
    BOOST_TEST((t1 == 0));
    t1.sub(t2);
    BOOST_TEST((t1 == -3000));
    t1.sub(3000);
    BOOST_TEST((t1 == -6000));
}

BOOST_AUTO_TEST_CASE(MulDiv)
{
    auto t1{ ::xrn::Time::createAsSeconds(3) };

    t1 *= 3;
    BOOST_TEST((t1 == 9000));
    t1 /= 3;
    BOOST_TEST((t1 == 3000));
    t1 = t1 * 3;
    BOOST_TEST((t1 == 9000));
    t1 = t1 / 3;
    BOOST_TEST((t1 == 3000));
}

BOOST_AUTO_TEST_CASE(Mod)
{
    auto t1{ ::xrn::Time::createAsSeconds(3) };

    t1 %= 3;
    BOOST_TEST((t1 == 0));
    t1 = ::xrn::Time::createAsSeconds(3);
    t1 = t1 % 3;
    BOOST_TEST((t1 == 0));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
