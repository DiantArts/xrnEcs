#include <pch.hpp>
#include <catch2/catch.hpp>
#include <xrn/Meta/ForEach.hpp>

TEST_CASE("ForEach.Basic01", "ForEach")
{
    REQUIRE((::xrn::meta::ForEach<int, float>::getPosition<int>() == 0));
}

TEST_CASE("ForEach.Basic02", "ForEach")
{
    REQUIRE((::xrn::meta::ForEach<int, float>::getPosition<float>() == 1));
}

TEST_CASE("ForEach.Basic03", "ForEach")
{
    REQUIRE((::xrn::meta::ForEach<int, float, ::std::string>::getPosition<int>() == 0));
}

TEST_CASE("ForEach.Basic04", "ForEach")
{
    REQUIRE((::xrn::meta::ForEach<int, float, ::std::string>::getPosition<float>() == 1));
}

TEST_CASE("ForEach.Basic05", "ForEach")
{
    REQUIRE((::xrn::meta::ForEach<int, float, ::std::string>::getPosition<::std::string>() == 2));
}
