#include <pch.hpp>
#include <Ecs/Signature.hpp>
#include <Ecs/AComponent.hpp>



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
BOOST_AUTO_TEST_SUITE(Signature)



BOOST_AUTO_TEST_CASE(constexprness)
{
    auto signature1{ ::xrn::ecs::Signature::generate<::xrn::ecs::component::test::Movable>() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<::xrn::ecs::component::test::Movable>() };
    constexpr auto signature3{ ::xrn::ecs::Signature::generate<::xrn::ecs::component::test::Movable>() };
    if constexpr (signature2 == signature3) {}
}



// ------------------------------------------------------------------ ContainsSignature
BOOST_AUTO_TEST_SUITE(ContainsSignature)



BOOST_AUTO_TEST_CASE(true1)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >() };
    constexpr auto signature2{
        ::xrn::ecs::Signature::generate<::xrn::ecs::component::test::Movable>()
    };
    BOOST_TEST(signature1.contains(signature2));
}

BOOST_AUTO_TEST_CASE(true2)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Transformable
    >() };
    BOOST_TEST(signature1.contains(signature2));
}

BOOST_AUTO_TEST_CASE(true3)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >() };
    BOOST_TEST(signature1.contains(signature2));
}

BOOST_AUTO_TEST_CASE(true4)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable
    >() };
    BOOST_TEST(signature1.contains(signature2));
}

BOOST_AUTO_TEST_CASE(false1)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Transformable
    >() };
    BOOST_TEST(!signature1.contains(signature2));
}

BOOST_AUTO_TEST_CASE(false2)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >() };
    BOOST_TEST(!signature1.contains(signature2));
}



BOOST_AUTO_TEST_SUITE_END()
// ------------------------------------------------------------------ ContainsComponent
BOOST_AUTO_TEST_SUITE(ContainsComponent)



BOOST_AUTO_TEST_CASE(true1)
{
    constexpr auto signature{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >() };
    BOOST_TEST(signature.contains<::xrn::ecs::component::test::Movable>());
    ::xrn::ecs::component::test::Movable movable;
    BOOST_TEST(signature.contains(movable));
}

BOOST_AUTO_TEST_CASE(true2)
{
    constexpr auto signature{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >() };
    BOOST_TEST(signature.contains<::xrn::ecs::component::test::Transformable>());
    ::xrn::ecs::component::test::Transformable transformable;
    BOOST_TEST(signature.contains(transformable));
}

BOOST_AUTO_TEST_CASE(true3)
{
    constexpr auto signature{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >() };
    BOOST_TEST((signature.contains<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >()));
    ::xrn::ecs::component::test::Movable movable;
    ::xrn::ecs::component::test::Transformable transformable;
    BOOST_TEST(signature.contains(movable, transformable));
}

BOOST_AUTO_TEST_CASE(true4)
{
    constexpr auto signature{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable
    >() };
    BOOST_TEST(signature.contains<::xrn::ecs::component::test::Movable>());
    ::xrn::ecs::component::test::Movable movable;
    BOOST_TEST(signature.contains(movable));
}

BOOST_AUTO_TEST_CASE(false1)
{
    constexpr auto signature{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable
    >() };
    BOOST_TEST(!signature.contains<::xrn::ecs::component::test::Transformable>());
    ::xrn::ecs::component::test::Transformable transformable;
    BOOST_TEST(!signature.contains(transformable));
}

BOOST_AUTO_TEST_CASE(CmpRamComponents)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >() };
    ::xrn::ecs::component::test::Movable m{};
    ::xrn::ecs::component::test::Transformable t{};
    BOOST_TEST(!signature1.contains(m, t));
    BOOST_TEST(signature2.contains(m, t));
}



BOOST_AUTO_TEST_SUITE_END()
// ------------------------------------------------------------------ Comparison
BOOST_AUTO_TEST_SUITE(Comparison)



BOOST_AUTO_TEST_CASE(true1Arg)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable
    >() };
    BOOST_TEST(signature1 == signature2);
}

BOOST_AUTO_TEST_CASE(true2Arg)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >() };
    BOOST_TEST(signature1 == signature2);
}

BOOST_AUTO_TEST_CASE(false1Arg)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Transformable
    >() };
    BOOST_TEST(signature1 != signature2);
}

BOOST_AUTO_TEST_CASE(false2Arg1)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >() };
    BOOST_TEST(signature1 != signature2);
}

BOOST_AUTO_TEST_CASE(false2Arg2)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable
    >() };
    BOOST_TEST(signature1 != signature2);
}

BOOST_AUTO_TEST_CASE(false2Arg3)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Transformable
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >() };
    BOOST_TEST(signature1 != signature2);
}

BOOST_AUTO_TEST_CASE(false2Arg4)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >() };
    constexpr auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Transformable
    >() };
    BOOST_TEST(signature1 != signature2);
}

BOOST_AUTO_TEST_CASE(trueConstexprNonConstexpr)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable
    >() };
    auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable
    >() };
    BOOST_TEST(signature1 == signature2);
}

BOOST_AUTO_TEST_CASE(falseConstexprNonConstexpr)
{
    constexpr auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >() };
    auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Transformable
    >() };
    BOOST_TEST(signature1 != signature2);
}



BOOST_AUTO_TEST_SUITE_END()
// ------------------------------------------------------------------ BitManipulation
BOOST_AUTO_TEST_SUITE(BitManipulation)



BOOST_AUTO_TEST_CASE(set1Arg)
{
    auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable
    >() };
    auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >() };
    signature1.set<::xrn::ecs::component::test::Transformable>();
    BOOST_TEST(signature1 == signature2);
}

BOOST_AUTO_TEST_CASE(set2Arg)
{
    auto signature1{ ::xrn::ecs::Signature::generate() };
    auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >() };
    signature1.set<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >();
    BOOST_TEST(signature1 == signature2);
}

BOOST_AUTO_TEST_CASE(reset1Arg)
{
    auto signature1{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable
    >() };
    auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >() };
    signature2.reset<::xrn::ecs::component::test::Transformable>();
    BOOST_TEST(signature1 == signature2);
}

BOOST_AUTO_TEST_CASE(reset2Arg)
{
    auto signature1{ ::xrn::ecs::Signature::generate() };
    auto signature2{ ::xrn::ecs::Signature::generate<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >() };
    signature2.reset<
        ::xrn::ecs::component::test::Movable,
        ::xrn::ecs::component::test::Transformable
    >();
    BOOST_TEST(signature1 == signature2);
}



BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
