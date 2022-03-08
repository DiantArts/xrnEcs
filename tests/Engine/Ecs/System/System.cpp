#include <pch.hpp>
#include <Ecs/System.hpp>
#include <Util/Clock.hpp>



// ------------------------------------------------------------------ Class test

namespace xrn::ecs::component::test {



    class Movable
        : public ::xrn::ecs::AComponent<::xrn::ecs::component::test::Movable>
    {
    public:
        Movable() = default;
        ~Movable() = default;

        int value{ 0 };
    };

    class Transformable
        : public ::xrn::ecs::AComponent<::xrn::ecs::component::test::Transformable>
    {
    public:
        Transformable() = default;
        ~Transformable() = default;

        int value{ 0 };
    };



} // namespace xrn::ecs::component::test



namespace detail {

    static void function1(
        ::xrn::ecs::Entity& e,
        ::xrn::ecs::component::test::Movable& m
    ) {
        ++m.value;
    }
    static auto lambda1{
        [](
            ::xrn::ecs::Entity& e,
            ::xrn::ecs::component::test::Movable& m
        ) {
            ++m.value;
        }
    };

    static int function2(
        ::xrn::ecs::Entity& e,
        ::xrn::ecs::component::test::Transformable& t
    )
    {
        ++t.value;
        return 0;
    }
    static auto lambda2{
        [](
            ::xrn::ecs::Entity& e,
            ::xrn::ecs::component::test::Transformable& t
        )
            -> int
        {
            ++t.value;
            return 0;
        }
    };

    static void function3(
        ::xrn::ecs::component::test::Movable& m,
        ::xrn::ecs::component::test::Transformable& t
    )
    {
        ++m.value;
        ++t.value;
    }
    static auto lambda3{
        [](
            ::xrn::ecs::component::test::Movable& m,
            ::xrn::ecs::component::test::Transformable& t
        ) {
            ++m.value;
            ++t.value;
        }
    };

    static void function4(
        const ::xrn::ecs::Entity& e,
        const ::xrn::ecs::component::test::Movable& m,
        const ::xrn::ecs::component::test::Transformable& t
    )
    {}

    static void function5(
        ::xrn::Time deltaTime,
        ::xrn::ecs::component::test::Movable& m
    ) {
        ++m.value;
    }

    static void function6(
        ::xrn::Time deltaTime,
        ::xrn::ecs::Entity& e,
        ::xrn::ecs::component::test::Movable& m
    ) {
        ++m.value;
    }

    static void function7(
        ::xrn::ecs::Entity& e,
        ::xrn::Time deltaTime,
        ::xrn::ecs::component::test::Movable& m
    ) {
        ++m.value;
    }

    static void function8(
        ::xrn::Time deltaTime,
        const ::xrn::ecs::Entity& e,
        ::xrn::ecs::component::test::Movable& m,
        ::xrn::ecs::component::test::Transformable& t
    ) {
        ++m.value;
        ++t.value;
    }

    static void function9(
        const ::xrn::ecs::Entity& e,
        const ::xrn::Time deltaTime,
        const ::xrn::ecs::component::test::Movable& m
    ) {}

    static void function10(
        const ::xrn::ecs::Entity& e,
        const ::xrn::Time deltaTime,
        const::xrn::ecs::component::test::Movable& m
    ) {}


}



#include <boost/test/unit_test.hpp>
BOOST_AUTO_TEST_SUITE(Engine)
BOOST_AUTO_TEST_SUITE(Core)
BOOST_AUTO_TEST_SUITE(Ecs)
BOOST_AUTO_TEST_SUITE(System)



