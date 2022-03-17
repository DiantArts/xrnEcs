#pragma once

#include <Ecs/Entity/Entity.hpp>
#include <Ecs/Entity/ConstReference.hpp>



namespace xrn::ecs::component { class Container; }

///////////////////////////////////////////////////////////////////////////
/// \brief Contains all the entities
/// \ingroup ecs-entity
///
/// \include Reference.hpp <Ecs/Entity/Reference.hpp>
///
/// Refers to an ::xrn::ecs::entity::Entity, the difference between a
/// ::xrn::ecs::entity::Entity::Reference and a ::xrn::ecs::entity::Entity::ConstReference
/// is that xrn::ecs::Entity::Reference contains a reference to a
/// ::xrn::ecs::component::Container that is passed to the constructor. It
/// allows actions like addComponent() and removeComponent() that are not
/// possible with ::xrn::ecs::entity::Entity::ConstReference.
///
/// Usage example:
/// \code
/// ::xrn::ecs::component::Container components;
/// ::xrn::ecs::entity::Entity entity;
/// ::xrn::ecs::entity::Entity::Reference ref{ components, entity };
/// ref.addComponent<::xrn::ecs::component::test::ComponentA, ::xrn::ecs::component::test::ComponentB>();
///
/// entity.hasComponent<::xrn::ecs::component::test::ComponentA>(); // true
/// ref.hasComponent<::xrn::ecs::component::test::ComponentA>(); // true
/// entity.hasComponent<::xrn::ecs::component::test::ComponentB>(); // true
/// ref.hasComponent<::xrn::ecs::component::test::ComponentB>(); // true
/// \endcode
///
/// \see ::xrn::ecs::entity::Entity, ::xrn::ecs::entity::Entity::ConstReference,
///      ::xrn::ecs::component::Container
///
///////////////////////////////////////////////////////////////////////////
class xrn::ecs::Entity::Reference {

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
    /// Constructs a xrn::ecs::Entity::ConstReference but does not store
    /// anything. This reference will be invalid.
    ///
    ///////////////////////////////////////////////////////////////////////////
    explicit Reference() noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    /// Constructs a xrn::ecs::Entity::Reference from an ::xrn::ecs::entity::Entity and
    /// a ::xrn::ecs::component::Container.
    ///
    /// \param components Container containing the entity's components
    /// \param entity Entity that the class is refering to
    ///
    /// \see ::xrn::ecs::entity::Entity, ::xrn::ecs::component::Container
    ///
    ///////////////////////////////////////////////////////////////////////////
    explicit Reference(
        ::xrn::ecs::Entity& entity,
        ::xrn::ecs::component::Container& components
    ) noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Constructor with argument order reversed
    ///
    /// Constructs a xrn::ecs::Entity::Reference from an ::xrn::ecs::entity::Entity and
    /// a ::xrn::ecs::component::Container.
    ///
    /// \param components Container containing the entity's components
    /// \param entity Entity that the class is refering to
    ///
    /// \see ::xrn::ecs::entity::Entity, ::xrn::ecs::component::Container
    ///
    ///////////////////////////////////////////////////////////////////////////
    explicit Reference(
        ::xrn::ecs::component::Container& components,
        ::xrn::ecs::Entity& entity
    ) noexcept;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // AddComponents
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Creates a single component to the ::xrn::ecs::entity::Entity referred
    ///
    /// Creates the component given as template paremeter by perfect forwading
    /// the arguments to the constructor of the component.
    ///
    /// \tparam ComponentType Type of component to emplace inside the
    ///         ::xrn::ecs::entity::Entity when creating it.
    ///
    /// \param args Arguments to perfect forward to the constructor of the
    ///        component to create
    ///
    /// \see ::xrn::ecs::entity::Entity, ::xrn::ecs::Component
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > void addComponent(
        auto&&... args
    ) const;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Creates multiple components to the ::xrn::ecs::entity::Entity referred
    ///
    /// Creates the component given as template paremeter by perfect forwading
    /// the arguments to the constructor of the component.
    ///
    /// \tparam ComponentTypes Type of components to emplace inside the
    ///         ::xrn::ecs::entity::Entity when creating it.
    ///
    /// \see ::xrn::ecs::entity::Entity, ::xrn::ecs::Component
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void addComponents();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Creates multiple components to the ::xrn::ecs::entity::Entity referred
    ///
    /// Creates the component given as template paremeter by perfect forwading
    /// the arguments to the constructor of the component.
    ///
    /// \tparam ComponentTypes Type of components to emplace inside the
    ///         ::xrn::ecs::entity::Entity when creating it.
    ///
    /// \param components Component container where to emplace the components
    ///        given as template parameter.
    /// \param args Arguments to perfect forward to the constructor of the
    ///        component to create
    ///
    /// \see ::xrn::ecs::entity::Entity, ::xrn::ecs::Component
    ///
    ///////////////////////////////////////////////////////////////////////////
    void addComponents(
        ::xrn::ecs::detail::constraint::isComponent auto&&... components
    );




    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // HasComponents
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks if the ::xrn::ecs::entity::Entity referred has the component
    ///
    /// \tparam ComponentTypes Type of component to search
    ///
    /// \Return True if the component is contained by the entity
    ///
    /// \see ::xrn::ecs::entity::Entity, ::xrn::ecs::Component
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto hasComponent() const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks if the ::xrn::ecs::entity::Entity referred has multiple components
    ///
    /// \tparam ComponentTypes Type of component to search
    ///
    /// \Return True if the component is contained by the entity
    ///
    /// \see ::xrn::ecs::entity::Entity, ::xrn::ecs::Component
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > [[ nodiscard ]] auto hasComponents() const
        -> bool;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // RemoveComponents
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Remove a single component from the ::xrn::ecs::entity::Entity referred
    ///
    /// \tparam ComponentTypes Type of components to search
    ///
    /// \see ::xrn::ecs::entity::Entity, ::xrn::ecs::Component
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > void removeComponent();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Remove multiple components from the ::xrn::ecs::entity::Entity referred
    ///
    /// \tparam ComponentTypes Type of components to search
    ///
    /// \see ::xrn::ecs::entity::Entity, ::xrn::ecs::Component
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void removeComponents();



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
    [[ nodiscard ]] auto isValid() const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the signature of the ::xrn::ecs::entity::Entity referred
    ///
    /// \see ::xrn::ecs::entity::Entity, ::xrn::ecs::Signature
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto getSignature() const
        -> const ::xrn::ecs::Signature&;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the Id of the ::xrn::ecs::entity::Entity referred
    ///
    /// \see ::xrn::ecs::entity::Entity, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto getId() const
        -> ::xrn::Id;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the ::xrn::ecs::entity::Entity referred
    ///
    /// \see ::xrn::ecs::entity::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto get()
        -> ::xrn::ecs::Entity&;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the ::xrn::ecs::entity::Entity referred
    ///
    /// \see ::xrn::ecs::entity::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto get() const
        -> const ::xrn::ecs::Entity&;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Implicitly converts the reference into the ::xrn::ecs::entity::Entity
    /// referred
    ///
    /// \see ::xrn::ecs::entity::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] operator const ::xrn::ecs::Entity&() const;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Implicitly converts the mutable reference into a
    /// xrn::ecs::Entity::ConstReference
    ///
    /// \see xrn::ecs::Entity::ConstReference
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] operator ::xrn::ecs::Entity::ConstReference() const;




private:

    ::xrn::ecs::component::Container* m_components;
    ::xrn::ecs::Entity* m_entity;

};



///////////////////////////////////////////////////////////////////////////
// Header-implimentation
///////////////////////////////////////////////////////////////////////////
#include <Ecs/Entity/Reference.impl.hpp>
