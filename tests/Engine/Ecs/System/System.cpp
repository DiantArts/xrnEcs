#include <pch.hpp>
#include <xrn/Ecs/System.hpp>



namespace detail {

    static void function1(
        ::xrn::ecs::entity::Entity& e,
        ::xrn::ecs::component::test::ComponentA& m
    ) {
        ++m.value;
    }
    static auto lambda1{
        [](
            ::xrn::ecs::entity::Entity& e,
            ::xrn::ecs::component::test::ComponentA& m
        ) {
            ++m.value;
        }
    };

    static int function2(
        ::xrn::ecs::entity::Entity& e,
        ::xrn::ecs::component::test::ComponentB& t
    )
    {
        ++t.value;
        return 0;
    }
    static auto lambda2{
        [](
            ::xrn::ecs::entity::Entity& e,
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

    static void function5(
        ::xrn::Time deltaTime,
        ::xrn::ecs::component::test::ComponentA& m
    ) {
        ++m.value;
    }

    static void function6(
        ::xrn::Time deltaTime,
        ::xrn::ecs::entity::Entity& e,
        ::xrn::ecs::component::test::ComponentA& m
    ) {
        ++m.value;
    }

    static void function7(
        ::xrn::ecs::entity::Entity& e,
        ::xrn::Time deltaTime,
        ::xrn::ecs::component::test::ComponentA& m
    ) {
        ++m.value;
    }

    static void function8(
        ::xrn::Time deltaTime,
        const ::xrn::ecs::entity::Entity& e,
        ::xrn::ecs::component::test::ComponentA& m,
        ::xrn::ecs::component::test::ComponentB& t
    ) {
        ++m.value;
        ++t.value;
    }

    static void function9(
        const ::xrn::ecs::entity::Entity& e,
        const ::xrn::Time deltaTime,
        const ::xrn::ecs::component::test::ComponentA& m
    ) {}

    static void function10(
        const ::xrn::ecs::entity::Entity& e,
        const ::xrn::Time deltaTime,
        const ::xrn::ecs::component::test::ComponentA& m
    ) {}

}



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>
#pragma GCC diagnostic pop
BOOST_AUTO_TEST_SUITE(Engine)
BOOST_AUTO_TEST_SUITE(Core)
BOOST_AUTO_TEST_SUITE(Ecs)
BOOST_AUTO_TEST_SUITE(System)



BOOST_AUTO_TEST_CASE(mulpiteComponentMulipleEntityMulipleSystem)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    auto e1Id{ entities.emplace<::xrn::ecs::component::test::ComponentA>().getId() };
    auto e2Id{ entities.emplace<::xrn::ecs::component::test::ComponentB>().getId() };
    auto e3Id{ entities.emplace<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >().getId() };

    ::xrn::ecs::System system1{ detail::function1 };
    ::xrn::Clock c;
    system1(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 0);

    system1(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 0);

    ::xrn::ecs::System system2{ detail::function2 };
    system2(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 1);

    ::xrn::ecs::System system3{ detail::function3 };
    system3(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 2);

    ::xrn::ecs::System system4{ detail::function1 };
    system4(c.restart(), entities);
    system4(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 4);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 5);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 2);
}

BOOST_AUTO_TEST_CASE(lambdaMulpiteComponentMulipleEntityMulipleSystem)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    auto e1Id{ entities.emplace<::xrn::ecs::component::test::ComponentA>().getId() };
    auto e2Id{ entities.emplace<::xrn::ecs::component::test::ComponentB>().getId() };
    auto e3Id{ entities.emplace<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >().getId() };

    ::xrn::ecs::System system1{ detail::lambda1 };
    ::xrn::Clock c;
    system1(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 0);

    system1(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 0);

    ::xrn::ecs::System system2{ detail::lambda2 };
    system2(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 1);

    ::xrn::ecs::System system3{ detail::lambda3 };
    system3(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 2);
}

BOOST_AUTO_TEST_CASE(inlineLambdaMulpiteComponentMulipleEntityMulipleSystem)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    auto e1Id{ entities.emplace<::xrn::ecs::component::test::ComponentA>().getId() };
    auto e2Id{ entities.emplace<::xrn::ecs::component::test::ComponentB>().getId() };
    auto e3Id{ entities.emplace<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >().getId() };

    ::xrn::ecs::System system1{ [](::xrn::ecs::component::test::ComponentA& m) { ++m.value;} };
    ::xrn::Clock c;
    system1(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 0);

    system1(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 0);

    ::xrn::ecs::System system2{
        [](::xrn::ecs::component::test::ComponentB& t) -> int { ++t.value; return 0; }
    };
    system2(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 1);

    ::xrn::ecs::System system3{
        [](::xrn::ecs::component::test::ComponentA& m, ::xrn::ecs::component::test::ComponentB& t) {
            ++m.value;
            ++t.value;
        }
    };
    system3(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 2);
}

BOOST_AUTO_TEST_CASE(systemTime)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    auto e1Id{ entities.emplace<::xrn::ecs::component::test::ComponentA>().getId() };
    auto e2Id{ entities.emplace<::xrn::ecs::component::test::ComponentB>().getId() };
    auto e3Id{ entities.emplace<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >().getId() };

    ::xrn::ecs::System system1{ detail::function5 };
    ::xrn::Clock c;
    system1(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 0);

    ::xrn::ecs::System system2{ detail::function6 };
    system2(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 0);

    ::xrn::ecs::System system3{ detail::function7 };
    system3(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 0);

    ::xrn::ecs::System system4{ detail::function8 };
    system4(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 4);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 1);

    ::xrn::ecs::System system5{ detail::function9 };
    system5(c.restart(), entities);

    ::xrn::ecs::System system6{ detail::function10 };
    system6(c.restart(), entities);
}

