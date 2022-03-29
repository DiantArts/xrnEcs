#include <pch.hpp>
#include <xrn/Ecs/Signature.hpp>
#include <xrn/Ecs/Component.hpp>



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/test/unit_test.hpp>
#pragma GCC diagnostic pop
BOOST_AUTO_TEST_SUITE(Engine)
BOOST_AUTO_TEST_SUITE(Core)
BOOST_AUTO_TEST_SUITE(Ecs)
BOOST_AUTO_TEST_SUITE(Signature)



BOOST_AUTO_TEST_CASE(constexprness)
{
    auto signature1{ ::xrn::ecs::Signature::generate<::xrn::ecs::component::test::ComponentA>() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<::xrn::ecs::component::test::ComponentA>() };
    constexpr auto signature3{ ::xrn::ecs::Signature::generate<::xrn::ecs::component::test::ComponentA>() };
    constexpr auto signature4{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::AbilityA
    >() };
    if constexpr (signature2 == signature3) {}
}



// ------------------------------------------------------------------ ContainsSignature
BOOST_AUTO_TEST_SUITE(ContainsSignature)



BOOST_AUTO_TEST_CASE(true1)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    constexpr auto signature2{
        ::xrn::ecs::Signature::generate<::xrn::ecs::component::test::ComponentA>()
    };
    BOOST_TEST(signature1.contains(signature2));
}

BOOST_AUTO_TEST_CASE(true2)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentB
    >() };
    BOOST_TEST(signature1.contains(signature2));
}

BOOST_AUTO_TEST_CASE(true3)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    BOOST_TEST(signature1.contains(signature2));
    BOOST_TEST(signature2.contains(signature1));
}

BOOST_AUTO_TEST_CASE(true4)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA
    >() };
    BOOST_TEST(signature1.contains(signature2));
    BOOST_TEST(signature2.contains(signature1));
}

BOOST_AUTO_TEST_CASE(true5)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::AbilityA
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::AbilityA
    >() };
    BOOST_TEST(signature1.contains(signature2));
    BOOST_TEST(signature2.contains(signature1));
}

BOOST_AUTO_TEST_CASE(false1)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentB
    >() };
    BOOST_TEST(!signature1.contains(signature2));
    BOOST_TEST(!signature2.contains(signature1));
}

BOOST_AUTO_TEST_CASE(false2)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    BOOST_TEST(!signature1.contains(signature2));
}

BOOST_AUTO_TEST_CASE(false3)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::AbilityA
    >() };
    BOOST_TEST(!signature1.contains(signature2));
    BOOST_TEST(signature2.contains(signature1));
}

BOOST_AUTO_TEST_CASE(false4)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::AbilityA
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::AbilityB
    >() };
    BOOST_TEST(!signature1.contains(signature2));
    BOOST_TEST(!signature2.contains(signature1));
}



BOOST_AUTO_TEST_SUITE_END()
// ------------------------------------------------------------------ ContainsComponent
BOOST_AUTO_TEST_SUITE(ContainsComponent)



