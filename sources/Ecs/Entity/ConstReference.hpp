#pragma once

#include <Ecs/Entity.hpp>



namespace xrn::ecs::component { class Container; }



class xrn::ecs::Entity::ConstReference {

public:

    // ------------------------------------------------------------------ *structors

    explicit ConstReference(
        const ::xrn::ecs::Entity& entity
    );

    ~ConstReference();



    // ------------------------------------------------------------------ HasComponent

    template <
        ::xrn::ecs::component::ConceptType ComponentType
    > [[ nodiscard ]] auto hasComponent() const
        -> bool;

    template <
        ::xrn::ecs::component::ConceptType... ComponentTypes
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
