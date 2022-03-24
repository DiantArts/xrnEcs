#include <pch.hpp>
#include <xrn/Meta/Constraint.hpp>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>
#pragma GCC diagnostic pop
BOOST_AUTO_TEST_SUITE(test)
BOOST_AUTO_TEST_SUITE(xrn)
BOOST_AUTO_TEST_SUITE(meta)
BOOST_AUTO_TEST_SUITE(constraint)



BOOST_AUTO_TEST_CASE(sameAs)
{
    BOOST_TEST((::xrn::meta::constraint::sameAs<int, const int&>));
    BOOST_TEST((::xrn::meta::constraint::sameAs<int, const int*>));
    BOOST_TEST((::xrn::meta::constraint::sameAs<int, const int>));
    BOOST_TEST((::xrn::meta::constraint::sameAs<int, int&>));
    BOOST_TEST((::xrn::meta::constraint::sameAs<int, int*>));
    BOOST_TEST((::xrn::meta::constraint::sameAs<int, int>));

    BOOST_TEST((::xrn::meta::constraint::sameAs<const int&, int>));
    BOOST_TEST((::xrn::meta::constraint::sameAs<const int*, int>));
    BOOST_TEST((::xrn::meta::constraint::sameAs<const int, int>));
    BOOST_TEST((::xrn::meta::constraint::sameAs<int&, int>));
    BOOST_TEST((::xrn::meta::constraint::sameAs<int*, int>));
    BOOST_TEST((::xrn::meta::constraint::sameAs<int, int>));
}

BOOST_AUTO_TEST_CASE(isConst)
{
    BOOST_TEST(!::xrn::meta::constraint::isConst<int>);
    BOOST_TEST(!::xrn::meta::constraint::isConst<int&>);
    BOOST_TEST(!::xrn::meta::constraint::isConst<int* const>);

    BOOST_TEST(::xrn::meta::constraint::isConst<const int*>);
    BOOST_TEST(::xrn::meta::constraint::isConst<const int&>);
    BOOST_TEST(::xrn::meta::constraint::isConst<const int>);
}

BOOST_AUTO_TEST_CASE(isMutable)
{
    BOOST_TEST(!::xrn::meta::constraint::isMutable<int>);
    BOOST_TEST(!::xrn::meta::constraint::isMutable<const int&>);
    BOOST_TEST(!::xrn::meta::constraint::isMutable<const int*>);

    BOOST_TEST(::xrn::meta::constraint::isMutable<int*>);
    BOOST_TEST(::xrn::meta::constraint::isMutable<int&>);
    BOOST_TEST(::xrn::meta::constraint::isMutable<int *const>);
}



BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
