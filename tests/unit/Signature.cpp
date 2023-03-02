#include <pch.hpp>
#include <gtest/gtest.h>
#include <xrn/Ecs/Signature.hpp>
#include <xrn/Ecs/Registry.hpp>

TEST(Signature, Generate01)
{
    ::xrn::ecs::Registry<int> r;
    r.add<int>(r.createEntity());
    constexpr auto s1{ ::xrn::ecs::Signature<int, float>::generate<int, float>() };
    auto s2{ ::xrn::ecs::Signature<int, float>::generate<int>() };
}

TEST(Signature, Generate02)
{
    constexpr auto s1{ ::xrn::ecs::Signature<::std::string, int, float>::generate<>() };
    auto s2{ ::xrn::ecs::Signature<int, float, ::std::string>::generate<int>() };
}

TEST(Signature, Generate03)
{
    constexpr auto s1{ ::xrn::ecs::Signature<>::generate<>() };
    auto s2{ ::xrn::ecs::Signature<>::generate<>() };
}

TEST(Signature, Comparison01)
{
    constexpr auto constexprSignature{ ::xrn::ecs::Signature<int, float>::generate<int, float>() };
    auto runtimeSignature{ ::xrn::ecs::Signature<int, float>::generate<int>() };

    EXPECT_TRUE(constexprSignature != runtimeSignature);
}

TEST(Signature, Comparison02)
{
    constexpr auto constexprSignature{ ::xrn::ecs::Signature<int, float>::generate<int, float>() };
    auto runtimeSignature{ ::xrn::ecs::Signature<int, float>::generate<int>() };

    EXPECT_TRUE(!(constexprSignature == runtimeSignature));
}

TEST(Signature, Comparison03)
{
    constexpr auto constexprSignature{ ::xrn::ecs::Signature<int, float>::generate<int, float>() };
    auto runtimeSignature{ ::xrn::ecs::Signature<int, float>::generate<int>() };

    EXPECT_TRUE(!constexprSignature.containsNone(runtimeSignature));
}

TEST(Signature, Comparison04)
{
    constexpr auto constexprSignature{ ::xrn::ecs::Signature<int, float>::generate<int, float>() };
    auto runtimeSignature{ ::xrn::ecs::Signature<int, float>::generate<int>() };

    EXPECT_TRUE(constexprSignature.containsAll(runtimeSignature));
}

TEST(Signature, Comparison05)
{
    constexpr auto constexprSignature{ ::xrn::ecs::Signature<int, float>::generate<int, float>() };
    auto runtimeSignature{ ::xrn::ecs::Signature<int, float>::generate<int>() };

    EXPECT_TRUE(!runtimeSignature.containsAll(constexprSignature));
}
