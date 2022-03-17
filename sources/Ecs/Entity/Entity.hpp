// Using an Entity composed with Both a Base and Derived class result in an undefined behavior

#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Util/Id.hpp>
#include <Ecs/Detail/Constraint.hpp>
#include <Ecs/Signature.hpp>
#include <Ecs/Component/Detail/ForEach.hpp>

namespace xrn::ecs::component { class Container; }



namespace xrn::ecs::entity {

///////////////////////////////////////////////////////////////////////////
/// \brief Representation of an entity in the xrn ecs Project
/// \ingroup ecs-entity
///
/// \include Entity.hpp <Ecs/Entity/Entity.hpp>
///
/// ::xrn::ecs::Entity represents a general-purpose object. It allows to add
/// and remove Components and Abilities (as well as check if it possesses one).
/// It possesses an Id and a Signature that the user can get.
/// This class is aliased with ::xrn::Entity.
///
/// Usage example:
/// \code
/// ::xrn::ecs::component::Container components;
/// ::xrn::ecs::Entity entity1;
/// entity1.addComponent<::xrn::ecs::component::test::ComponentA>(components);
/// entity1.hasComponent<::xrn::ecs::component::test::ComponentA>(); // true
/// entity1.hasComponent<::xrn::ecs::component::test::ComponentB>(); // false
/// entity1.removeComponent<::xrn::ecs::component::test::ComponentA>(components);
/// entity1.hasComponent<::xrn::ecs::component::test::ComponentA>(); // false
/// entity1.hasComponent<::xrn::ecs::component::test::ComponentB>(); // false
/// \endcode
///
/// \see ::xrn::ecs::component::Container, ::xrn::ecs::Signature,
///      ::xrn::util::Id
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

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Constructs an ::xrn::ecs::Entity with components and abilities
    ///
    /// \tparam Types Type of components and abilities to emplace inside the
    ///         ::xrn::ecs::Entity when creating it.
    ///
    /// \param components Component container where to emplace the components
    ///        given as template parameter.
    ///
    /// \return New ::xrn::ecs::Entity just created
    ///
    /// \see ::xrn::ecs::component::Container
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename... Types
    > [[ nodiscard ]] static constexpr auto generate(
        ::xrn::ecs::component::Container& components
    ) -> ::xrn::ecs::entity::Entity;



public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Add
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    template <
        typename... Types
    > void add(
        ::xrn::ecs::component::Container& components
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Adds a single component
    ///
    /// Creates the component by perfect forwading the arguments to the
    /// constructor of the component.
    ///
    /// \tparam ComponentTypes Type of components to emplace inside the
    /// ::xrn::ecs::Entity when creating it.
    ///
    /// \param components Component container where to emplace the components
    ///        given as template parameter.
    ///
    /// \see ::xrn::ecs::component::Container
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > void addComponent(
        ::xrn::ecs::component::Container& components,
        auto&&... args
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Adds multiple components
    ///
    /// \tparam ComponentTypes Type of components to emplace inside the
    /// ::xrn::ecs::Entity when creating it.
    ///
    /// \param components Component container where to emplace the components
    /// given as template parameter.
    ///
    /// \see ::xrn::ecs::component::Container
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
    /// \see ::xrn::ecs::component::Container
    ///
    ///////////////////////////////////////////////////////////////////////////
    void addComponents(
        ::xrn::ecs::component::Container& componentsContainer,
        ::xrn::ecs::detail::constraint::isComponent auto&&... components
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Adds a single ability
    ///
    /// \tparam ComponentTypes Type of abilitys to emplace inside the
    /// ::xrn::ecs::Entity when creating it.
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isAbility AbilityType
    > void addAbility();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Adds multiple abilities
    ///
    /// \tparam ComponentTypes Type of abilitys to emplace inside the
    /// ::xrn::ecs::Entity when creating it.
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isAbility... AbilityTypes
    > void addAbilities();




    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Has
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks if the entity has the components or abilities
    ///
    /// \tparam Types Types to search
    ///
    /// \Return True if the components or abilities are contained by the entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename... Types
    > [[ nodiscard ]] auto has() const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks if the entity has the component
    ///
    /// \tparam ComponentType Type of component to search
    ///
    /// \Return True if the component is contained by the entity
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
    /// \Return True if the components are all contained by the entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > [[ nodiscard ]] auto hasComponents() const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks if the entity has the ability
    ///
    /// \tparam ComponentType Type of ability to search
    ///
    /// \Return True if the ability is contained by the entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isAbility AbilityType
    > [[ nodiscard ]] auto hasAbility() const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks if the entity has all the abilities
    ///
    /// \tparam ComponentTypes Type of abilities to search
    ///
    /// \Return True if the abilities are all contained by the entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isAbility... AbilityTypes
    > [[ nodiscard ]] auto hasAbilities() const
        -> bool;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Remove
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    /// \brief Remove multiple components and abilities from the entity
    ///
    /// \tparam Types Type of components and entities to remove
    ///
    /// \param components Component container containing the entity components
    ///
    /// \see ::xrn::ecs::component::Container
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename... Types
    > void remove(
        ::xrn::ecs::component::Container& container
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Remove a single component from the entity
    ///
    /// \tparam ComponentTypes Type of components to remove
    ///
    /// \param components Component container containing the entity components
    ///
    /// \see ::xrn::ecs::component::Container
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
    /// \tparam ComponentTypes Type of components to remove
    ///
    /// \param components Component container containing the entity components
    ///
    /// \see ::xrn::ecs::component::Container
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void removeComponents(
        ::xrn::ecs::component::Container& container
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Remove a single ability from the entity
    ///
    /// \tparam ComponentTypes Type of ability to remove
    ///
    /// \param ability Component container containing the entity ability
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isAbility AbilityType
    > void removeAbility();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Remove multiple abilities from the entity
    ///
    /// \tparam ComponentTypes Type of abilities to remove
    ///
    /// \param abilities Component container containing the entity abilities
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isAbility... AbilityTypes
    > void removeAbilities();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Remove all components and abilities from the entity
    ///
    /// \param components Component container containing the entity components
    ///
    /// \see ::xrn::ecs::component::Container
    ///
    ///////////////////////////////////////////////////////////////////////////
    void remove(
        ::xrn::ecs::component::Container& container
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Remove all components from the entity
    ///
    /// \param components Component container containing the entity components
    ///
    /// \see ::xrn::ecs::component::Container
    ///
    ///////////////////////////////////////////////////////////////////////////
    void removeComponents(
        ::xrn::ecs::component::Container& components
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Remove all abilities from the entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    void removeAbilities();



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Getters
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



///////////////////////////////////////////////////////////////////////////
// Alias name
///////////////////////////////////////////////////////////////////////////
namespace xrn::ecs { using Entity = ::xrn::ecs::entity::Entity; }



///////////////////////////////////////////////////////////////////////////
// Header-implimentation
///////////////////////////////////////////////////////////////////////////
#include <Ecs/Entity/Entity.impl.hpp>
