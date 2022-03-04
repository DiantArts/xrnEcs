#pragma once

#include <Ecs/Entity.hpp>



namespace xrn::ecs::component { class Container; }



class xrn::ecs::Entity::Reference {

public:

    // ------------------------------------------------------------------ Constructors

    explicit Reference(
        ::xrn::ecs::component::Container& components,
        ::xrn::ecs::Entity& entity
    );

    explicit Reference(
        ::xrn::ecs::Entity& entity,
        ::xrn::ecs::component::Container& components
    );

    ~Reference();



    // ------------------------------------------------------------------ AddComponent

    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > void addComponent(
        auto&&... args
    ) const;

    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void addComponents();




    // ------------------------------------------------------------------ HasComponent

    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto hasComponent() const
        -> bool;

    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > [[ nodiscard ]] auto hasComponents() const
        -> bool;



    // ------------------------------------------------------------------ RemoveComponent

    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > void removeComponent();

    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void removeComponents();



    // ------------------------------------------------------------------ Signature

    [[ nodiscard ]] auto getSignature() const
        -> const ::xrn::ecs::Signature&;



    // ------------------------------------------------------------------ Id

    [[ nodiscard ]] auto getId() const
        -> ::xrn::Id;



    // ------------------------------------------------------------------ Conversion

    [[ nodiscard ]] auto get() const
        -> const ::xrn::ecs::Entity&;

    [[ nodiscard ]] operator ::xrn::ecs::Entity&();

    [[ nodiscard ]] operator const ::xrn::ecs::Entity&() const;




private:

    ::xrn::ecs::component::Container& m_components;
    ::xrn::ecs::Entity& m_entity;

};

#include <Ecs/Entity/Reference.impl.hpp>
