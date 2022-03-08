#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Ecs/Signature.hpp>
#include <Ecs/Component.hpp>
#include <Ecs/Entity.hpp>
#include <Ecs/System/Detail/Meta/Function.hpp>
#include <Ecs/System/ASystem.hpp>
#include <Ecs/System/Detail/System.hpp>



namespace xrn::ecs::system {

///////////////////////////////////////////////////////////////////////////
/// \brief Simplifies time measures
/// \ingroup ecs-system
///
/// \include System.hpp <Ecs/System/System.hpp>
///
/// Represents the system of the xrn's ECS. This class allows actions
/// (represented by callable - functions or classes with operator())
/// on components.
///
/// Usage example:
/// \code
/// \endcode
///
/// \see ::xrn::ecs::component::AComponent
///
///////////////////////////////////////////////////////////////////////////
template <
    auto function,
    typename... BanishedComponentTypes
> class System;



///////////////////////////////////////////////////////////////////////////
/// \brief System containing no banished components
///
///////////////////////////////////////////////////////////////////////////
template <
    auto function
> class System<function>
    : public ::xrn::ecs::system::ASystem
{

public:

    // ------------------------------------------------------------------ Constructors

    System();



    // ------------------------------------------------------------------ Run

    void operator()(
        ::xrn::Time t,
        ::xrn::ecs::entity::Container& entities,
        ::xrn::ecs::component::Container& components
    ) override;

    void operator()(
        ::xrn::Time t,
        ::xrn::ecs::component::Container& components,
        ::xrn::ecs::entity::Container& entities
    );

    void operator()(
        ::xrn::Time t,
        const ::xrn::ecs::entity::Container& entities,
        const ::xrn::ecs::component::Container& components
    ) const override;

    void operator()(
        ::xrn::Time t,
        const ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::entity::Container& entities
    ) const;



    // ------------------------------------------------------------------ Signature

    [[ nodiscard ]] static constexpr auto getSignature()
        -> const ::xrn::ecs::Signature&;

};



///////////////////////////////////////////////////////////////////////////
/// \brief System containing banished components
///
///////////////////////////////////////////////////////////////////////////
template <
    auto function,
    ::xrn::ecs::detail::constraint::isComponent... BanishedComponentTypes
> class System<function, BanishedComponentTypes...>
    : public ::xrn::ecs::system::ASystem
{

public:

    // ------------------------------------------------------------------ Constructors

    System();



    // ------------------------------------------------------------------ Run

    void operator()(
        ::xrn::Time t,
        ::xrn::ecs::entity::Container& entities,
        ::xrn::ecs::component::Container& components
    ) override;

    void operator()(
        ::xrn::Time t,
        ::xrn::ecs::component::Container& components,
        ::xrn::ecs::entity::Container& entities
    );

    void operator()(
        ::xrn::Time t,
        const ::xrn::ecs::entity::Container& entities,
        const ::xrn::ecs::component::Container& components
    ) const override;

    void operator()(
        ::xrn::Time t,
        const ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::entity::Container& entities
    ) const;



    // ------------------------------------------------------------------ Signature

    [[ nodiscard ]] static constexpr auto getSignature()
        -> const ::xrn::ecs::Signature&;

    [[ nodiscard ]] static constexpr auto getBanishedSignature()
        -> const ::xrn::ecs::Signature&;



private:

    static constexpr auto m_banishedSignature{
        ::xrn::ecs::Signature::generate<BanishedComponentTypes...>()
    };

};

} // namespace xrn::ecs::system



///////////////////////////////////////////////////////////////////////////
// Alias name
///////////////////////////////////////////////////////////////////////////
namespace xrn::ecs {
    template <
        auto function,
        ::xrn::ecs::detail::constraint::isComponent... BanishedComponentTypes
    > using System = ::xrn::ecs::system::System<function, BanishedComponentTypes...>;
}



///////////////////////////////////////////////////////////////////////////
// Header-implimentation
///////////////////////////////////////////////////////////////////////////
#include <Ecs/System/System.impl.hpp>
