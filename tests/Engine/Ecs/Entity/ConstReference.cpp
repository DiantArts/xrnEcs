#include <pch.hpp>
#include <xrn/Ecs/Entity.hpp>
#include <xrn/Ecs/Component.hpp>
#include <xrn/Ecs/Component/Container.hpp>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>
#pragma GCC diagnostic pop
BOOST_AUTO_TEST_SUITE(Engine)
BOOST_AUTO_TEST_SUITE(Core)
BOOST_AUTO_TEST_SUITE(Ecs)
BOOST_AUTO_TEST_SUITE(Entity)
BOOST_AUTO_TEST_SUITE(ConstReferenre)



// ------------------------------------------------------------------ Component
BOOST_AUTO_TEST_SUITE(Component)



BOOST_AUTO_TEST_CASE(addNhas)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Entity entity;
    ::xrn::ecs::entity::ConstReference ref{ entity };
    entity.addComponent<::xrn::ecs::component::test::ComponentA>(components);

    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(ref.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::ComponentB>());
    BOOST_TEST(!ref.hasComponent<::xrn::ecs::component::test::ComponentB>());
}

BOOST_AUTO_TEST_CASE(removeNhas)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Entity entity;
    ::xrn::ecs::entity::ConstReference ref{ entity };

    entity.addComponent<::xrn::ecs::component::test::ComponentA>(components);
    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(ref.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(components.contains<::xrn::ecs::component::test::ComponentA>(entity.getId()));
    BOOST_TEST(components.contains<::xrn::ecs::component::test::ComponentA>(ref.getId()));

    entity.removeComponent<::xrn::ecs::component::test::ComponentA>(components);
    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(!ref.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(!components.contains<::xrn::ecs::component::test::ComponentA>(entity.getId()));
    BOOST_TEST(!components.contains<::xrn::ecs::component::test::ComponentA>(ref.getId()));
}



BOOST_AUTO_TEST_SUITE_END()
// ------------------------------------------------------------------ Signature
BOOST_AUTO_TEST_SUITE(Signature)



BOOST_AUTO_TEST_CASE(single)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Entity entity;
    ::xrn::ecs::entity::ConstReference ref{ entity };

    entity.addComponent<::xrn::ecs::component::test::ComponentA>(components);
    auto signature{ ::xrn::ecs::Signature::generate<::xrn::ecs::component::test::ComponentA>() };

    BOOST_TEST((entity.getSignature() == signature));
    BOOST_TEST((ref.getSignature() == signature));
    BOOST_TEST((ref.getSignature() == entity.getSignature()));
    BOOST_TEST((&ref.getSignature() == &entity.getSignature()));
}



BOOST_AUTO_TEST_SUITE_END()
// ------------------------------------------------------------------ Signature
BOOST_AUTO_TEST_SUITE(Id)



BOOST_AUTO_TEST_CASE(incrementation)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Entity entity;
    ::xrn::ecs::entity::ConstReference ref{ entity };

    BOOST_TEST(entity.getId() == ref.getId());
    BOOST_TEST(&entity == &ref.get());
    BOOST_TEST(&entity == &static_cast<const ::xrn::ecs::entity::Entity&>(ref));
}

BOOST_AUTO_TEST_CASE(example)
{
    using namespace ::xrn::ecs::component::test;

    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Entity entity;
    ::xrn::ecs::entity::ConstReference ref{ entity };

    BOOST_TEST(!entity.hasComponent<ComponentA>());
    BOOST_TEST(!ref.hasComponent<ComponentA>());
    BOOST_TEST(!entity.hasComponent<ComponentB>());
    BOOST_TEST(!ref.hasComponent<ComponentB>());
    entity.addComponents<ComponentA, ComponentB>(components);
    BOOST_TEST((entity.hasComponents<ComponentA, ComponentB>()));
    BOOST_TEST((ref.hasComponents<ComponentA, ComponentB>()));
}



BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