BOOST_AUTO_TEST_CASE(mulpiteComponentMulipleEntityMulipleSystem)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity::Container entities{ components };
    auto e1Id{ entities.emplace<::xrn::ecs::component::test::Movable>().getId() };
    auto e2Id{ entities.emplace<::xrn::ecs::component::test::Transformable>().getId() };
    auto e3Id{ entities.emplace<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >().getId() };

    ::xrn::ecs::System<detail::function1> system1;
    ::xrn::Clock c;
    system1(c.restart(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 0);

    system1(c.restart(), components, entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 0);

    ::xrn::ecs::System<detail::function2> system2;
    system2(c.restart(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 1);

    ::xrn::ecs::System<detail::function3> system3;
    system3(c.restart(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 2);

    ::xrn::ecs::System<
        detail::function1,
        ::xrn::ecs::component::test::Transformable
    > system4;
    system4(c.restart(), components, entities);
    system4(c.restart(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 4);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 2);

    const ::xrn::ecs::System<detail::function4> system5;
    system5(c.restart(), entities, components);
}

BOOST_AUTO_TEST_CASE(lambdaMulpiteComponentMulipleEntityMulipleSystem)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity::Container entities{ components };
    auto e1Id{ entities.emplace<::xrn::ecs::component::test::Movable>().getId() };
    auto e2Id{ entities.emplace<::xrn::ecs::component::test::Transformable>().getId() };
    auto e3Id{ entities.emplace<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >().getId() };

    ::xrn::ecs::System<detail::lambda1> system1;
    ::xrn::Clock c;
    system1(c.restart(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 0);

    system1(c.restart(), components, entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 0);

    ::xrn::ecs::System<detail::lambda2> system2;
    system2(c.restart(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 1);

    ::xrn::ecs::System<detail::lambda3> system3;
    system3(c.restart(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 2);
}

BOOST_AUTO_TEST_CASE(inlineLambdaMulpiteComponentMulipleEntityMulipleSystem)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity::Container entities{ components };
    auto e1Id{ entities.emplace<::xrn::ecs::component::test::Movable>().getId() };
    auto e2Id{ entities.emplace<::xrn::ecs::component::test::Transformable>().getId() };
    auto e3Id{ entities.emplace<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >().getId() };

    ::xrn::ecs::System<[](::xrn::ecs::component::test::Movable& m) { ++m.value;}> system1;
    ::xrn::Clock c;
    system1(c.restart(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 0);

    system1(c.restart(), components, entities);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 0);

    ::xrn::ecs::System<[](::xrn::ecs::component::test::Transformable& t) -> int
        { ++t.value; return 0; }> system2;
    system2(c.restart(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 1);

    ::xrn::ecs::System<[](
            ::xrn::ecs::component::test::Movable& m,
            ::xrn::ecs::component::test::Transformable& t
        ) {
            ++m.value;
            ++t.value;
        }
    > system3;
    system3(c.restart(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 2);
}

BOOST_AUTO_TEST_CASE(systemTime)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity::Container entities{ components };
    auto e1Id{ entities.emplace<::xrn::ecs::component::test::Movable>().getId() };
    auto e2Id{ entities.emplace<::xrn::ecs::component::test::Transformable>().getId() };
    auto e3Id{ entities.emplace<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >().getId() };

    ::xrn::ecs::System<detail::function5> system1;
    ::xrn::Clock c;
    system1(c.restart(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 0);

    ::xrn::ecs::System<detail::function6> system2;
    system2(c.restart(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 0);

    ::xrn::ecs::System<detail::function7> system3;
    system3(c.restart(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 0);

    ::xrn::ecs::System<detail::function8> system4;
    system4(c.restart(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 4);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 1);

    ::xrn::ecs::System<detail::function9> system5;
    system5(c.restart(), entities, components);

    ::xrn::ecs::System<detail::function10> system6;
    system6(c.restart(), entities, components);
}

BOOST_AUTO_TEST_CASE(systemAdditionalArgs)
{
    // ::xrn::ecs::component::Container components;
    // ::xrn::ecs::Entity::Container entities{ components };
    // auto e1Id{ entities.emplace<::xrn::ecs::component::test::Movable>().getId() };

    // ::xrn::ecs::System<[](int a, const::xrn::ecs::component::test::Movable& m){}> system1{ 2 };
    // ::xrn::Clock c;
    // system1(c.restart(), entities, components);
}

BOOST_AUTO_TEST_CASE(signature)
{
    auto value{ ::xrn::ecs::System<detail::function1>::getSignature() ==
        ::xrn::ecs::Signature::generate<::xrn::ecs::component::test::Movable>()
    };
    BOOST_TEST(value);

    value = ::xrn::ecs::System<detail::lambda1>::getSignature() ==
        ::xrn::ecs::Signature::generate<::xrn::ecs::component::test::Movable>();
    BOOST_TEST(value);

    value = ::xrn::ecs::System<detail::function3>::getSignature() ==
        ::xrn::ecs::Signature::generate<
            ::xrn::ecs::component::test::Movable,
            ::xrn::ecs::component::test::Transformable
        >();
    BOOST_TEST(value);

    value = ::xrn::ecs::System<detail::lambda3>::getSignature() ==
        ::xrn::ecs::Signature::generate<
            ::xrn::ecs::component::test::Movable,
            ::xrn::ecs::component::test::Transformable
        >();
    BOOST_TEST(value);

    constexpr auto value2{ ::xrn::ecs::System<detail::function3>::getSignature() ==
        ::xrn::ecs::Signature::generate<
            ::xrn::ecs::component::test::Movable,
            ::xrn::ecs::component::test::Transformable
        >()
    };
    BOOST_TEST(value2);

    constexpr auto value3{ ::xrn::ecs::System<detail::lambda3>::getSignature() ==
        ::xrn::ecs::Signature::generate<
            ::xrn::ecs::component::test::Movable,
            ::xrn::ecs::component::test::Transformable
        >()
    };
    BOOST_TEST(value3);

    value = ::xrn::ecs::System<detail::function5>::getSignature() ==
        ::xrn::ecs::Signature::generate<
            ::xrn::ecs::component::test::Movable
        >();
    BOOST_TEST(value);

    value = ::xrn::ecs::System<detail::function6>::getSignature() ==
        ::xrn::ecs::Signature::generate<
            ::xrn::ecs::component::test::Movable
        >();
    BOOST_TEST(value);

    value = ::xrn::ecs::System<detail::function7>::getSignature() ==
        ::xrn::ecs::Signature::generate<
            ::xrn::ecs::component::test::Movable
        >();
    BOOST_TEST(value);

    value = ::xrn::ecs::System<detail::function8>::getSignature() ==
        ::xrn::ecs::Signature::generate<
            ::xrn::ecs::component::test::Movable,
            ::xrn::ecs::component::test::Transformable
        >();
    BOOST_TEST(value);

    value = ::xrn::ecs::System<detail::function9>::getSignature() ==
        ::xrn::ecs::Signature::generate<
            ::xrn::ecs::component::test::Movable
        >();
    BOOST_TEST(value);

    value = ::xrn::ecs::System<detail::function10>::getSignature() ==
        ::xrn::ecs::Signature::generate<
            ::xrn::ecs::component::test::Movable
        >();
    BOOST_TEST(value);
}


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
