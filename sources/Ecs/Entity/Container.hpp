#pragma once

#include <Ecs/Entity.hpp>
#include <Ecs/Component/Container.hpp>



namespace xrn::ecs::entity {



class Container {

public:

    using Type = ::std::vector<::xrn::ecs::Entity>;




public:

    // ------------------------------------------------------------------ *structors

    explicit Container(
        ::xrn::ecs::component::Container& componentContainer
    );

    ~Container();



    // ------------------------------------------------------------------ Emplace

    template <
        ::xrn::ecs::component::ConceptType... ComponentTypes
    > auto emplace()
        -> ::xrn::ecs::Entity::Reference;

    template <
        ::xrn::ecs::component::ConceptType... ComponentTypes
    > auto emplace(
        ComponentTypes&&... componentsArgs
    )
        -> ::xrn::ecs::Entity::Reference;



    // ------------------------------------------------------------------ Remove

    void remove(
        ::xrn::ecs::Id entityId
    );

    void remove(
        ::xrn::ecs::Entity::Reference&& reference
    );



    // ------------------------------------------------------------------ Get

    [[ nodiscard ]] auto operator[](
        ::xrn::ecs::Id entityId
    ) const
        -> ::xrn::ecs::Entity::ConstReference;

    [[ nodiscard ]] auto operator[](
        ::xrn::ecs::Id entityId
    )
        -> ::xrn::ecs::Entity::Reference;

    [[ nodiscard ]] auto get(
        ::xrn::ecs::Id entityId
    ) const
        -> ::xrn::ecs::Entity::ConstReference;

    [[ nodiscard ]] auto unsafeGet(
        ::xrn::ecs::Id entityId
    )
        -> ::xrn::ecs::Entity::Reference;

    [[ nodiscard ]] auto unsafeGet(
        ::xrn::ecs::Id entityId
    ) const
        -> ::xrn::ecs::Entity::ConstReference;



    // ------------------------------------------------------------------ Contains

    [[ nodiscard ]] auto contains(
        ::xrn::ecs::Id entityId
    ) const
        -> bool;



    // ------------------------------------------------------------------ Iterator

    [[ nodiscard ]] auto begin()
        -> Container::Type::iterator;

    [[ nodiscard ]] auto begin() const
        -> Container::Type::const_iterator;

    [[ nodiscard ]] auto cbegin() const
        -> Container::Type::const_iterator;

    [[ nodiscard ]] auto end()
        -> Container::Type::iterator;

    [[ nodiscard ]] auto end() const
        -> Container::Type::const_iterator;

    [[ nodiscard ]] auto cend() const
        -> Container::Type::const_iterator;




private:

    Container::Type m_entities{};

    ::xrn::ecs::component::Container& m_components;

};



} // namespace xrn::ecs::entity

#include <Ecs/Entity/Container.impl.hpp>
