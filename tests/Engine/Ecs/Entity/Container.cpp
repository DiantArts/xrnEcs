#include <pch.hpp>
#include <Ecs/Entity/Container.hpp>
#include <Ecs/AComponent.hpp>
#include <Ecs/Component/Container.hpp>
#include <Ecs/Entity/ConstReference.hpp>



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
    auto entity1{ entities.emplace<::xrn::ecs::component::test::Movable>() };
    auto entity2{ entities.get(entity1.getId()) };
    auto entity3{ entities[entity1.getId()] };

    BOOST_TEST(entities.contains(entity1.getId()));
    BOOST_TEST(&entities.unsafeGet(entity1.getId()).get() == &entity1.get());
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
    BOOST_TEST(entities.contains(entityId));
    entities.remove(entityId);
    BOOST_TEST(!entities.contains(entityId));
}



BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
