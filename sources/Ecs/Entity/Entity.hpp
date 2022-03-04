// Using an Entity composed with Both a Base and Derived class result in an undefined behavior

#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Util/Id.hpp>
#include <Ecs/Detail/Constraint.hpp>
#include <Ecs/AComponent.hpp>
#include <Ecs/Component/Container.hpp>
#include <Ecs/Signature.hpp>



namespace xrn::ecs::entity {

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
class Entity {

public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // static elements
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Class in reference to ::xrn::ecs::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    class ConstReference;
    class Reference;
    class Container;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Constructs an ::xrn::ecs::Entity with components
    ///
    /// \tparam ComponentTypes Type of components to emplace inside the
    ///         ::xrn::ecs::Entity when creating it.
    ///
    /// \param components Component container where to emplace the components
    ///        given as template parameter.
    ///
    /// \return New ::xrn::ecs::Entity just created
    ///
    /// \see ::xrn::ecs::component::Container, ::xrn::ecs::Component
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > [[ nodiscard ]] static constexpr auto generate(
        ::xrn::ecs::component::Container& components
    ) -> ::xrn::ecs::entity::Entity;



public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Add components
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Adds a single component
    ///
    /// Creates a component by perfect forwading the arguments to the
    /// constructor of the component.
    ///
    /// \tparam ComponentTypes Type of components to emplace inside the
    /// ::xrn::ecs::Entity when creating it.
    ///
    /// \param components Component container where to emplace the components
    ///        given as template parameter.
    /// \param args Arguments to perfect forward to the constructor of the
    ///        component to create
    ///
    /// \see ::xrn::ecs::component::Container, ::xrn::ecs::Component
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > void addComponent(
        ::xrn::ecs::component::Container& components,
        auto&&... args
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Adds multiple component
    ///
    /// \tparam ComponentTypes Type of components to emplace inside the
    /// ::xrn::ecs::Entity when creating it.
    ///
    /// \param components Component container where to emplace the components
    /// given as template parameter.
    ///
    /// \see ::xrn::ecs::component::Container, ::xrn::ecs::Component
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void addComponents(
        ::xrn::ecs::component::Container& components
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Adds a single component
    ///
    /// Moves the components instead of creating them.
    ///
    /// \tparam ComponentTypes Type of components to emplace inside the
    /// ::xrn::ecs::Entity when creating it.
    ///
    /// \param components Component container where to emplace the components
    /// given as template parameter.
    ///
    /// \see ::xrn::ecs::component::Container, ::xrn::ecs::Component
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void addComponents(
        ::xrn::ecs::component::Container& componentsContainer,
        ComponentTypes&&... components
    );




    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Has components
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks if the entity has a component
    ///
    /// \tparam ComponentTypes Type of component to search
    ///
    /// \param components Component container containing the entity components
    ///
    /// \Return True if the component is contained by the entity
    ///
    /// \see ::xrn::ecs::Component
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto hasComponent() const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks if the entity has all the components
    ///
    /// \tparam ComponentTypes Type of components to search
    ///
    /// \param components Component container containing the entity components
    ///
    /// \Return True if the components are all contained by the entity
    ///
    /// \see ::xrn::ecs::Component
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > [[ nodiscard ]] auto hasComponents() const
        -> bool;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Remove components
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Remove a single component from the entity
    ///
    /// \tparam ComponentTypes Type of components to search
    ///
    /// \param components Component container containing the entity components
    ///
    /// \see ::xrn::ecs::Component
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > void removeComponent(
        ::xrn::ecs::component::Container& container
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Remove multiple components from the entity
    ///
    /// \tparam ComponentTypes Type of components to search
    ///
    /// \param components Component container containing the entity components
    ///
    /// \see ::xrn::ecs::Component
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void removeComponents(
        ::xrn::ecs::component::Container& container
    );



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Getters components
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the signature
    ///
    /// \see ::xrn::ecs::Signature
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto getSignature() const
        -> const ::xrn::ecs::Signature&;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the Id
    ///
    /// \see ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto getId() const
        -> ::xrn::Id;




private:

    ///////////////////////////////////////////////////////////////////////////
    // Id generator always incrementing each assignment, avoiding equal ids.
    ///////////////////////////////////////////////////////////////////////////
    static inline ::xrn::Id m_IdGenerator{ 0 };

    ::xrn::Id m_id{ ++m_IdGenerator };
    ::xrn::ecs::Signature m_signature{};

};



} // namespace xrn::ecs::Entity

#include <Ecs/Entity/Entity.impl.hpp>

namespace xrn::ecs { using Entity = ::xrn::ecs::entity::Entity; }
