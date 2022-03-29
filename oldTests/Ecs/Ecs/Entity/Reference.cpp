#include <pch.hpp>
#include <xrn/Ecs/Entity.hpp>
#include <xrn/Ecs/Component.hpp>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>
#pragma GCC diagnostic pop
BOOST_AUTO_TEST_SUITE(Engine)
BOOST_AUTO_TEST_SUITE(Core)
BOOST_AUTO_TEST_SUITE(Ecs)
BOOST_AUTO_TEST_SUITE(Entity)
BOOST_AUTO_TEST_SUITE(Referenre)



// ------------------------------------------------------------------ Component
BOOST_AUTO_TEST_SUITE(Component)



BOOST_AUTO_TEST_CASE(addNhas)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Entity entity;
    ::xrn::ecs::entity::Reference ref{ components, entity };
    ref.addComponent<::xrn::ecs::component::test::ComponentA>();

    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(ref.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::ComponentB>());
    BOOST_TEST(!ref.hasComponent<::xrn::ecs::component::test::ComponentB>());
}

BOOST_AUTO_TEST_CASE(addNhas2)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Entity entity;
    ::xrn::ecs::entity::Reference ref{ entity, components };
    ref.addComponents(::xrn::ecs::component::test::ComponentB{});

    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(!ref.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::ComponentB>());
    BOOST_TEST(ref.hasComponent<::xrn::ecs::component::test::ComponentB>());
}

BOOST_AUTO_TEST_CASE(removeNhas)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Entity entity;
    ::xrn::ecs::entity::Reference ref{ components, entity };

    ref.addComponent<::xrn::ecs::component::test::ComponentA>();
    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(ref.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(components.contains<::xrn::ecs::component::test::ComponentA>(entity.getId()));
    BOOST_TEST(components.contains<::xrn::ecs::component::test::ComponentA>(ref.getId()));

    ref.removeComponent<::xrn::ecs::component::test::ComponentA>();
    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(!ref.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(!components.contains<::xrn::ecs::component::test::ComponentA>(entity.getId()));
    BOOST_TEST(!components.contains<::xrn::ecs::component::test::ComponentA>(ref.getId()));

    ref.addComponents<::xrn::ecs::component::test::ComponentA, ::xrn::ecs::component::test::ComponentB>();
    BOOST_TEST(ref.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(ref.hasComponent<::xrn::ecs::component::test::ComponentB>());
    ref.removeComponents();
    BOOST_TEST(!ref.hasComponent<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(!ref.hasComponent<::xrn::ecs::component::test::ComponentB>());

    ref.addAbilities<::xrn::ecs::component::test::AbilityA, ::xrn::ecs::component::test::AbilityB>();
    BOOST_TEST(ref.hasAbility<::xrn::ecs::component::test::AbilityA>());
    BOOST_TEST(ref.hasAbility<::xrn::ecs::component::test::AbilityB>());
    ref.removeAbilities();
    BOOST_TEST(!ref.hasAbility<::xrn::ecs::component::test::AbilityA>());
    BOOST_TEST(!ref.hasAbility<::xrn::ecs::component::test::AbilityB>());

    ref.add<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB,
        ::xrn::ecs::component::test::AbilityA,
        ::xrn::ecs::component::test::AbilityB
    >();
    BOOST_TEST((ref.has<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB,
        ::xrn::ecs::component::test::AbilityA,
        ::xrn::ecs::component::test::AbilityB
    >()));
    ref.removeAbilitiesAndComponents();
    BOOST_TEST((!ref.has<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB,
        ::xrn::ecs::component::test::AbilityA,
        ::xrn::ecs::component::test::AbilityB
    >()));
}



BOOST_AUTO_TEST_SUITE_END()
// ------------------------------------------------------------------ Signature
BOOST_AUTO_TEST_SUITE(Signature)



BOOST_AUTO_TEST_CASE(single)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Entity entity;
    ::xrn::ecs::entity::Reference ref{ components, entity };

    ref.addComponent<::xrn::ecs::component::test::ComponentA>();
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
    ::xrn::ecs::entity::Reference ref{components, entity};

    BOOST_TEST(entity.getId() == ref.getId());
}



BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(others)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Entity entity;
    ::xrn::ecs::entity::Reference ref{ components, entity };
    const ::xrn::ecs::entity::Reference constNonConstRef{ components, entity };
    const ::xrn::ecs::entity::Reference constMutableRef{ components, entity };
    ::xrn::ecs::entity::ConstReference constRef{ ref };
    const ::xrn::ecs::entity::Entity& entityRef = ref; // operator=() avoids copy for some reasons lmao

    BOOST_TEST(&entity == &static_cast<const ::xrn::ecs::entity::Entity&>(ref));
    BOOST_TEST(entity.getId() == constMutableRef.getId());
    BOOST_TEST(&constRef.get() == &ref.get());
    BOOST_TEST(&constRef.get() == &entity);
    BOOST_TEST(&constRef.get() == &entityRef);
    BOOST_TEST(&constNonConstRef.get() == &entityRef);
}

BOOST_AUTO_TEST_CASE(example)
{
    using namespace ::xrn::ecs::component::test;

    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Entity entity;
    ::xrn::ecs::entity::Reference ref{ components, entity };

    BOOST_TEST(!entity.hasComponent<ComponentA>());
    BOOST_TEST(!ref.hasComponent<ComponentA>());
    BOOST_TEST(!entity.hasComponent<ComponentB>());
    BOOST_TEST(!ref.hasComponent<ComponentB>());
    ref.addComponents<ComponentA, ComponentB>();
    BOOST_TEST((entity.hasComponents<ComponentA, ComponentB>()));
    BOOST_TEST((ref.hasComponents<ComponentA, ComponentB>()));
}


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
