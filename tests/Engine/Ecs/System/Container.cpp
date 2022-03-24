#include <pch.hpp>
#include <xrn/Ecs/System.hpp>




namespace detail {

    static void function1(
        ::xrn::ecs::component::test::ComponentA& m
    ) {
        ++m.value;
    }
    static auto lambda1{
        [](
            ::xrn::ecs::component::test::ComponentA& m
        ) {
            ++m.value;
        }
    };

    static int function2(
        ::xrn::ecs::component::test::ComponentB& t
    )
    {
        ++t.value;
        return 0;
    }
    static auto lambda2{
        [](
            ::xrn::ecs::component::test::ComponentB& t
        )
            -> int
        {
            ++t.value;
            return 0;
        }
    };

    static void function3(
        ::xrn::ecs::component::test::ComponentA& m,
        ::xrn::ecs::component::test::ComponentB& t
    )
    {
        ++m.value;
        ++t.value;
    }
    static auto lambda3{
        [](
            ::xrn::ecs::component::test::ComponentA& m,
            ::xrn::ecs::component::test::ComponentB& t
        ) {
            ++m.value;
            ++t.value;
        }
    };

}



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>
#pragma GCC diagnostic pop
BOOST_AUTO_TEST_SUITE(Engine)
BOOST_AUTO_TEST_SUITE(Core)
BOOST_AUTO_TEST_SUITE(Ecs)
BOOST_AUTO_TEST_SUITE(System)
BOOST_AUTO_TEST_SUITE(Container)

BOOST_AUTO_TEST_CASE(mulpiteComponentMulipleEntityMulipleSystem)
{
    ::xrn::Clock c;
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    auto e1Id{ entities.emplace<::xrn::ecs::component::test::ComponentA>().getId() };
    auto e2Id{ entities.emplace<::xrn::ecs::component::test::ComponentB>().getId() };
    auto e3Id{ entities.emplace<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >().getId() };
    ::xrn::ecs::system::Container systems;

    systems.emplace<detail::function1>();
    systems.run(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 0);

    systems.run(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 0);

    systems.emplace<detail::function2>();
    systems.run(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 1);

    systems.emplace<detail::function3>();
    systems.run(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 4);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 5);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 3);
}

BOOST_AUTO_TEST_CASE(lambdaMulpiteComponentMulipleEntityMulipleSystem)
{
    ::xrn::Clock c;
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    auto e1Id{ entities.emplace<::xrn::ecs::component::test::ComponentA>().getId() };
    auto e2Id{ entities.emplace<::xrn::ecs::component::test::ComponentB>().getId() };
    auto e3Id{ entities.emplace<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >().getId() };
    ::xrn::ecs::system::Container systems;

    systems.emplace<detail::lambda1>();
    systems.run(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 0);

    systems.run(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 0);

    systems.emplace<detail::lambda2>();
    systems.run(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 1);

    systems.emplace<detail::lambda3>();
    systems.run(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 4);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 5);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 3);
}

BOOST_AUTO_TEST_CASE(inlineLambdaMulpiteComponentMulipleEntityMulipleSystem)
{
    ::xrn::Clock c;
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    auto e1Id{ entities.emplace<::xrn::ecs::component::test::ComponentA>().getId() };
    auto e2Id{ entities.emplace<::xrn::ecs::component::test::ComponentB>().getId() };
    auto e3Id{ entities.emplace<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >().getId() };
    ::xrn::ecs::system::Container systems;

    systems.emplace<[](::xrn::ecs::component::test::ComponentA& m) { ++m.value;}>();
    systems.run(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 0);

    systems.run(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 0);

    systems.emplace<[](::xrn::ecs::component::test::ComponentB& t) -> int
        { ++t.value; return 0; }>();
    systems.run(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 1);

    systems.emplace<[](
            ::xrn::ecs::component::test::ComponentA& m,
            ::xrn::ecs::component::test::ComponentB& t
        ) {
            ++m.value;
            ++t.value;
        }>();
    systems.run(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 4);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 5);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 3);
}

BOOST_AUTO_TEST_CASE(constSystems)
{
    ::xrn::Clock c;
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    auto e1Id{ entities.emplace<::xrn::ecs::component::test::ComponentA>().getId() };
    auto e2Id{ entities.emplace<::xrn::ecs::component::test::ComponentB>().getId() };
    auto e3Id{ entities.emplace<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >().getId() };
    ::xrn::ecs::system::ConstContainer systems;

    systems.emplace<[](const ::xrn::ecs::component::test::ComponentA& m){}>();
    systems.run(c.restart(), entities);
}

BOOST_AUTO_TEST_CASE(nonConstOnConst)
{
    ::xrn::Clock c;
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    auto e1Id{ entities.emplace<::xrn::ecs::component::test::ComponentA>().getId() };
    auto e2Id{ entities.emplace<::xrn::ecs::component::test::ComponentB>().getId() };
    ::xrn::ecs::system::Container systems;
    ::xrn::ecs::system::ConstContainer constSystems;

    systems.emplace<[](const ::xrn::ecs::entity::Entity& e, ::xrn::ecs::component::test::ComponentA& m){}>();
    systems.emplace<
        [](const ::xrn::ecs::entity::Entity& e, ::xrn::Time dt, ::xrn::ecs::component::test::ComponentA& m){}
    >();
    systems.emplace<
        [](::xrn::Time dt, const ::xrn::ecs::entity::Entity& e, ::xrn::ecs::component::test::ComponentA& m){}
    >();
    systems.emplace<
        [](::xrn::Time dt, const ::xrn::ecs::entity::Entity& e, const ::xrn::ecs::component::test::ComponentA& m){}
    >();
    ::std::cerr.setstate(::std::ios::failbit);
    constSystems.emplace<
        [](::xrn::Time dt, ::xrn::ecs::entity::Entity& e, const ::xrn::ecs::component::test::ComponentA& m){}
    >();
    ::std::cerr.clear();

    systems.run(c.restart(), entities);
    constSystems.run(c.restart(), entities);
}


BOOST_AUTO_TEST_CASE(other)
{
    ::xrn::Clock c;
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    auto e1Id{ entities.emplace<::xrn::ecs::component::test::ComponentA>().getId() };
    auto e2Id{ entities.emplace<::xrn::ecs::component::test::ComponentB>().getId() };
    ::xrn::ecs::system::Container systems;
    ::xrn::ecs::system::Container& constSystems = systems;

    systems.emplace<[](const ::xrn::ecs::entity::Entity& e, const ::xrn::ecs::component::test::ComponentA& m){}>();
    systems.emplace<
        [](const ::xrn::ecs::entity::Entity& e, ::xrn::Time dt, const ::xrn::ecs::component::test::ComponentA& m){}
    >();
    systems.emplace<
        [](::xrn::Time dt, const ::xrn::ecs::entity::Entity& e, const ::xrn::ecs::component::test::ComponentA& m){}
    >();
    systems.run(c.restart(), entities);
    constSystems.run(c.restart(), entities);
}



BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
