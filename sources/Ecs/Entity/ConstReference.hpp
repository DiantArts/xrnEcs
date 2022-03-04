#pragma once

#include <Ecs/Entity/Entity.hpp>


namespace xrn::ecs::component { class Container; }



class xrn::ecs::Entity::ConstReference {

public:

    // ------------------------------------------------------------------ Constructors

    explicit ConstReference(
        const ::xrn::ecs::Entity& entity
    );

    ~ConstReference();



    // ------------------------------------------------------------------ HasComponent

    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto hasComponent() const
        -> bool;

    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > [[ nodiscard ]] auto hasComponents() const
        -> bool;



    // ------------------------------------------------------------------ Signature

    [[ nodiscard ]] auto getSignature() const
        -> const ::xrn::ecs::Signature&;



    // ------------------------------------------------------------------ Id

    [[ nodiscard ]] auto getId() const
        -> ::xrn::Id;



    // ------------------------------------------------------------------ Conversion

    [[ nodiscard ]] auto get() const
        -> const ::xrn::ecs::Entity&;

    [[ nodiscard ]] operator const ::xrn::ecs::Entity&() const;




private:

    const ::xrn::ecs::Entity& m_entity;

};

#include <Ecs/Entity/ConstReference.impl.hpp>
