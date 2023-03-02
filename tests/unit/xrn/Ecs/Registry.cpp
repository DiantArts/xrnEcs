#include <pch.hpp>
#include <gtest/gtest.h>
#include <xrn/Ecs/Detail/Function.hpp>

struct ComponentA {};
struct ComponentB {
    ComponentB(int val)
        : a{ val }
    {}
    int a;
};

static void func1(int) {}
static auto lambda1{ [](int){} };

static int func2(int, float) { return 0; }
static auto lambda2{ [](int, float) -> int { return 0; }};

static void func3(ComponentA) {}
static auto lambda3{ [](ComponentA){} };

static void func4(ComponentA&, ComponentB&) {}
static auto lambda4{ [](ComponentA&, ComponentB&){} };

static void func5(const ComponentA&, const ComponentB&) {}
static auto lambda5{ [](const ComponentA&, const ComponentB&){} };

void funcRemoveWarn()
{
    int a{ 0 };
    float b{ 0.0f };
    ComponentA c;
    ComponentB d{ 1 };

    func1(a);
    lambda1(a);
    func2(a, b);
    lambda2(a, b);
    func3(c);
    lambda3(c);
    func4(c, d);
    lambda4(c, d);
    func5(c, d);
    lambda5(c, d);
}



TEST(Registry, ReturnType)
{
    EXPECT_TRUE((::std::is_same<::xrn::ecs::detail::Function<int, float, ComponentA, ComponentB>::
        template Information<func1>::Return::Type, void>::value));
    EXPECT_TRUE((::std::is_same<::xrn::ecs::detail::Function<int, float, ComponentA, ComponentB>::
        template Information<lambda1>::Return::Type, void>::value));

    EXPECT_TRUE((::std::is_same<::xrn::ecs::detail::Function<int, float, ComponentA, ComponentB>::
        template Information<func2>::Return::Type, int>::value));
    EXPECT_TRUE((::std::is_same<::xrn::ecs::detail::Function<int, float, ComponentA, ComponentB>::
        template Information<lambda2>::Return::Type, int>::value));
}
