#pragma once

#include <Ecs/Signature.hpp>
#include <Ecs/AComponent.hpp>
#include <Ecs/System/Detail/Meta/Function.hpp>
#include <Ecs/System/ASystem.hpp>



namespace xrn::ecs::system {



template <
    auto function,
    typename... BanishedComponentTypes
> class System;



template <
    auto function
> class System<function>
    : public ::xrn::ecs::system::ASystem
{

public:

    // ------------------------------------------------------------------ *structors

    System();

    ~System();



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



template <
    auto function,
    ::xrn::ecs::component::ConceptType... BanishedComponentTypes
> class System<function, BanishedComponentTypes...>
    : public ::xrn::ecs::system::ASystem
{

public:

    // ------------------------------------------------------------------ *structors

    System();

    ~System();



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

#include <Ecs/System/System.impl.hpp>