BOOST_AUTO_TEST_CASE(true1)
{
    constexpr auto signature{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    BOOST_TEST(signature.contains<::xrn::ecs::component::test::ComponentA>());
    ::xrn::ecs::component::test::ComponentA movable;
    BOOST_TEST(signature.contains(movable));
    BOOST_TEST(signature[movable.getId()]);
}

BOOST_AUTO_TEST_CASE(true2)
{
    constexpr auto signature{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    BOOST_TEST(signature.contains<::xrn::ecs::component::test::ComponentB>());
    ::xrn::ecs::component::test::ComponentB transformable;
    BOOST_TEST(signature.contains(transformable));
    BOOST_TEST(signature[transformable.getId()]);
}

BOOST_AUTO_TEST_CASE(true3)
{
    constexpr auto signature{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    BOOST_TEST((signature.contains<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >()));
    ::xrn::ecs::component::test::ComponentA movable;
    ::xrn::ecs::component::test::ComponentB transformable;
    BOOST_TEST(signature.contains(movable, transformable));
    BOOST_TEST(signature.contains(transformable, movable));
}

BOOST_AUTO_TEST_CASE(true4)
{
    constexpr auto signature{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA
    >() };
    BOOST_TEST(signature.contains<::xrn::ecs::component::test::ComponentA>());
    ::xrn::ecs::component::test::ComponentA movable;
    BOOST_TEST(signature.contains(movable));
    BOOST_TEST(signature.contains(movable.getId()));
    BOOST_TEST(signature[movable.getId()]);
}

BOOST_AUTO_TEST_CASE(false1)
{
    constexpr auto signature{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA
    >() };
    BOOST_TEST(!signature.contains<::xrn::ecs::component::test::ComponentB>());
    ::xrn::ecs::component::test::ComponentB transformable;
    BOOST_TEST(!signature.contains(transformable));
    BOOST_TEST(!signature.contains(transformable.getId()));
    BOOST_TEST(!signature[transformable.getId()]);
}

BOOST_AUTO_TEST_CASE(CmpRamComponents)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    ::xrn::ecs::component::test::ComponentA m{};
    ::xrn::ecs::component::test::ComponentB t{};
    BOOST_TEST(!signature1.contains(m, t));
    BOOST_TEST(signature2.contains(m, t));
    BOOST_TEST(!signature1.contains(t, m));
    BOOST_TEST(signature2.contains(t, m));
    BOOST_TEST(!signature1.contains(m.getId(), t.getId()));
    BOOST_TEST(signature2.contains(m.getId(), t.getId()));
    BOOST_TEST(!signature1.contains(t.getId(), m.getId()));
    BOOST_TEST(signature2.contains(t.getId(), m.getId()));
}

BOOST_AUTO_TEST_CASE(ContainsAny)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    constexpr auto signature3{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentB
    >() };
    ::xrn::ecs::component::test::ComponentA m{};
    ::xrn::ecs::component::test::ComponentB t{};
    BOOST_TEST(signature1.containsAny(m, t));
    BOOST_TEST(signature2.containsAny(m, t));
    BOOST_TEST(signature1.containsAny(m.getId(), t.getId()));
    BOOST_TEST(signature2.containsAny(m.getId(), t.getId()));
    BOOST_TEST((signature1.containsAny<
        ::xrn::ecs::component::test::ComponentA, ::xrn::ecs::component::test::ComponentB
    >()));
    BOOST_TEST((signature2.containsAny<
        ::xrn::ecs::component::test::ComponentA, ::xrn::ecs::component::test::ComponentB
    >()));
    BOOST_TEST(signature1.containsAny(signature2));
    BOOST_TEST(signature2.containsAny(signature1));

    BOOST_TEST(!signature1.containsAny(t));
    BOOST_TEST(!signature1.containsAny(t.getId()));
    BOOST_TEST(!signature1[t.getId()]);
    BOOST_TEST((!signature1.containsAny<::xrn::ecs::component::test::ComponentB>()));
    BOOST_TEST(!signature1.containsAny(signature3));
}

BOOST_AUTO_TEST_CASE(ContainsNone)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    constexpr auto signature3{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentB
    >() };
    ::xrn::ecs::component::test::ComponentA m{};
    ::xrn::ecs::component::test::ComponentB t{};

    BOOST_TEST(signature1.containsNone(t));
    BOOST_TEST(signature3.containsNone(m));
    BOOST_TEST(signature1.containsNone(t.getId()));
    BOOST_TEST(signature3.containsNone(m.getId()));
    BOOST_TEST((signature1.containsNone<::xrn::ecs::component::test::ComponentB>()));
    BOOST_TEST((signature3.containsNone<::xrn::ecs::component::test::ComponentA>()));
    BOOST_TEST(signature1.containsNone(signature3));
    BOOST_TEST(signature3.containsNone(signature1));

    BOOST_TEST(!signature1.containsNone(m, t));
    BOOST_TEST(!signature2.containsNone(m, t));
    BOOST_TEST(!signature1.containsNone(m.getId(), t.getId()));
    BOOST_TEST(!signature2.containsNone(m.getId(), t.getId()));
    BOOST_TEST(!(signature1.containsNone<
        ::xrn::ecs::component::test::ComponentA, ::xrn::ecs::component::test::ComponentB
    >()));
    BOOST_TEST((!signature2.containsNone<
        ::xrn::ecs::component::test::ComponentA, ::xrn::ecs::component::test::ComponentB
    >()));
    BOOST_TEST(!signature1.containsNone(signature2));
    BOOST_TEST(!signature2.containsNone(signature1));
    BOOST_TEST(signature1.containsNone(t));
    BOOST_TEST(signature1.containsNone(t.getId()));
    BOOST_TEST((signature1.containsNone<::xrn::ecs::component::test::ComponentB>()));
    BOOST_TEST(signature1.containsNone(signature3));
}



BOOST_AUTO_TEST_SUITE_END()
// ------------------------------------------------------------------ Comparison
BOOST_AUTO_TEST_SUITE(Comparison)



BOOST_AUTO_TEST_CASE(true1Arg)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA
    >() };
    BOOST_TEST((signature1 == signature2));
    BOOST_TEST((signature2 == signature1));
}

