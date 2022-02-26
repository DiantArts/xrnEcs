#pragma once

namespace xrn::util {



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
        const ::xrn::util::Id& other
    ) noexcept;

    constexpr auto operator=(
        const ::xrn::util::Id& other
    ) noexcept
        -> ::xrn::util::Id&;



    // ------------------------------------------------------------------ copy idiom

    constexpr Id(
        ::xrn::util::Id&& other
    ) noexcept;

    constexpr auto operator=(
        ::xrn::util::Id&& other
    ) noexcept
        -> ::xrn::util::Id&;



    // ------------------------------------------------------------------ Get

    [[ nodiscard ]] constexpr auto get() const
        -> Id::Type;

    [[ nodiscard ]] constexpr operator Id::Type() const;

    [[ nodiscard ]] operator ::std::string() const;



    // ------------------------------------------------------------------ Set

    auto operator=(
        Id::Type value
    ) -> ::xrn::util::Id&;



    // ------------------------------------------------------------------ Incrementation

    auto operator++()
        -> ::xrn::util::Id&;

    [[ nodiscard ]] auto operator++(
        int
    ) -> ::xrn::util::Id;

    void increment();



    // ------------------------------------------------------------------ Others

    [[ nodiscard ]] auto operator<=>(
        const ::xrn::util::Id& other
    ) -> ::std::weak_ordering;



private:

    Id::Type m_value{ 0 };

};



} // namespace xrn::util

#include <Util/Id.impl.hpp>



///////////////////////////////////////////////////////////////////////////
// Template specialization
///////////////////////////////////////////////////////////////////////////
// namespace xrn::util { using Id = ::xrn::util::Id<::std::size_t>; }
namespace xrn { using Id = ::xrn::util::Id; }
