#include <pch.hpp>
#include <xrn/Meta/UniqueTypes.hpp>



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>
#pragma GCC diagnostic pop
BOOST_AUTO_TEST_SUITE(Engine)
BOOST_AUTO_TEST_SUITE(Core)
BOOST_AUTO_TEST_SUITE(Detail)
BOOST_AUTO_TEST_SUITE(Meta)
BOOST_AUTO_TEST_SUITE(UniqueTypes)



BOOST_AUTO_TEST_CASE(baseArg)
{
    BOOST_TEST((::xrn::meta::UniqueTypes<int>::value));
    BOOST_TEST((::xrn::meta::UniqueTypes<int, float>::value));
    BOOST_TEST((::xrn::meta::UniqueTypes<int, float, double>::value));
}

BOOST_AUTO_TEST_CASE(trueMultipleArgs)
{
    BOOST_TEST((::xrn::meta::UniqueTypes<short, int, long, float, double, char>::value));
}



BOOST_AUTO_TEST_CASE(false2Args)
{
    BOOST_TEST((!::xrn::meta::UniqueTypes<int, int>::value));
}

BOOST_AUTO_TEST_CASE(false3Args)
{
    BOOST_TEST((!::xrn::meta::UniqueTypes<int, double, int>::value));
    BOOST_TEST((!::xrn::meta::UniqueTypes<double, int, int>::value));
    BOOST_TEST((!::xrn::meta::UniqueTypes<int, int, double>::value));
}

BOOST_AUTO_TEST_CASE(falseMultipleArgs)
{
    BOOST_TEST((!::xrn::meta::UniqueTypes<int, float, double, long, short, char, int>::value));
    BOOST_TEST((!::xrn::meta::UniqueTypes<float, double, long, int, short, char, int>::value));
    BOOST_TEST((!::xrn::meta::UniqueTypes<float, double, int, long, short, int, char>::value));
}



BOOST_AUTO_TEST_CASE(false4Test)
{
    BOOST_TEST((!::xrn::meta::UniqueTypes<int, int, float, double>::value));
    BOOST_TEST((!::xrn::meta::UniqueTypes<int, float, int, double>::value));
    BOOST_TEST((!::xrn::meta::UniqueTypes<int, float, double, int>::value));
    BOOST_TEST((!::xrn::meta::UniqueTypes<float, int, int, double>::value));
    BOOST_TEST((!::xrn::meta::UniqueTypes<float, int, double, int>::value));
    BOOST_TEST((!::xrn::meta::UniqueTypes<float, double, int, int>::value));
}



BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
