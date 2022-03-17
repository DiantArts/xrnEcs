#include <pch.hpp>
#include <Util/Id.hpp>

template class ::xrn::util::BasicForwardId<::std::size_t>;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>
#pragma GCC diagnostic pop

BOOST_AUTO_TEST_SUITE(test)
BOOST_AUTO_TEST_SUITE(xrn)
BOOST_AUTO_TEST_SUITE(util)
BOOST_AUTO_TEST_SUITE(Id)

BOOST_AUTO_TEST_CASE(BasicConstexpr)
{
    constexpr ::xrn::Id cId1{ 1 };
    constexpr ::xrn::Id cId2{ 1 };
    constexpr ::xrn::Id cId3{ 2 };
    constexpr ::xrn::Id cId4{ cId2 };
    constexpr ::xrn::Id cId5{ ::std::move(cId2) };
    BOOST_TEST((cId1 == cId2));
    BOOST_TEST((cId1 != cId3));
    BOOST_TEST((cId1 == 1));
    BOOST_TEST((cId1 != 2));
    BOOST_TEST((1 == cId1));
    BOOST_TEST((2 != cId1));

    BOOST_TEST((cId3 > cId1));
    BOOST_TEST((cId3 >= cId1));
    BOOST_TEST((cId1 < cId3));
    BOOST_TEST((cId1 <= cId3));
    BOOST_TEST((cId1 < 2));
    BOOST_TEST((cId1 <= 2));
    BOOST_TEST((2 > cId1));
    BOOST_TEST((2 >= cId1));
}

BOOST_AUTO_TEST_CASE(Basic)
{
    ::xrn::Id cId1{ 1 };
    ::xrn::Id cId1_2{ cId1 };
    ::xrn::Id cId2{ ::std::move(cId1_2) };
    ::xrn::Id cId3{ 2 };
    ::xrn::Id cId4{ 1 };
    BOOST_TEST((cId1 == cId2));
    BOOST_TEST((cId1 != cId3));
    BOOST_TEST((cId3 > cId1));
    BOOST_TEST((cId3 >= cId1));
    BOOST_TEST((cId1 < cId3));
    BOOST_TEST((cId1 <= cId3));

    cId1 = cId3;
    BOOST_TEST((cId1 == cId3));

    cId1 = ::std::move(cId2);
    BOOST_TEST((cId1 == 1));

    cId1++;
    BOOST_TEST((cId1 == 2));
    ++cId1;
    BOOST_TEST((cId1 == 3));
    cId1.increment();
    BOOST_TEST((cId1 == 4));

    BOOST_TEST((static_cast<::std::string>(cId1) == "4"));
    BOOST_TEST((cId1.getAsString() == "4"));
    BOOST_TEST((static_cast<::std::size_t>(cId1) == 4));
    BOOST_TEST((cId1.get() == 4));

    cId1 = ::std::move(cId3);
    BOOST_TEST((cId1 == 2));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
