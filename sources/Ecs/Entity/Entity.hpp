// Using an Entity composed with Both a Base and Derived class result in an undefined behavior

#pragma once

#include <Ecs/Id.hpp>
#include <Ecs/AComponent.hpp>
#include <Ecs/Component/Container.hpp>
#include <Ecs/Signature.hpp>



namespace xrn::ecs::entity {



class Entity {

public:

    class ConstReference;
    class Reference;



public:

    // ------------------------------------------------------------------ Genetate

    template <
        ::xrn::ecs::component::ConceptType... ComponentTypes
    > [[ nodiscard ]] static constexpr auto generate(
        ::xrn::ecs::component::Container& components
    )
        -> ::xrn::ecs::entity::Entity;



    // ------------------------------------------------------------------ AddComponent

    template <
        ::xrn::ecs::component::ConceptType ComponentType
    > auto addComponent(
        ::xrn::ecs::component::Container& components
    )
        -> ComponentType&;

    template <
        ::xrn::ecs::component::ConceptType... ComponentTypes
    > void addComponents(
        ::xrn::ecs::component::Container& components
    );

    template <
        ::xrn::ecs::component::ConceptType... ComponentTypes
    > void addComponents(
        ::xrn::ecs::component::Container& componentsContainer,
        ComponentTypes&&... components
    );




    // ------------------------------------------------------------------ HasComponent

    template <
        ::xrn::ecs::component::ConceptType ComponentType
    > [[ nodiscard ]] auto hasComponent() const
        -> bool;

    template <
        ::xrn::ecs::component::ConceptType... ComponentTypes
    > [[ nodiscard ]] auto hasComponents() const
        -> bool;



    // ------------------------------------------------------------------ RemoveComponent

    template <
        ::xrn::ecs::component::ConceptType ComponentType
    > void removeComponent(
        ::xrn::ecs::component::Container& container
    );

    template <
        ::xrn::ecs::component::ConceptType... ComponentTypes
    > void removeComponents(
        ::xrn::ecs::component::Container& container
    );



    // ------------------------------------------------------------------ Signature

    [[ nodiscard ]] auto getSignature() const
        -> const ::xrn::ecs::Signature&;



    // ------------------------------------------------------------------ Id

    [[ nodiscard ]] auto getId() const
        -> ::xrn::ecs::Id;




private:

    static inline ::xrn::ecs::Id m_IdGiver{};
    ::xrn::ecs::Id m_id{ ++m_IdGiver };

    ::xrn::ecs::Signature m_signature{};

};



template <
    typename Type
> concept ConceptType =
    ::std::is_same<
        ::xrn::ecs::entity::Entity,
        ::std::remove_cvref_t<Type>
    >::value;



} // namespace xrn::ecs::Entity

#include <Ecs/Entity/Entity.impl.hpp>
