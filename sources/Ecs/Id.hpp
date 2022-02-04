#pragma once

namespace xrn::ecs {



class Id {

public:

    using Type = ::std::size_t;

    struct Hasher;

public:

    // ------------------------------------------------------------------ *structors

    explicit constexpr Id() noexcept;

    constexpr Id(
        ::std::integral auto baseValue
    ) noexcept;

    constexpr ~Id() noexcept;



    // ------------------------------------------------------------------ copy idiom

    constexpr Id(
        const ::xrn::ecs::Id& other
    ) noexcept;

    constexpr auto operator=(
        const ::xrn::ecs::Id& other
    ) noexcept
        -> ::xrn::ecs::Id&;



    // ------------------------------------------------------------------ copy idiom

    constexpr Id(
        ::xrn::ecs::Id&& other
    ) noexcept;

    constexpr auto operator=(
        ::xrn::ecs::Id&& other
    ) noexcept
        -> ::xrn::ecs::Id&;



    // ------------------------------------------------------------------ Get

    [[ nodiscard ]] constexpr auto get() const
        -> Id::Type;

    [[ nodiscard ]] constexpr operator Id::Type() const;

    [[ nodiscard ]] operator ::std::string() const;



    // ------------------------------------------------------------------ Set

    auto operator=(
        Id::Type value
    ) -> ::xrn::ecs::Id&;



    // ------------------------------------------------------------------ Incrementation

    auto operator++()
        -> xrn::ecs::Id&;

    [[ nodiscard ]] auto operator++(
        int
    ) -> xrn::ecs::Id;

    void increment();



    // ------------------------------------------------------------------ Others

    [[ nodiscard ]] auto operator<=>(
        const ::xrn::ecs::Id& other
    ) -> ::std::weak_ordering;



private:

    Id::Type m_value{ 0 };

};



} // namespace xrn::ecs

#include <Ecs/Id.impl.hpp>