BOOST_AUTO_TEST_CASE(true2Arg)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    BOOST_TEST((signature1 == signature2));
    BOOST_TEST((signature2 == signature1));
}

BOOST_AUTO_TEST_CASE(false1Arg)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentB
    >() };
    BOOST_TEST((signature1 != signature2));
    BOOST_TEST((signature2 != signature1));
}

BOOST_AUTO_TEST_CASE(false2Arg1)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    BOOST_TEST((signature1 != signature2));
    BOOST_TEST((signature2 != signature1));
}

BOOST_AUTO_TEST_CASE(false2Arg2)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA
    >() };
    BOOST_TEST((signature1 != signature2));
    BOOST_TEST((signature2 != signature1));
}

BOOST_AUTO_TEST_CASE(false2Arg3)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentB
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    BOOST_TEST((signature1 != signature2));
    BOOST_TEST((signature2 != signature1));
}

BOOST_AUTO_TEST_CASE(false2Arg4)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentB
    >() };
    BOOST_TEST((signature1 != signature2));
    BOOST_TEST((signature2 != signature1));
}

BOOST_AUTO_TEST_CASE(trueConstexprNonConstexpr)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA
    >() };
    auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA
    >() };
    BOOST_TEST((signature1 == signature2));
    BOOST_TEST((signature2 == signature1));
}

BOOST_AUTO_TEST_CASE(falseConstexprNonConstexpr)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentB
    >() };
    BOOST_TEST((signature1 != signature2));
    BOOST_TEST((signature2 != signature1));
}



BOOST_AUTO_TEST_SUITE_END()
// ------------------------------------------------------------------ BitManipulation
BOOST_AUTO_TEST_SUITE(BitManipulation)



BOOST_AUTO_TEST_CASE(set1Arg)
{
    auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA
    >() };
    auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    signature1.set<::xrn::ecs::component::test::ComponentB>();
    BOOST_TEST((signature1 == signature2));
    BOOST_TEST((signature2 == signature1));
}

BOOST_AUTO_TEST_CASE(set2Arg)
{
    auto signature1{ ::xrn::ecs::Signature::generate() };
    auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    signature1.set<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >();
    BOOST_TEST((signature1 == signature2));
    BOOST_TEST((signature2 == signature1));
}

BOOST_AUTO_TEST_CASE(reset1Arg)
{
    auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA
    >() };
    auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    signature2.reset<::xrn::ecs::component::test::ComponentB>();
    BOOST_TEST((signature1 == signature2));
    BOOST_TEST((signature2 == signature1));
}

BOOST_AUTO_TEST_CASE(reset2Arg)
{
    auto signature1{ ::xrn::ecs::Signature::generate() };
    auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    signature2.reset<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >();
    BOOST_TEST((signature1 == signature2));
    BOOST_TEST((signature2 == signature1));
}

BOOST_AUTO_TEST_CASE(resetAll)
{
    auto signature{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB,
        ::xrn::ecs::component::test::AbilityA
    >() };
    BOOST_TEST(signature.contains<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(signature.contains<::xrn::ecs::component::test::ComponentB>());
    BOOST_TEST(signature.contains<::xrn::ecs::component::test::AbilityA>());
    signature.reset();
    BOOST_TEST(!signature.contains<::xrn::ecs::component::test::ComponentA>());
    BOOST_TEST(!signature.contains<::xrn::ecs::component::test::ComponentB>());
    BOOST_TEST(!signature.contains<::xrn::ecs::component::test::AbilityA>());
}

BOOST_AUTO_TEST_CASE(ostream)
{
    auto signature1{ ::xrn::ecs::Signature::generate<::xrn::ecs::component::test::ComponentA>() };
    auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::ComponentA,
        ::xrn::ecs::component::test::ComponentB
    >() };
    ::std::ostringstream os;
    os << signature1 << signature2; // assumes the output is correct
}

BOOST_AUTO_TEST_CASE(other)
{
    auto signature1{ ::xrn::ecs::Signature::generate<::xrn::ecs::component::test::ComponentA>() };
    auto signature2{ ::xrn::ecs::Signature::generate<::xrn::ecs::component::test::ComponentA>() };
    auto signature3{ ::xrn::ecs::Signature::generate<::xrn::ecs::component::test::ComponentB>() };
    BOOST_TEST(!signature1.containsNone(signature2));
    BOOST_TEST(signature1.containsNone(signature3));
    BOOST_TEST(!signature2.containsNone(signature1));
    BOOST_TEST(signature3.containsNone(signature1));
}



BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
