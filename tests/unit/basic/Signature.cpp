#include <pch.hpp>
#include <catch2/catch.hpp>
#include <xrn/Ecs/Signature.hpp>
#include <xrn/Ecs/Registry.hpp>

TEST_CASE("Signature.Generate01", "Signature")
{
    ::xrn::ecs::Registry<int> r;
    r.add<int>(r.createEntity());
    constexpr auto s1{ ::xrn::ecs::Signature<int, float>::generate<int, float>() };
    auto s2{ ::xrn::ecs::Signature<int, float>::generate<int>() };
}

TEST_CASE("Signature.Generate02", "Signature")
{
    constexpr auto s1{ ::xrn::ecs::Signature<::std::string, int, float>::generate<>() };
    auto s2{ ::xrn::ecs::Signature<int, float, ::std::string>::generate<int>() };
}

TEST_CASE("Signature.Generate03", "Signature")
{
    constexpr auto s1{ ::xrn::ecs::Signature<>::generate<>() };
    auto s2{ ::xrn::ecs::Signature<>::generate<>() };
}

TEST_CASE("Signature.Comparison01", "Signature")
{
    constexpr auto constexprSignature{ ::xrn::ecs::Signature<int, float>::generate<int, float>() };
    auto runtimeSignature{ ::xrn::ecs::Signature<int, float>::generate<int>() };

    REQUIRE(constexprSignature != runtimeSignature);
}

TEST_CASE("Signature.Comparison02", "Signature")
{
    constexpr auto constexprSignature{ ::xrn::ecs::Signature<int, float>::generate<int, float>() };
    auto runtimeSignature{ ::xrn::ecs::Signature<int, float>::generate<int>() };

    REQUIRE(!(constexprSignature == runtimeSignature));
}

TEST_CASE("Signature.Comparison03", "Signature")
{
    constexpr auto constexprSignature{ ::xrn::ecs::Signature<int, float>::generate<int, float>() };
    auto runtimeSignature{ ::xrn::ecs::Signature<int, float>::generate<int>() };

    REQUIRE(!constexprSignature.containsNone(runtimeSignature));
}

TEST_CASE("Signature.Comparison04", "Signature")
{
    constexpr auto constexprSignature{ ::xrn::ecs::Signature<int, float>::generate<int, float>() };
    auto runtimeSignature{ ::xrn::ecs::Signature<int, float>::generate<int>() };

    REQUIRE(constexprSignature.containsAll(runtimeSignature));
}

TEST_CASE("Signature.Comparison05", "Signature")
{
    constexpr auto constexprSignature{ ::xrn::ecs::Signature<int, float>::generate<int, float>() };
    auto runtimeSignature{ ::xrn::ecs::Signature<int, float>::generate<int>() };

    REQUIRE(!runtimeSignature.containsAll(constexprSignature));
}