BOOST_AUTO_TEST_CASE(systemAdditionalArgs)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    auto e1Id{ entities.emplace<::xrn::ecs::component::test::ComponentA>().getId() };

    ::xrn::ecs::System system1{
        [i = 5](::xrn::ecs::component::test::ComponentA& m){ m.value += i; }
    };
    ::xrn::Clock c;
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 0);
    system1(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 5);
}

BOOST_AUTO_TEST_CASE(banished)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    auto e1Id{ entities.emplace<::xrn::ecs::component::test::ComponentA>().getId() };
    auto e2Id{ entities.emplace<::xrn::ecs::component::test::ComponentB>().getId() };
    auto e3Id{ entities.emplace<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >().getId() };

    ::xrn::ecs::System system1{ detail::function1 };
    ::xrn::Clock c;
    system1(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 0);

    system1.banish<::xrn::ecs::component::test::ComponentB>();
    system1(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 0);
}

BOOST_AUTO_TEST_CASE(ability)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    auto e1Id{ entities.emplace<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::AbilityA
    >().getId() };
    auto e2Id{ entities.emplace<::xrn::ecs::component::test::ComponentB>().getId() };
    auto e3Id{ entities.emplace<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >().getId() };

    ::xrn::ecs::System system1{ detail::function1 };
    ::xrn::Clock c;
    system1(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 0);

    system1.addToSignature<::xrn::ecs::component::test::AbilityA>();
    system1(c.restart(), entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value == 0);
}

BOOST_AUTO_TEST_CASE(banishedConst)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    auto e1Id{ entities.emplace<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::AbilityA
    >().getId() };
    auto e2Id{ entities.emplace<::xrn::ecs::component::test::ComponentB>().getId() };
    auto e3Id{ entities.emplace<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >().getId() };

    int i = 0;
    ::xrn::ecs::ConstSystem system1{
        [&i](
            const ::xrn::ecs::entity::Entity& e,
            const ::xrn::ecs::component::test::ComponentA& m
        ) {
            i++;
        }
    };
    ::xrn::Clock c;
    system1(c.restart(), entities);
    BOOST_TEST(i == 2);

    system1.banish<::xrn::ecs::component::test::ComponentB>();
    system1(c.restart(), entities);
    BOOST_TEST(i == 3);
}

BOOST_AUTO_TEST_CASE(abilityConst)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    auto e1Id{ entities.emplace<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::AbilityA
    >().getId() };
    auto e2Id{ entities.emplace<::xrn::ecs::component::test::ComponentB>().getId() };
    auto e3Id{ entities.emplace<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >().getId() };

    int i = 0;
    ::xrn::ecs::ConstSystem system1{
        [&i](
            const ::xrn::ecs::entity::Entity& e,
            const ::xrn::ecs::component::test::ComponentA& m
        ) {
            i++;
        }
    };
    ::xrn::Clock c;
    system1(c.restart(), entities);
    BOOST_TEST(i == 2);

    system1.addToSignature<::xrn::ecs::component::test::AbilityA>();
    system1(c.restart(), entities);
    BOOST_TEST(i == 3);
}

BOOST_AUTO_TEST_CASE(signature)
{
    ::xrn::ecs::System system1{ detail::function1 };
    auto value{ system1.getSignature() ==
        ::xrn::ecs::Signature::generate<::xrn::ecs::component::test::ComponentA>()
    };
    BOOST_TEST(value);

    ::xrn::ecs::System system2{ detail::lambda1 };
    value = system2.getSignature() ==
        ::xrn::ecs::Signature::generate<::xrn::ecs::component::test::ComponentA>();
    BOOST_TEST(value);

    ::xrn::ecs::System system3{ detail::function3 };
    value = system3.getSignature() ==
        ::xrn::ecs::Signature::generate<
            ::xrn::ecs::component::test::ComponentA,
            ::xrn::ecs::component::test::ComponentB
        >();
    BOOST_TEST(value);

    ::xrn::ecs::System system4{ detail::lambda3 };
    value = system4.getSignature() ==
        ::xrn::ecs::Signature::generate<
            ::xrn::ecs::component::test::ComponentA,
            ::xrn::ecs::component::test::ComponentB
        >();
    BOOST_TEST(value);

    ::xrn::ecs::System system5{ detail::function5 };
    value = system5.getSignature() ==
        ::xrn::ecs::Signature::generate<
            ::xrn::ecs::component::test::ComponentA
        >();
    BOOST_TEST(value);

    ::xrn::ecs::System system6{ detail::function6 };
    value = system6.getSignature() ==
        ::xrn::ecs::Signature::generate<
            ::xrn::ecs::component::test::ComponentA
        >();
    BOOST_TEST(value);

    ::xrn::ecs::System system7{ detail::function7 };
    value = system7.getSignature() ==
        ::xrn::ecs::Signature::generate<
            ::xrn::ecs::component::test::ComponentA
        >();
    BOOST_TEST(value);

    ::xrn::ecs::System system8{ detail::function8 };
    value = system8.getSignature() ==
        ::xrn::ecs::Signature::generate<
            ::xrn::ecs::component::test::ComponentA,
            ::xrn::ecs::component::test::ComponentB
        >();
    BOOST_TEST(value);

    ::xrn::ecs::System system9{ detail::function9 };
    value = system9.getSignature() ==
        ::xrn::ecs::Signature::generate<
            ::xrn::ecs::component::test::ComponentA
        >();
    BOOST_TEST(value);

    ::xrn::ecs::System system10{ detail::function10 };
    value = system10.getSignature() ==
        ::xrn::ecs::Signature::generate<
            ::xrn::ecs::component::test::ComponentA
        >();
    BOOST_TEST(value);
}


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
