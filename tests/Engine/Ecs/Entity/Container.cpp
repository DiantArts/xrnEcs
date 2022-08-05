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
BOOST_AUTO_TEST_SUITE(Container)



BOOST_AUTO_TEST_CASE(get)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    const auto& constEntities{ entities };
    auto entity1{ entities.emplace<::xrn::ecs::component::test::Movable>() };
    auto entity2{ entities.get(entity1.getId()) };
    auto entity3{ entities[entity1.getId()] };

    BOOST_TEST(entities.contains(entity1.getId()));
    BOOST_TEST(&entities.unsafeGet(entity1.getId()).get() == &entity1.get());
    BOOST_TEST(constEntities.contains(entity1.getId()));
    BOOST_TEST(&constEntities.unsafeGet(entity1.getId()).get() == &entity1.get());
    BOOST_TEST(&entity1.get() == &entity2.get());
    BOOST_TEST(&entity1.get() == &entity3.get());
}


// ------------------------------------------------------------------ emplace
BOOST_AUTO_TEST_SUITE(emplace)



BOOST_AUTO_TEST_CASE(singleComponent)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    auto entity{ entities.emplace<::xrn::ecs::component::test::Movable>() };

    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::Movable>());
    BOOST_TEST(!entity.hasComponent<::xrn::ecs::component::test::Transformable>());
}

BOOST_AUTO_TEST_CASE(multipleComponent)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    auto entity{ entities.emplace<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >() };

    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::Movable>());
    BOOST_TEST(entity.hasComponent<::xrn::ecs::component::test::Transformable>());
}




BOOST_AUTO_TEST_SUITE_END()
// ------------------------------------------------------------------ remove
BOOST_AUTO_TEST_SUITE(remove)



BOOST_AUTO_TEST_CASE(remove)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    auto entityId{ entities.emplace<::xrn::ecs::component::test::Movable>().getId() };
    auto entityId2{ entities.emplace<::xrn::ecs::component::test::Movable>().getId() };
    auto entityId3{ entities.emplace<::xrn::ecs::component::test::Movable>().getId() };
    auto entityId4{ entities.emplace<::xrn::ecs::component::test::Movable>().getId() };
    BOOST_TEST(entities.contains(entityId));
    entities.remove(entityId);
    BOOST_TEST(!entities.contains(entityId));
    BOOST_TEST(entities.contains(entityId2));
    entities.remove(entities[entityId2]);
    BOOST_TEST(!entities.contains(entityId2));
    BOOST_TEST(entities.contains(entityId3));
    const auto& constEntities{ entities };
    entities.remove(constEntities.get(entityId3));
    BOOST_TEST(!entities.contains(entityId3));
    BOOST_TEST(entities.contains(entityId4));
    entities.remove(constEntities[entityId4]);
    BOOST_TEST(!entities.contains(entityId4));
}



BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(other)
{
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    const auto& constEntities{ entities };
    BOOST_TEST(!entities[::xrn::Id{ 1 }].isValid());
    BOOST_TEST(!constEntities[::xrn::Id{ 1 }].isValid());
    BOOST_TEST(!entities.get(::xrn::Id{ 1 }).isValid());
    BOOST_TEST(!constEntities.get(::xrn::Id{ 1 }).isValid());

    BOOST_TEST(&*entities.cbegin() == &*entities.begin());
    BOOST_TEST(&*constEntities.cbegin() == &*constEntities.begin());
    BOOST_TEST(&*entities.cend() == &*entities.end());
    BOOST_TEST(&*constEntities.cend() == &*constEntities.end());
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
