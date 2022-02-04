#include <pch.hpp>
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

        Movable(
            const Movable&
        ) noexcept = delete;

        auto operator=(
            const Movable&
        ) noexcept
            -> Movable& = delete;

        Movable(
            Movable&&
        ) noexcept = default;

        auto operator=(
            Movable&&
        ) noexcept
            -> Movable& = default;

        bool operator==(const ::xrn::ecs::component::test::Movable& that) const {
            return this == &that;
        }

        int value{ 0 };
    };

    class Transformable
        : public ::xrn::ecs::AComponent<::xrn::ecs::component::test::Transformable>
    {
    public:
        Transformable(int v) : value{ v } {};
        ~Transformable() = default;

        int value{ 0 };
    };



} // namespace xrn::ecs::component::test




#include <boost/test/unit_test.hpp>
BOOST_AUTO_TEST_SUITE(Engine)
BOOST_AUTO_TEST_SUITE(Core)
BOOST_AUTO_TEST_SUITE(Ecs)
BOOST_AUTO_TEST_SUITE(Component)
BOOST_AUTO_TEST_SUITE(Container)



BOOST_AUTO_TEST_CASE(emplaceTwiceTheSameOnSameId)
{
    ::xrn::ecs::component::Container container;
    container.emplace<::xrn::ecs::component::test::Movable>(1);
    BOOST_CHECK_THROW(container.emplace<::xrn::ecs::component::test::Movable>(1), ::std::exception);
}

BOOST_AUTO_TEST_CASE(compareEmplaceRetValAndGetRetVal)
{
    ::xrn::ecs::component::Container container;
    const auto& movableComponent{ container.emplace<::xrn::ecs::component::test::Movable>(1) };
    BOOST_TEST((movableComponent == container.get<::xrn::ecs::component::test::Movable>(1)));
    BOOST_TEST((movableComponent.value == 0));

    container.emplace<::xrn::ecs::component::test::Transformable>(2, 3);
    BOOST_TEST((
        container.get<::xrn::ecs::component::test::Movable>(1).value + 3 ==
        container.get<::xrn::ecs::component::test::Transformable>(2).value
    ));
}

BOOST_AUTO_TEST_CASE(exists)
{
    ::xrn::ecs::component::Container container;
    container.emplace<::xrn::ecs::component::test::Movable>(1);
    container.emplace<::xrn::ecs::component::test::Transformable>(2, 3);
    BOOST_TEST((container.exists<::xrn::ecs::component::test::Movable>(1)));
    BOOST_TEST((container.exists<::xrn::ecs::component::test::Movable>(2)) == false);
    BOOST_TEST((container.exists<::xrn::ecs::component::test::Transformable>(1)) == false);
    BOOST_TEST((container.exists<::xrn::ecs::component::test::Transformable>(2)));
}

BOOST_AUTO_TEST_CASE(doenstExists)
{
    ::xrn::ecs::component::Container container;
    BOOST_TEST((!container.exists<::xrn::ecs::component::test::Movable>(1)));
}

BOOST_AUTO_TEST_CASE(getIndex)
{
    ::xrn::ecs::component::Container container;
    container.emplace<::xrn::ecs::component::test::Movable>(1);
    BOOST_TEST((container.getIndex<::xrn::ecs::component::test::Movable>(1) == 0));
}

BOOST_AUTO_TEST_CASE(multipleComponentValue)
{
    ::xrn::ecs::component::Container container;
    const auto& movableComponent{ container.emplace<::xrn::ecs::component::test::Movable>(1) };
    BOOST_TEST(container.get<::xrn::ecs::component::test::Movable>(1).value == 0);
    BOOST_TEST(movableComponent.value == 0);
    const auto& movableComponent2{ container.emplace<::xrn::ecs::component::test::Movable>(2) };
    BOOST_TEST(container.get<::xrn::ecs::component::test::Movable>(1).value == 0);
    BOOST_TEST(container.get<::xrn::ecs::component::test::Movable>(2).value == 0);
    BOOST_TEST(movableComponent2.value == 0);
}

BOOST_AUTO_TEST_CASE(push)
{
    ::xrn::ecs::component::Container container;
    container.push<::xrn::ecs::component::test::Movable>(
        1,
        ::xrn::ecs::component::test::Movable{}
    );
    container.push(2, ::xrn::ecs::component::test::Movable{});
    container.pushMany<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >(
        3,
        ::xrn::ecs::component::test::Movable{},
        ::xrn::ecs::component::test::Transformable{ 1 }
    );
    container.pushMany(
        4,
        ::xrn::ecs::component::test::Movable{},
        ::xrn::ecs::component::test::Transformable{ 5 }
    );
}



BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
