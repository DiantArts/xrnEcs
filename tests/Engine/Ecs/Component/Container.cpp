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

BOOST_AUTO_TEST_CASE(other)
{
    ::xrn::ecs::component::Container container3;
    {
        ::xrn::ecs::component::Container container{ 1024 };
        container.emplace<::xrn::ecs::component::test::ComponentA>(1);
        BOOST_TEST(container.get<::xrn::ecs::component::test::ComponentA>(1)->value == 0);
        auto container2{ ::std::move(container) };
        container2.emplace<::xrn::ecs::component::test::ComponentB>(2);
        BOOST_TEST(container2.get<::xrn::ecs::component::test::ComponentA>(1)->value == 0);
        BOOST_TEST(container2.get<::xrn::ecs::component::test::ComponentB>(2)->value == 0);
        container3 = ::std::move(container2);
    }
    container3.emplace<::xrn::ecs::component::test::ComponentA>(3);
    BOOST_TEST(container3.get<::xrn::ecs::component::test::ComponentA>(1)->value == 0);
    BOOST_TEST(container3.get<::xrn::ecs::component::test::ComponentB>(2)->value == 0);
    BOOST_TEST(container3.get<::xrn::ecs::component::test::ComponentA>(3)->value == 0);
    container3.clear();
    BOOST_TEST(container3.get<::xrn::ecs::component::test::ComponentA>(1) == nullptr);
    BOOST_TEST(container3.get<::xrn::ecs::component::test::ComponentB>(2) == nullptr);
    BOOST_TEST(container3.get<::xrn::ecs::component::test::ComponentA>(3) == nullptr);
}

BOOST_AUTO_TEST_CASE(recycle)
{
    ::xrn::ecs::component::Container container{ 1024 };
    container.emplace<::xrn::ecs::component::test::ComponentA>(1);
    void* ptr{ container.get<::xrn::ecs::component::test::ComponentA>(1) };
    container.remove<::xrn::ecs::component::test::ComponentA>(1);

    BOOST_TEST((&container.emplace<::xrn::ecs::component::test::ComponentA>(2) == ptr));
    container.remove<::xrn::ecs::component::test::ComponentA>(2);

    // ::xrn::ecs::component::Container container2;
    // container2 = ::std::move(container);
    // ::std::cout << &container2.emplace<::xrn::ecs::component::test::ComponentA>(3) << " == " << ptr << ::std::endl;
    // BOOST_TEST((&container2.emplace<::xrn::ecs::component::test::ComponentA>(3) == ptr));
    // container.remove<::xrn::ecs::component::test::ComponentA>(3);
}



BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
