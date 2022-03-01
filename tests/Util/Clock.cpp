#include <pch.hpp>
#include <Util/Clock.hpp>

template class ::xrn::util::BasicClock<::xrn::Time>;

#include <boost/test/unit_test.hpp>
BOOST_AUTO_TEST_SUITE(test)
BOOST_AUTO_TEST_SUITE(xrn)
BOOST_AUTO_TEST_SUITE(util)
BOOST_AUTO_TEST_SUITE(Clock)

BOOST_AUTO_TEST_CASE(Basic)
{
    ::xrn::Clock clock;
    ::std::this_thread::sleep_for(50ms);
    auto t1{ clock.getElapsed() };
    auto t2{ clock.restart() };
    auto t3{ clock.restart() };
    BOOST_TEST((t1 < t2));
    BOOST_TEST((t1 > t3));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
