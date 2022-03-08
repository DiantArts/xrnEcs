#include <pch.hpp>
#include <Ecs/System/Container.hpp>



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
        ::xrn::ecs::component::test::Movable& m
    ) {
        ++m.value;
    }
    static auto lambda1{
        [](
            ::xrn::ecs::component::test::Movable& m
        ) {
            ++m.value;
        }
    };

    static int function2(
        ::xrn::ecs::component::test::Transformable& t
    )
    {
        ++t.value;
        return 0;
    }
    static auto lambda2{
        [](
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

}



#include <boost/test/unit_test.hpp>
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
    auto e1Id{ entities.emplace<::xrn::ecs::component::test::Movable>().getId() };
    auto e2Id{ entities.emplace<::xrn::ecs::component::test::Transformable>().getId() };
    auto e3Id{ entities.emplace<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >().getId() };
    ::xrn::ecs::system::Container systems;

    systems.emplace<detail::function1>();
    systems.run(c.getElapsed(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 0);

    systems.run(c.getElapsed(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 0);

    systems.emplace<detail::function2>();
    systems.run(c.getElapsed(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 1);

    systems.emplace<detail::function3>();
    systems.run(c.getElapsed(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 4);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 5);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 3);
}

BOOST_AUTO_TEST_CASE(lambdaMulpiteComponentMulipleEntityMulipleSystem)
{
    ::xrn::Clock c;
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    auto e1Id{ entities.emplace<::xrn::ecs::component::test::Movable>().getId() };
    auto e2Id{ entities.emplace<::xrn::ecs::component::test::Transformable>().getId() };
    auto e3Id{ entities.emplace<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >().getId() };
    ::xrn::ecs::system::Container systems;

    systems.emplace<detail::lambda1>();
    systems.run(c.getElapsed(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 0);

    systems.run(c.getElapsed(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 0);

    systems.emplace<detail::lambda2>();
    systems.run(c.getElapsed(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 1);

    systems.emplace<detail::lambda3>();
    systems.run(c.getElapsed(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 4);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 5);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 3);
}

BOOST_AUTO_TEST_CASE(inlineLambdaMulpiteComponentMulipleEntityMulipleSystem)
{
    ::xrn::Clock c;
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    auto e1Id{ entities.emplace<::xrn::ecs::component::test::Movable>().getId() };
    auto e2Id{ entities.emplace<::xrn::ecs::component::test::Transformable>().getId() };
    auto e3Id{ entities.emplace<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >().getId() };
    ::xrn::ecs::system::Container systems;

    systems.emplace<[](::xrn::ecs::component::test::Movable& m) { ++m.value;}>();
    systems.run(c.getElapsed(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 0);

    systems.run(c.getElapsed(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 0);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 0);

    systems.emplace<[](::xrn::ecs::component::test::Transformable& t) -> int
        { ++t.value; return 0; }>();
    systems.run(c.getElapsed(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 1);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 3);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 1);

    systems.emplace<[](
            ::xrn::ecs::component::test::Movable& m,
            ::xrn::ecs::component::test::Transformable& t
        ) {
            ++m.value;
            ++t.value;
        }>();
    systems.run(c.getElapsed(), entities, components);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e1Id).value == 4);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e2Id).value == 2);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Movable>(e3Id).value == 5);
    BOOST_TEST(components.get<::xrn::ecs::component::test::Transformable>(e3Id).value == 3);
}



BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
