#include <pch.hpp>
#include <catch2/catch.hpp>
#include <xrn/Ecs/System/Detail/Meta/Function.hpp>

struct ComponentA {};
struct ComponentB {
    ComponentB(int val)
        : a{ val }
    {}
    int a;
};

static void func1(int) {}
auto lambda1{ [](int){} };

static int func2(int, float) { return 0; }
auto lambda2{ [](int, float) -> int { return 0; }};

static void func3(ComponentA) {}
auto lambda3{ [](ComponentA){} };

static void func4(ComponentA&, ComponentB&) {}
auto lambda4{ [](ComponentA&, ComponentB&){} };

static void func5(const ComponentA&, const ComponentB&) {}
auto lambda5{ [](const ComponentA&, const ComponentB&){} };



TEST_CASE("FunctionInfo.ReturnType", "FunctionInfo")
{
    REQUIRE((::std::is_same<::xrn::ecs::detail::meta::ComponentHelper<int, float, ComponentA, ComponentB>::
        template FunctionInfo<decltype(func1)>::Return::Type, void>::value));
    REQUIRE((::std::is_same<::xrn::ecs::detail::meta::ComponentHelper<int, float, ComponentA, ComponentB>::
        template FunctionInfo<decltype(lambda1)>::Return::Type, void>::value));

    REQUIRE((::std::is_same<::xrn::ecs::detail::meta::ComponentHelper<int, float, ComponentA, ComponentB>::
        template FunctionInfo<decltype(func2)>::Return::Type, int>::value));
    REQUIRE((::std::is_same<::xrn::ecs::detail::meta::ComponentHelper<int, float, ComponentA, ComponentB>::
        template FunctionInfo<decltype(lambda2)>::Return::Type, int>::value));
}

TEST_CASE("FunctionInfo.ArgumentsType", "FunctionInfo")
{
    REQUIRE((::std::is_same<::xrn::ecs::detail::meta::ComponentHelper<int, float, ComponentA, ComponentB>::
        template FunctionInfo<decltype(func3)>::Arguments::Type, ::std::tuple<ComponentA>>::value));
    REQUIRE((::std::is_same<::xrn::ecs::detail::meta::ComponentHelper<int, float, ComponentA, ComponentB>::
        template FunctionInfo<decltype(lambda3)>::Arguments::Type, ::std::tuple<ComponentA>>::value));
    bool value = ::std::is_same<::xrn::ecs::detail::meta::ComponentHelper<int, float, ComponentA, ComponentB>::
        template FunctionInfo<decltype(func4)>::Arguments::Type, ::std::tuple<ComponentA&, ComponentB&>>::value;
    REQUIRE(value);
    value = ::std::is_same<::xrn::ecs::detail::meta::ComponentHelper<int, float, ComponentA, ComponentB>::template FunctionInfo<decltype(lambda4)>::Arguments::Type,
        ::std::tuple<ComponentA&, ComponentB&>>::value;
    REQUIRE(value);
    REQUIRE((::std::is_same<
        ::xrn::ecs::detail::meta::ComponentHelper<int, float, ComponentA, ComponentB>::template FunctionInfo<decltype(func4)>::Arguments::Type,
        ::xrn::ecs::detail::meta::ComponentHelper<int, float, ComponentA, ComponentB>::template FunctionInfo<decltype(lambda4)>::Arguments::Type
    >::value));
    REQUIRE((::std::is_same<
        ::xrn::ecs::detail::meta::ComponentHelper<int, float, ComponentA, ComponentB>::template FunctionInfo<decltype(func5)>::Arguments::Type,
        ::xrn::ecs::detail::meta::ComponentHelper<int, float, ComponentA, ComponentB>::template FunctionInfo<decltype(lambda5)>::Arguments::Type
    >::value));
}

TEST_CASE("FunctionInfo.ArgumentsSignature", "FunctionInfo")
{
    auto value{ ::xrn::ecs::detail::meta::ComponentHelper<int, float, ComponentA, ComponentB>::
        template FunctionInfo<decltype(func3)>::Arguments::signature == ::xrn::ecs::Signature<int, float, ComponentA, ComponentB>::generate<ComponentA>() };
    REQUIRE(value);
    value = ::xrn::ecs::detail::meta::ComponentHelper<int, float, ComponentA, ComponentB>::
        template FunctionInfo<decltype(lambda3)>::Arguments::signature == ::xrn::ecs::Signature<int, float, ComponentA, ComponentB>::generate<ComponentA>();
    REQUIRE(value);

    value = ::xrn::ecs::detail::meta::ComponentHelper<int, float, ComponentA, ComponentB>::
        template FunctionInfo<decltype(func4)>::Arguments::signature == ::xrn::ecs::Signature<int, float, ComponentA, ComponentB>::generate<ComponentA, ComponentB>();
    REQUIRE(value);
    value = ::xrn::ecs::detail::meta::ComponentHelper<int, float, ComponentA, ComponentB>::
        template FunctionInfo<decltype(lambda4)>::Arguments::signature == ::xrn::ecs::Signature<int, float, ComponentA, ComponentB>::generate<ComponentA, ComponentB>();
    REQUIRE(value);
}

TEST_CASE("FunctionInfo.ArgumentsAreConst", "FunctionInfo")
{
    auto value{ ::xrn::ecs::detail::meta::ComponentHelper<int, float, ComponentA, ComponentB>::
        template FunctionInfo<decltype(func3)>::Arguments::areConst };
    REQUIRE(value);

    value = ::xrn::ecs::detail::meta::ComponentHelper<int, float, ComponentA, ComponentB>::
        template FunctionInfo<decltype(func4)>::Arguments::areConst;
    REQUIRE(!value);

    value = ::xrn::ecs::detail::meta::ComponentHelper<int, float, ComponentA, ComponentB>::
        template FunctionInfo<decltype(func5)>::Arguments::areConst;
    REQUIRE(value);

    value = ::xrn::ecs::detail::meta::ComponentHelper<int, float, ComponentA, ComponentB>::
        template FunctionInfo<decltype(lambda5)>::Arguments::areConst;
    REQUIRE(value);
}
