#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Ecs/Entity.hpp>
#include <Ecs/Component/Container.hpp>
#include <Ecs/Entity/Reference.hpp>



///////////////////////////////////////////////////////////////////////////
/// \brief Representation of an entity in the xrn ecs Project
/// \ingroup ecs
///
/// \include Entity.hpp <Ecs/Entity/Entity.hpp>
///
/// ::xrn::ecs::Entity represents a general-purpose object. It allows to add
/// and remove ::xrn::ecs::Component (as well as check if it possesses one).
/// It possesses an Id and a Signature that the user can get.
/// This class is aliased with ::xrn::Entity.
///
/// Usage example:
/// \code
/// ::xrn::ecs::component::Container components;
/// ::xrn::ecs::Entity entity1;
/// entity1.addComponent<::xrn::ecs::component::test::Movable>(components);
/// auto entity2{ ::xrn::ecs::Entity::generate<::xrn::ecs::component::test::Transformable>(components) };
/// entity1.hasComponent<::xrn::ecs::component::test::Movable>(); // true
/// entity1.hasComponent<::xrn::ecs::component::test::Transformable>(); // false
/// \endcode
///
/// \see ::xrn::ecs::component::Container, ::xrn::ecs::Component,
///      ::xrn::ecs::Signature, ::xrn::util::Id
///
///////////////////////////////////////////////////////////////////////////
class xrn::ecs::Entity::Container {

public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // static elements
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Type internally contained by the class
    ///
    ///////////////////////////////////////////////////////////////////////////
    using Type = ::std::vector<::xrn::ecs::Entity>;




public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    /// Constructs an ::xrn::ecs::Entity::Container.
    ///
    /// \param amount Time in milliseconds
    ///
    ///////////////////////////////////////////////////////////////////////////
    explicit Container(
        ::xrn::ecs::component::Container& componentContainer
    );



    // ------------------------------------------------------------------ Emplace

    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > auto emplace()
        -> ::xrn::ecs::Entity::Reference;

    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > auto emplace(
        ComponentTypes&&... componentsArgs
    )
        -> ::xrn::ecs::Entity::Reference;



    // ------------------------------------------------------------------ Remove

    void remove(
        ::xrn::Id entityId
    );

    void remove(
        ::xrn::ecs::Entity::Reference&& reference
    );



    // ------------------------------------------------------------------ Get

    [[ nodiscard ]] auto operator[](
        ::xrn::Id entityId
    ) const
        -> ::xrn::ecs::Entity::ConstReference;

    [[ nodiscard ]] auto operator[](
        ::xrn::Id entityId
    )
        -> ::xrn::ecs::Entity::Reference;

    [[ nodiscard ]] auto get(
        ::xrn::Id entityId
    ) const
        -> ::xrn::ecs::Entity::ConstReference;

    [[ nodiscard ]] auto unsafeGet(
        ::xrn::Id entityId
    )
        -> ::xrn::ecs::Entity::Reference;

    [[ nodiscard ]] auto unsafeGet(
        ::xrn::Id entityId
    ) const
        -> ::xrn::ecs::Entity::ConstReference;



    // ------------------------------------------------------------------ Contains

    [[ nodiscard ]] auto contains(
        ::xrn::Id entityId
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

#include <Ecs/Entity/Container.impl.hpp>
