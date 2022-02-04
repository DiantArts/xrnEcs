#include <pch.hpp>
#include <Ecs/AComponent.hpp>



// ------------------------------------------------------------------ Class test

namespace xrn::ecs::component::test {



    class Movable
        : public ::xrn::ecs::AComponent<::xrn::ecs::component::test::Movable>
    {};

    class Transformable
        : public ::xrn::ecs::AComponent<::xrn::ecs::component::test::Transformable>
    {};



} // namespace xrn::ecs::component::test




#include <boost/test/unit_test.hpp>
BOOST_AUTO_TEST_SUITE(Engine)
BOOST_AUTO_TEST_SUITE(Core)
BOOST_AUTO_TEST_SUITE(Ecs)
BOOST_AUTO_TEST_SUITE(Component)



BOOST_AUTO_TEST_CASE(Constructor)
{
    ::xrn::ecs::component::test::Movable movable;
    ::xrn::ecs::component::test::Movable{};
}



// ------------------------------------------------------------------ Id
BOOST_AUTO_TEST_SUITE(Id)



BOOST_AUTO_TEST_CASE(getStaticVsMember)
{
    BOOST_TEST(::xrn::ecs::component::test::Movable::getId() ==
        ::xrn::ecs::component::test::Movable().getId());
}

BOOST_AUTO_TEST_CASE(different)
{
    BOOST_TEST(::xrn::ecs::component::test::Movable::getId() !=
        ::xrn::ecs::component::test::Transformable::getId());
}

BOOST_AUTO_TEST_CASE(constexprness)
{
    // bitset needs a constexpr to compile
    ::std::bitset<::xrn::ecs::component::test::Movable::getId() + 1>();
}



BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
