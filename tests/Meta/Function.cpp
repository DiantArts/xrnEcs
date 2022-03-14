#include <pch.hpp>
#include <Ecs/System/Detail/Meta/Function.hpp>

static void func1(int) {}
auto lambda1{ [](int){} };

static int func2(int, float) { return 0; }
auto lambda2{ [](int, float) -> int { return 0; }};

static void func3(::xrn::ecs::component::test::ComponentA) {}
auto lambda3{ [](::xrn::ecs::component::test::ComponentA){} };

static void func4(
    ::xrn::ecs::component::test::ComponentA&,
    ::xrn::ecs::component::test::ComponentB&
) {}
auto lambda4{ [](
    ::xrn::ecs::component::test::ComponentA&,
    ::xrn::ecs::component::test::ComponentB&
){} };

static void func5(
    const ::xrn::ecs::component::test::ComponentA&,
    const ::xrn::ecs::component::test::ComponentB&
) {}
auto lambda5{ [](
    const ::xrn::ecs::component::test::ComponentA&,
    const ::xrn::ecs::component::test::ComponentB&
){} };



#include <boost/test/unit_test.hpp>
BOOST_AUTO_TEST_SUITE(Engine)
BOOST_AUTO_TEST_SUITE(Core)
BOOST_AUTO_TEST_SUITE(Detail)
BOOST_AUTO_TEST_SUITE(Meta)
BOOST_AUTO_TEST_SUITE(Function)



BOOST_AUTO_TEST_CASE(ReturnType)
{
    BOOST_TEST((::std::is_same<::xrn::ecs::detail::meta::Function<decltype(func1)>::Return::Type,
        void>::value));
    BOOST_TEST((::std::is_same<::xrn::ecs::detail::meta::Function<decltype(lambda1)>::Return::Type,
        void>::value));

    BOOST_TEST((::std::is_same<::xrn::ecs::detail::meta::Function<decltype(func2)>::Return::Type,
        int>::value));
    BOOST_TEST((::std::is_same<::xrn::ecs::detail::meta::Function<decltype(lambda2)>::Return::Type,
        int>::value));
}

BOOST_AUTO_TEST_CASE(ArgumentsType)
{
    BOOST_TEST((::std::is_same<::xrn::ecs::detail::meta::Function<decltype(func3)>::Arguments::Type,
        ::std::tuple<::xrn::ecs::component::test::ComponentA>>::value));
    BOOST_TEST((::std::is_same<::xrn::ecs::detail::meta::Function<decltype(lambda3)>::Arguments::Type,
        ::std::tuple<::xrn::ecs::component::test::ComponentA>>::value));
    bool value = ::std::is_same<::xrn::ecs::detail::meta::Function<decltype(func4)>::Arguments::Type,
        ::std::tuple<
            ::xrn::ecs::component::test::ComponentA&,
            ::xrn::ecs::component::test::ComponentB&
        >>::value;
    BOOST_TEST(value);
    value = ::std::is_same<::xrn::ecs::detail::meta::Function<decltype(lambda4)>::Arguments::Type,
        ::std::tuple<
            ::xrn::ecs::component::test::ComponentA&,
            ::xrn::ecs::component::test::ComponentB&
        >>::value;
    BOOST_TEST(value);
    BOOST_TEST((::std::is_same<
        ::xrn::ecs::detail::meta::Function<decltype(func4)>::Arguments::Type,
        ::xrn::ecs::detail::meta::Function<decltype(lambda4)>::Arguments::Type
    >::value));
    BOOST_TEST((::std::is_same<
        ::xrn::ecs::detail::meta::Function<decltype(func5)>::Arguments::Type,
        ::xrn::ecs::detail::meta::Function<decltype(lambda5)>::Arguments::Type
    >::value));
}

BOOST_AUTO_TEST_CASE(ArgumentsSignature)
{
    auto value{ ::xrn::ecs::detail::meta::Function<decltype(func3)>::Arguments::signature ==
        ::xrn::ecs::Signature::generate<::xrn::ecs::component::test::ComponentA>() };
    BOOST_TEST(value);
    value = ::xrn::ecs::detail::meta::Function<decltype(lambda3)>::Arguments::signature ==
        ::xrn::ecs::Signature::generate<::xrn::ecs::component::test::ComponentA>();
    BOOST_TEST(value);

    value = ::xrn::ecs::detail::meta::Function<decltype(func4)>::Arguments::signature ==
        ::xrn::ecs::Signature::generate<
            ::xrn::ecs::component::test::ComponentA,
            ::xrn::ecs::component::test::ComponentB
        >();
    BOOST_TEST(value);
    value = ::xrn::ecs::detail::meta::Function<decltype(lambda4)>::Arguments::signature ==
        ::xrn::ecs::Signature::generate<
            ::xrn::ecs::component::test::ComponentA,
            ::xrn::ecs::component::test::ComponentB
        >();
    BOOST_TEST(value);
}

BOOST_AUTO_TEST_CASE(ArgumentsAreConst)
{
    auto value{ ::xrn::ecs::detail::meta::Function<decltype(func3)>::Arguments::areConst };
    BOOST_TEST(value);

    value = ::xrn::ecs::detail::meta::Function<decltype(func4)>::Arguments::areConst;
    BOOST_TEST(!value);

    value = ::xrn::ecs::detail::meta::Function<decltype(func5)>::Arguments::areConst;
    BOOST_TEST(value);

    value = ::xrn::ecs::detail::meta::Function<decltype(lambda5)>::Arguments::areConst;
    BOOST_TEST(value);
}



BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
