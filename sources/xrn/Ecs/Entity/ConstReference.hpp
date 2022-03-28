#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs/Entity/Entity.hpp>

///////////////////////////////////////////////////////////////////////////
// Forward declarations
///////////////////////////////////////////////////////////////////////////
namespace xrn::ecs::component { class Container; }



namespace xrn::ecs::entity {

///////////////////////////////////////////////////////////////////////////
/// \brief A const reference to an ::xrn::ecs::entity::Entity
/// \ingroup ecs-entity
///
/// \include Reference.hpp <xrn/Ecs/Entity/Reference.hpp>
///
/// Refers to an ::xrn::ecs::entity::Entity, the difference between a
/// ::xrn::ecs::entity::Reference and a
/// ::xrn::ecs::entity::ConstReference is that
/// ::xrn::ecs::entity::Reference contains a reference to a
/// ::xrn::ecs::component::Container that is passed to the constructor. It
/// allows actions like addComponent() and removeComponent() that are not
/// possible with ::xrn::ecs::entity::ConstReference.
///
/// Usage example:
/// \code
/// using namespace ::xrn::ecs::component::test;
///
/// ::xrn::ecs::component::Container components;
/// ::xrn::ecs::entity::Entity entity;
/// ::xrn::ecs::entity::ConstReference ref{ entity };
///
/// entity.hasComponent<ComponentA>(); // false
/// entity.hasComponent<ComponentB>(); // false
/// ref.hasComponent<ComponentA>(); // false
/// ref.hasComponent<ComponentB>(); // false
///
/// entity.addComponents<ComponentA, ComponentB>(components);
///
/// entity.hasComponents<ComponentA, ComponentB>() // true;
/// ref.hasComponents<ComponentA, ComponentB>() // true;
/// \endcode
///
/// \see ::xrn::ecs::entity::Entity, ::xrn::ecs::entity::Reference,
///      ::xrn::ecs::component::Container
///
///////////////////////////////////////////////////////////////////////////
class ConstReference {

public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Null constructor
    ///
    /// Constructs a xrn::ecs::entity::ConstReference but does not store
    /// anything. This reference will be invalid.
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline ConstReference() noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    /// Constructs a xrn::ecs::entity::ConstReference from an
    /// ::xrn::ecs::entity::Entity.
    ///
    /// \param entity Entity that the class is refering to
    ///
    /// \see ::xrn::ecs::entity::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline explicit ConstReference(
        const ::xrn::ecs::entity::Entity& entity
    ) noexcept;



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
        ::xrn::ecs::detail::constraint::isEcsRegistered... Types
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
    // GetComponents
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the entity component
    ///
    /// \warning The component pointer might be invalidated if an action other
    ///          than accessing is performed on the component container.
    ///
    /// \tparam ComponentType Component to search in the container and return
    ///         if existing
    ///
    /// \param components Container of components
    ///
    /// \return Pointer to the component, or nullptr if the component does not
    ///         exist.
    ///
    /// \see ::xrn::util::BasicForwardId
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto getComponent(
        const ::xrn::ecs::component::Container& components
    ) const
        -> const ::std::remove_cvref_t<::std::remove_pointer_t<ComponentType>>*;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Getters
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks if the reference is valid
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] inline auto isValid() const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the signature of the ::xrn::ecs::entity::Entity referred
    ///
    /// \see ::xrn::ecs::entity::Entity, ::xrn::ecs::Signature
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] inline auto getSignature() const
        -> const ::xrn::ecs::Signature&;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the Id of the ::xrn::ecs::entity::Entity referred
    ///
    /// \see ::xrn::ecs::entity::Entity, ::xrn::util::BasicForwardId
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] inline auto getId() const
        -> ::xrn::Id;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the ::xrn::ecs::entity::Entity referred
    ///
    /// \see ::xrn::ecs::entity::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] inline auto get() const
        -> const ::xrn::ecs::entity::Entity&;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Implicitly converts the refernce into the ::xrn::ecs::entity::Entity
    /// referred
    ///
    /// \see ::xrn::ecs::entity::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] inline operator const ::xrn::ecs::entity::Entity&() const;




private:

    const ::xrn::ecs::entity::Entity* m_entity;

};

} // namespace xrn::ecs::entity



///////////////////////////////////////////////////////////////////////////
// Header-implimentation
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs/Entity/ConstReference.impl.hpp>
