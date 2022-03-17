#include <pch.hpp>
#include <Meta/ForEach.hpp>



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>
#pragma GCC diagnostic pop
BOOST_AUTO_TEST_SUITE(Engine)
BOOST_AUTO_TEST_SUITE(Core)
BOOST_AUTO_TEST_SUITE(Detail)
BOOST_AUTO_TEST_SUITE(Meta)
BOOST_AUTO_TEST_SUITE(ForEach)



BOOST_AUTO_TEST_CASE(run)
{
    int value{ 0 };
    ::xrn::meta::ForEach<int, float>::run<[]<typename>(int& value){ ++value; }>(value);
    BOOST_TEST(value == 2);
    ::xrn::meta::ForEach<int, float, int>::run<[]<typename>(int& value){ ++value; }>(value);
    BOOST_TEST(value == 5);
}

BOOST_AUTO_TEST_CASE(compareAnd)
{
    bool value;

    value = ::xrn::meta::ForEach<int, short, long>::compareAnd<[]<typename T>(){
        return ::std::is_integral<T>();
    }>();
    BOOST_TEST(value);

    value = ::xrn::meta::ForEach<float, int, ::std::string>::compareAnd<[]<typename T>(){
        return ::std::is_integral<T>();
    }>();
    BOOST_TEST(!value);

    value = ::xrn::meta::ForEach<int, float, ::std::string>::compareAnd<[]<typename T>(){
        return ::std::is_integral<T>();
    }>();
    BOOST_TEST(!value);
}

BOOST_AUTO_TEST_CASE(compareOr)
{
    bool value;

    value = ::xrn::meta::ForEach<int, short, long>::compareOr<[]<typename T>(){
        return ::std::is_integral<T>();
    }>();
    BOOST_TEST(value);

    value = ::xrn::meta::ForEach<float, int, ::std::string>::compareOr<[]<typename T>(){
        return ::std::is_integral<T>();
    }>();
    BOOST_TEST(value);

    value = ::xrn::meta::ForEach<int, float, ::std::string>::compareOr<[]<typename T>(){
        return ::std::is_integral<T>();
    }>();
    BOOST_TEST(value);

    value = ::xrn::meta::ForEach<::std::string, ::std::string>::compareOr<[]<typename T>(){
        return ::std::is_integral<T>();
    }>();
    BOOST_TEST(!value);
}

BOOST_AUTO_TEST_CASE(True2ArgsBeg)
{
    BOOST_TEST((::xrn::meta::ForEach<int, float>::hasType<int>() == true));
}

BOOST_AUTO_TEST_CASE(True2ArgsEnd)
{
    BOOST_TEST((::xrn::meta::ForEach<float, int>::hasType<int>() == true));
}

BOOST_AUTO_TEST_CASE(TrueMultipleArgsBeg)
{
    BOOST_TEST((::xrn::meta::ForEach<short, float, double, long, char>::hasType<short>() == true));
}

BOOST_AUTO_TEST_CASE(TrueMultipleArgsMid)
{
    BOOST_TEST((::xrn::meta::ForEach<float, double, short, long, char>::hasType<short>() == true));
}

BOOST_AUTO_TEST_CASE(TrueMultipleArgsEnd)
{
    BOOST_TEST((::xrn::meta::ForEach<float, double, long, char, short>::hasType<short>() == true));
}

BOOST_AUTO_TEST_CASE(False2Args)
{
    BOOST_TEST((::xrn::meta::ForEach<float, double>::hasType<int>() == false));
}

BOOST_AUTO_TEST_CASE(FalseMultipleArgs)
{
    BOOST_TEST((::xrn::meta::ForEach<float, double, short, long, char>::hasType<int>() == false));
}



BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
