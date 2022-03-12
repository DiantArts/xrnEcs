#include <pch.hpp>
#include <Ecs/Entity.hpp>
#include <Ecs/Component.hpp>
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
BOOST_AUTO_TEST_SUITE(ConstReferenre)



// ------------------------------------------------------------------ Component
BOOST_AUTO_TEST_SUITE(Component)



BOOST_AUTO_TEST_CASE(addNhas)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity entity;
    ::xrn::ecs::Entity::ConstReference ref{ entity };
    entity.addComponent<::xrn::ecs::component::test::Movable>(components);

    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::Movable>());
    BOOST_TEST(ref.hasComponent<::xrn::ecs::component::test::Movable>());
    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::Transformable>());
    BOOST_TEST(!ref.hasComponent<::xrn::ecs::component::test::Transformable>());
}

BOOST_AUTO_TEST_CASE(removeNhas)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity entity;
    ::xrn::ecs::Entity::ConstReference ref{ entity };

    entity.addComponent<::xrn::ecs::component::test::Movable>(components);
    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::Movable>());
    BOOST_TEST(ref.hasComponent<::xrn::ecs::component::test::Movable>());
    BOOST_TEST(components.exists<::xrn::ecs::component::test::Movable>(entity.getId()));
    BOOST_TEST(components.exists<::xrn::ecs::component::test::Movable>(ref.getId()));

    entity.removeComponent<::xrn::ecs::component::test::Movable>(components);
    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::Movable>());
    BOOST_TEST(!ref.hasComponent<::xrn::ecs::component::test::Movable>());
    BOOST_TEST(!components.exists<::xrn::ecs::component::test::Movable>(entity.getId()));
    BOOST_TEST(!components.exists<::xrn::ecs::component::test::Movable>(ref.getId()));
}



BOOST_AUTO_TEST_SUITE_END()
// ------------------------------------------------------------------ Signature
BOOST_AUTO_TEST_SUITE(Signature)



BOOST_AUTO_TEST_CASE(single)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity entity;
    ::xrn::ecs::Entity::ConstReference ref{ entity };

    entity.addComponent<::xrn::ecs::component::test::Movable>(components);
    auto signature{ ::xrn::ecs::Signature::generate<::xrn::ecs::component::test::Movable>() };

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
    ::xrn::ecs::Entity entity;
    ::xrn::ecs::Entity::ConstReference ref{ entity };

    BOOST_TEST(entity.getId() == ref.getId());
    BOOST_TEST(&entity == &ref.get());
    BOOST_TEST(&entity == &static_cast<const ::xrn::ecs::Entity&>(ref));
}



BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
