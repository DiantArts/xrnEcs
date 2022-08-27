#include <pch.hpp>
#include <catch2/catch.hpp>
#include <xrn/Util/OptionalReference.hpp>

TEST_CASE("OptionalReference.Aliases", "OptionalReference")
{
    ::xrn::util::OptionalReference<int> r1;
    int i{ 2 };
    ::xrn::util::OptRef<int> r2{ i };
    ::xrn::OptionalReference<int> r3{ &i };
    ::xrn::OptRef<int> r4{ &i };
}

TEST_CASE("OptionalReference.access", "OptionalReference")
{
    int i{ 2 };
    ::xrn::util::OptionalReference<int> r1{ i };
    const ::xrn::util::OptionalReference<int> r2{ i };

    i = 3;
    REQUIRE(r1.get() == 3);
    REQUIRE(r1.unsafeGet() == 3);
    REQUIRE(*r1 == 3);

    i = 4;
    REQUIRE(r2.get() == 4);
    REQUIRE(r2.unsafeGet() == 4);
    REQUIRE(*r2 == 4);
}

TEST_CASE("OptionalReference.empty", "OptionalReference")
{
    ::xrn::util::OptionalReference<int> r1;
    int i{ 2 };
    const ::xrn::util::OptionalReference<int> r2{ i };

    REQUIRE(r1.isEmpty());
    REQUIRE(!r2.isEmpty());
    REQUIRE_THROWS_AS(r1.get(), ::std::runtime_error);

    r1 = i;
    REQUIRE(!r1.isEmpty());
    REQUIRE(r2.get() == 2);

    r1.clear();
    REQUIRE(r1.isEmpty());
    REQUIRE_THROWS_AS(r1.get(), ::std::runtime_error);
}
