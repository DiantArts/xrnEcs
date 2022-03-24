#include <pch.hpp>
#include <xrn/Ecs/Component.hpp>




#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>
#pragma GCC diagnostic pop
BOOST_AUTO_TEST_SUITE(Engine)
BOOST_AUTO_TEST_SUITE(Core)
BOOST_AUTO_TEST_SUITE(Ecs)
BOOST_AUTO_TEST_SUITE(Component)



BOOST_AUTO_TEST_CASE(Constructor)
{
    ::xrn::ecs::component::test::ComponentA movable;
    ::xrn::ecs::component::test::ComponentA{};
}



// ------------------------------------------------------------------ Id
BOOST_AUTO_TEST_SUITE(Id)



BOOST_AUTO_TEST_CASE(getStaticVsMember)
{
    BOOST_TEST(::xrn::ecs::component::test::ComponentA::getId() ==
        ::xrn::ecs::component::test::ComponentA().getId());
}

BOOST_AUTO_TEST_CASE(different)
{
    BOOST_TEST(::xrn::ecs::component::test::ComponentA::getId() !=
        ::xrn::ecs::component::test::ComponentB::getId());
}

BOOST_AUTO_TEST_CASE(constexprness)
{
    // bitset needs a constexpr to compile
    ::std::bitset<::xrn::ecs::component::test::ComponentA::getId() + 1>();
}



BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
