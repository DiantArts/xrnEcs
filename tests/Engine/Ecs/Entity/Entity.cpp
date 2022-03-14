#include <pch.hpp>
#include <Ecs/Entity.hpp>
#include <Ecs/Component.hpp>
#include <Ecs/Component/Container.hpp>
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

    entity.addComponent<::xrn::ecs::component::test::ComponentA>(components);
    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::ComponentB>());
}

BOOST_AUTO_TEST_CASE(addNhas2)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity entity;
    entity.addComponent<::xrn::ecs::component::test::ComponentB>(components);

    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::ComponentB>());
}

BOOST_AUTO_TEST_CASE(removeNhas)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity entity;
    entity.addComponent<::xrn::ecs::component::test::ComponentA>(components);

    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(components.contains<::xrn::ecs::component::test::ComponentA>(entity.getId()));

    entity.removeComponent<::xrn::ecs::component::test::ComponentA>(components);
    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(!components.contains<::xrn::ecs::component::test::ComponentA>(entity.getId()));
}

BOOST_AUTO_TEST_CASE(addNhasMulti1)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity entity;
    entity.addComponent<::xrn::ecs::component::test::ComponentA>(components);
    entity.addComponent<::xrn::ecs::component::test::ComponentB>(components);

    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::ComponentB>());
}

BOOST_AUTO_TEST_CASE(addNhasMulti2)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity entity;
    entity.addComponents<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >(components);

    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::ComponentB>());
    BOOST_TEST((entity.hasComponents<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >()));
}

BOOST_AUTO_TEST_CASE(addNhasMulti3)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity entity;
    entity.addComponents<
        ::xrn::ecs::component::test::ComponentB
    >(components);

    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::ComponentB>());
    BOOST_TEST(!(entity.hasComponents<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >()));
}

BOOST_AUTO_TEST_CASE(generate)
{
    ::xrn::ecs::component::Container components;
    auto entity{ ::xrn::ecs::Entity::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >(components) };

    BOOST_TEST((entity.hasComponents<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >()));
}

BOOST_AUTO_TEST_CASE(removeNhasMulti1)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity entity;
    entity.addComponents<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >(components);

    BOOST_TEST((entity.hasComponents<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >()));
    entity.removeComponent<::xrn::ecs::component::test::ComponentA>(components);
    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::ComponentB>());
    entity.removeComponent<::xrn::ecs::component::test::ComponentB>(components);
    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::ComponentB>());
}

BOOST_AUTO_TEST_CASE(removeNhasMulti2)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity entity;
    entity.addComponents<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >(components);

    BOOST_TEST((entity.hasComponents<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >()));
    entity.removeComponents<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >(components);
    BOOST_TEST(!(entity.hasComponents<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >()));
    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::ComponentB>());
}



BOOST_AUTO_TEST_SUITE_END()
// ------------------------------------------------------------------ Signature
BOOST_AUTO_TEST_SUITE(Signature)



BOOST_AUTO_TEST_CASE(single)
{
    ::xrn::ecs::component::Container components;
    auto entity{ ::xrn::ecs::Entity::generate<::xrn::ecs::component::test::ComponentA>(components) };
    auto signature{ ::xrn::ecs::Signature::generate<::xrn::ecs::component::test::ComponentA>() };

    BOOST_TEST((entity.getSignature() == signature));
}

BOOST_AUTO_TEST_CASE(multi)
{
    ::xrn::ecs::component::Container components;
    auto entity{ ::xrn::ecs::Entity::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >(components) };
    auto signature{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
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
