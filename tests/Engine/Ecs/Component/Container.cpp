#include <pch.hpp>
#include <Ecs/Component.hpp>
#include <Ecs/Component/Container.hpp>




#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>
#pragma GCC diagnostic pop
BOOST_AUTO_TEST_SUITE(Engine)
BOOST_AUTO_TEST_SUITE(Core)
BOOST_AUTO_TEST_SUITE(Ecs)
BOOST_AUTO_TEST_SUITE(Component)
BOOST_AUTO_TEST_SUITE(Container)



BOOST_AUTO_TEST_CASE(compareEmplaceRetValAndGetRetVal)
{
    ::xrn::ecs::component::Container container;
    const auto& movableComponent{ container.emplace<::xrn::ecs::component::test::ComponentA>(1) };
    BOOST_TEST((movableComponent == *container.get<::xrn::ecs::component::test::ComponentA>(1)));
    BOOST_TEST((movableComponent.value == 0));

    container.emplace<::xrn::ecs::component::test::ComponentB>(2, 3);
    BOOST_TEST((
        container.get<::xrn::ecs::component::test::ComponentA>(1)->value + 3 ==
        container.get<::xrn::ecs::component::test::ComponentB>(2)->value
    ));
}

BOOST_AUTO_TEST_CASE(contains)
{
    ::xrn::ecs::component::Container container;
    container.emplace<::xrn::ecs::component::test::ComponentA>(1);
    container.emplace<::xrn::ecs::component::test::ComponentB>(2, 3);
    BOOST_TEST((container.contains<::xrn::ecs::component::test::ComponentA>(1)));
    BOOST_TEST((container.contains<::xrn::ecs::component::test::ComponentA>(2)) == false);
    BOOST_TEST((container.contains<::xrn::ecs::component::test::ComponentB>(1)) == false);
    BOOST_TEST((container.contains<::xrn::ecs::component::test::ComponentB>(2)));
}

BOOST_AUTO_TEST_CASE(doenstExists)
{
    ::xrn::ecs::component::Container container;
    BOOST_TEST((!container.contains<::xrn::ecs::component::test::ComponentA>(1)));
}

BOOST_AUTO_TEST_CASE(multipleComponentValue)
{
    ::xrn::ecs::component::Container container;
    const auto& movableComponent{ container.emplace<::xrn::ecs::component::test::ComponentA>(1) };
    BOOST_TEST(container.get<::xrn::ecs::component::test::ComponentA>(1)->value == 0);
    BOOST_TEST(movableComponent.value == 0);
    const auto& movableComponent2{ container.emplace<::xrn::ecs::component::test::ComponentA>(2) };
    BOOST_TEST(container.get<::xrn::ecs::component::test::ComponentA>(1)->value == 0);
    BOOST_TEST(container.get<::xrn::ecs::component::test::ComponentA>(2)->value == 0);
    BOOST_TEST(movableComponent2.value == 0);
}

BOOST_AUTO_TEST_CASE(push)
{
    ::xrn::ecs::component::Container container;
    container.push<::xrn::ecs::component::test::ComponentA>(
        1,
        ::xrn::ecs::component::test::ComponentA{}
    );
    container.push(2, ::xrn::ecs::component::test::ComponentA{});
    container.pushMany<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >(
        3,
        ::xrn::ecs::component::test::ComponentA{},
        ::xrn::ecs::component::test::ComponentB{ 1 }
    );
    container.pushMany(
        4,
        ::xrn::ecs::component::test::ComponentA{},
        ::xrn::ecs::component::test::ComponentB{ 5 }
    );
}



BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
