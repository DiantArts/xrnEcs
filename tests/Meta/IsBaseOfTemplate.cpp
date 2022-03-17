#include <pch.hpp>
#include <Meta/IsBaseOfTemplate.hpp>



namespace test::detail {

template <
    typename
> class Base {};

class OtherBase {};

class DerivedPublic : public ::test::detail::Base<DerivedPublic> {};

class DerivedPrivate : private ::test::detail::Base<DerivedPrivate> {};

class DerivedDerived : public DerivedPublic {};

} // namespace test::detail



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>
#pragma GCC diagnostic pop
BOOST_AUTO_TEST_SUITE(Engine)
BOOST_AUTO_TEST_SUITE(Core)
BOOST_AUTO_TEST_SUITE(Detail)
BOOST_AUTO_TEST_SUITE(Meta)
BOOST_AUTO_TEST_SUITE(IsBaseOfTemplate)



BOOST_AUTO_TEST_CASE(DerivedPublic)
{
    BOOST_TEST((::xrn::meta::IsBaseOfTemplate<
        ::test::detail::Base,
        ::test::detail::DerivedPublic
    >::value));
}

BOOST_AUTO_TEST_CASE(DerivedDerived)
{
    BOOST_TEST((::xrn::meta::IsBaseOfTemplate<
        ::test::detail::Base,
        ::test::detail::DerivedDerived
    >::value));
}

BOOST_AUTO_TEST_CASE(FalseDerivedPrivate)
{
    BOOST_TEST(!(::xrn::meta::IsBaseOfTemplate<
        ::test::detail::Base,
        ::test::detail::DerivedPrivate
    >::value));
}


BOOST_AUTO_TEST_CASE(False)
{
    BOOST_TEST(!(::xrn::meta::IsBaseOfTemplate<
        ::test::detail::Base,
        ::test::detail::OtherBase
    >::value));
}



BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
