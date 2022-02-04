#include <pch.hpp>
#include <Ecs/Entity.hpp>
#include <Ecs/AComponent.hpp>
#include <Ecs/Component/Container.hpp>



// ------------------------------------------------------------------ Class test

namespace xrn::ecs::component::test {



    class Movable
        : public ::xrn::ecs::AComponent<::xrn::ecs::component::test::Movable>
    {
    public:
        Movable() = default;
        ~Movable() = default;

        bool operator==(const ::xrn::ecs::component::test::Movable& that) const {
            return this == &that;
        }

    };

    class Transformable
        : public ::xrn::ecs::AComponent<::xrn::ecs::component::test::Transformable>
    {
    public:
        Transformable() = default;
        ~Transformable() = default;

    };



} // namespace xrn::ecs::component::test



#include <boost/test/unit_test.hpp>
BOOST_AUTO_TEST_SUITE(Engine)
BOOST_AUTO_TEST_SUITE(Core)
BOOST_AUTO_TEST_SUITE(Ecs)
BOOST_AUTO_TEST_SUITE(Entity)



// ------------------------------------------------------------------ Component
BOOST_AUTO_TEST_SUITE(Component)



BOOST_AUTO_TEST_CASE(addNhas1)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity entity;
    const auto& component{ entity.addComponent<::xrn::ecs::component::test::Movable>(components) };

    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::Movable>());
    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::Transformable>());
    BOOST_TEST(&component == &components.get<::xrn::ecs::component::test::Movable>(entity.getId()));
}

BOOST_AUTO_TEST_CASE(addNhas2)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity entity;
    const auto& component{ entity.addComponent<::xrn::ecs::component::test::Transformable>(components) };

    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::Movable>());
    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::Transformable>());
    BOOST_TEST(&component == &components.get<::xrn::ecs::component::test::Transformable>(entity.getId()));
}

BOOST_AUTO_TEST_CASE(removeNhas)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity entity;
    entity.addComponent<::xrn::ecs::component::test::Movable>(components);

    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::Movable>());
    BOOST_TEST(components.exists<::xrn::ecs::component::test::Movable>(entity.getId()));

    entity.removeComponent<::xrn::ecs::component::test::Movable>(components);
    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::Movable>());
    BOOST_TEST(!components.exists<::xrn::ecs::component::test::Movable>(entity.getId()));
}

BOOST_AUTO_TEST_CASE(addNhasMulti1)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity entity;
    const auto& comp1{ entity.addComponent<::xrn::ecs::component::test::Movable>(components) };
    const auto& comp2{ entity.addComponent<::xrn::ecs::component::test::Transformable>(components) };

    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::Movable>());
    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::Transformable>());

    BOOST_TEST(&comp1 == &components.get<::xrn::ecs::component::test::Movable>(entity.getId()));
    BOOST_TEST(&comp2 == &components.get<::xrn::ecs::component::test::Transformable>(entity.getId()));
}

BOOST_AUTO_TEST_CASE(addNhasMulti2)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity entity;
    entity.addComponents<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >(components);

    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::Movable>());
    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::Transformable>());
    BOOST_TEST((entity.hasComponents<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >()));
}

BOOST_AUTO_TEST_CASE(addNhasMulti3)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity entity;
    entity.addComponents<
        ::xrn::ecs::component::test::Transformable
    >(components);

    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::Movable>());
    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::Transformable>());
    BOOST_TEST(!(entity.hasComponents<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >()));
}

BOOST_AUTO_TEST_CASE(generate)
{
    ::xrn::ecs::component::Container components;
    auto entity{ ::xrn::ecs::Entity::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >(components) };

    BOOST_TEST((entity.hasComponents<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >()));
}

BOOST_AUTO_TEST_CASE(removeNhasMulti1)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity entity;
    entity.addComponents<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >(components);

    BOOST_TEST((entity.hasComponents<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >()));
    entity.removeComponent<::xrn::ecs::component::test::Movable>(components);
    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::Movable>());
    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::Transformable>());
    entity.removeComponent<::xrn::ecs::component::test::Transformable>(components);
    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::Movable>());
    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::Transformable>());
}

BOOST_AUTO_TEST_CASE(removeNhasMulti2)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity entity;
    entity.addComponents<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >(components);

    BOOST_TEST((entity.hasComponents<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >()));
    entity.removeComponents<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >(components);
    BOOST_TEST(!(entity.hasComponents<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >()));
    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::Movable>());
    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::Transformable>());
}



BOOST_AUTO_TEST_SUITE_END()
// ------------------------------------------------------------------ Signature
BOOST_AUTO_TEST_SUITE(Signature)



BOOST_AUTO_TEST_CASE(single)
{
    ::xrn::ecs::component::Container components;
    auto entity{ ::xrn::ecs::Entity::generate<::xrn::ecs::component::test::Movable>(components) };
    auto signature{ ::xrn::ecs::Signature::generate<::xrn::ecs::component::test::Movable>() };

    BOOST_TEST((entity.getSignature() == signature));
}

BOOST_AUTO_TEST_CASE(multi)
{
    ::xrn::ecs::component::Container components;
    auto entity{ ::xrn::ecs::Entity::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >(components) };
    auto signature{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >() };

    BOOST_TEST((entity.getSignature() == signature));
}



BOOST_AUTO_TEST_SUITE_END()
// ------------------------------------------------------------------ Signature
BOOST_AUTO_TEST_SUITE(Id)



BOOST_AUTO_TEST_CASE(incrementation)
{
    ::xrn::ecs::Entity entity1, entity2, entity3;

    BOOST_TEST(entity1.getId() == entity2.getId() - 1);
    BOOST_TEST(entity1.getId() == entity3.getId() - 2);
    BOOST_TEST(entity2.getId() == entity3.getId() - 1);
}



BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
