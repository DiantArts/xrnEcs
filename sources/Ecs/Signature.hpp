#pragma once

#include <Ecs/AComponent.hpp>
#include <Util/Time.hpp>

namespace xrn::ecs {



class Signature {

public:

    template <
        typename... Types
    > [[ nodiscard ]] static constexpr auto generate() noexcept
        -> ::xrn::ecs::Signature;

public:

    // ------------------------------------------------------------------ Constructors

    explicit Signature() noexcept;

    explicit constexpr Signature(
        const ::cbitset::Cbitset<::xrn::ecs::component::maxId>& bitset
    ) noexcept;

    constexpr ~Signature() noexcept;



    // ------------------------------------------------------------------ copy idiom

    constexpr Signature(
        const ::xrn::ecs::Signature& other
    ) noexcept;

    constexpr auto operator=(
        const ::xrn::ecs::Signature& other
    ) noexcept
        -> ::xrn::ecs::Signature&;



    // ------------------------------------------------------------------ copy idiom

    constexpr Signature(
        ::xrn::ecs::Signature&& other
    ) noexcept;

    constexpr auto operator=(
        ::xrn::ecs::Signature&& other
    ) noexcept
        -> ::xrn::ecs::Signature&;



    // ------------------------------------------------------------------ Comparisons

    [[ nodiscard ]] constexpr auto operator==(
        const ::xrn::ecs::Signature& that
    ) const
        -> bool;

    [[ nodiscard ]] constexpr auto operator!=(
        const ::xrn::ecs::Signature& that
    ) const
        -> bool;



    // ------------------------------------------------------------------ BitManipulation

    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void set();

    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void reset();



    // ------------------------------------------------------------------ Get

    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > auto get()
        -> bool;

    auto get(::xrn::ecs::detail::constraint::isComponent auto& component)
        -> bool;

    auto get(::xrn::Id id)
        -> bool;


    auto operator[](::xrn::ecs::detail::constraint::isComponent auto& component)
        -> bool;

    auto operator[](::xrn::Id id)
        -> bool;



    // ------------------------------------------------------------------ Contains

    [[ nodiscard ]] constexpr auto contains(
        const ::xrn::ecs::Signature& that
    ) const
        -> bool;

    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > [[ nodiscard ]] constexpr auto contains() const
        -> bool;

    [[ nodiscard ]] constexpr auto contains(
        const ::xrn::ecs::detail::constraint::isComponent auto&... component
    ) const
        -> bool;



    // ------------------------------------------------------------------ ContainsOne

    [[ nodiscard ]] constexpr auto containsAtLeastOne(
        const ::xrn::ecs::Signature& that
    ) const
        -> bool;

    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > [[ nodiscard ]] constexpr auto containsAtLeastOne() const
        -> bool;

    [[ nodiscard ]] constexpr auto containsAtLeastOne(
        const ::xrn::ecs::detail::constraint::isComponent auto&... component
    ) const
        -> bool;



    // ------------------------------------------------------------------ Others

    friend auto operator<<(
        ::std::ostream& os,
        const ::xrn::ecs::Signature& signature
    )
        -> ::std::ostream&
    {
        for (::std::size_t i{ 0 }; i < ::xrn::ecs::component::maxId; i++) {
            os << signature.m_bitset[i];
        }
        return os;
    }



private:

    ::cbitset::Cbitset<::xrn::ecs::component::maxId> m_bitset{};

};



} // namespace xrn::ecs

#include <Ecs/Signature.impl.hpp>
