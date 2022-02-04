#pragma once

#include <boost/functional/hash.hpp>




// ------------------------------------------------------------------ *structors

// default value is 0
constexpr ::xrn::ecs::Id::Id() noexcept = default;

constexpr ::xrn::ecs::Id::Id(
    ::std::integral auto baseValue
) noexcept
    : m_value{ static_cast<Id::Type>(baseValue) }
{}

constexpr ::xrn::ecs::Id::~Id() noexcept = default;



// ------------------------------------------------------------------ copy idiom

constexpr ::xrn::ecs::Id::Id(
    const ::xrn::ecs::Id& other
) noexcept = default;

constexpr auto ::xrn::ecs::Id::operator=(
    const ::xrn::ecs::Id& other
) noexcept
    -> ::xrn::ecs::Id& = default;



// ------------------------------------------------------------------ copy idiom

constexpr ::xrn::ecs::Id::Id(
    ::xrn::ecs::Id&& other
) noexcept = default;

constexpr auto ::xrn::ecs::Id::operator=(
    ::xrn::ecs::Id&& other
) noexcept
    -> ::xrn::ecs::Id& = default;



// ------------------------------------------------------------------ Get

constexpr auto ::xrn::ecs::Id::get() const
    -> ::xrn::ecs::Id::Type
{
    return m_value;
}

constexpr ::xrn::ecs::Id::operator ::xrn::ecs::Id::Type() const
{
    return m_value;
}



// ------------------------------------------------------------------ Hasher

struct xrn::ecs::Id::Hasher {

    auto operator () (
        const ::xrn::ecs::Id& id
    ) const
        -> ::std::size_t
    {
        ::std::size_t seed = 0;
        ::boost::hash_combine(seed, id.get());
        return seed;
    }

};
