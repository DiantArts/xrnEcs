#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Ecs/Component/Detail/MemoryManager.hpp>
#include <Ecs/Detail/Constraint.hpp>

///////////////////////////////////////////////////////////////////////////
// Forward declarations
///////////////////////////////////////////////////////////////////////////
namespace xrn::ecs::entity { class Entity; }



namespace xrn::ecs::component {

///////////////////////////////////////////////////////////////////////////
/// \brief Contains all the components
/// \ingroup ecs-component
///
/// \include Container.hpp <Ecs/Component/Container.hpp>
///
/// Contains all ::xrn::ecs::Component of the ::xrn::ecs::entity::Container and
/// ::xrn::ecs::entity::Entity.
///
/// Usage example:
/// \code
/// TODO code example
/// \endcode
///
/// \see ::xrn::ecs::entity::Entity
///
///////////////////////////////////////////////////////////////////////////
class Container {

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
    using ComponentId = ::xrn::Id;
    using ComponentAddr = void*;
    using EntityId = ::xrn::Id;



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
    /// Constructs an ::xrn::ecs::component::Container. Since the size is not
    /// specified, the allocation size will be
    /// ::xrn::ecs::component::Container::defaultBaseSize.
    /// This default size is the size of the first allocation.
    ///
    ///////////////////////////////////////////////////////////////////////////
    Container();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    /// Constructs an ::xrn::ecs::component::Container. The size given as
    /// parameter is the size of the first allocation.
    ///
    /// \param size Size to allocate
    ///
    ///////////////////////////////////////////////////////////////////////////
    explicit Container(
        ::std::size_t size
    );



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Rule of 5
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    /// Clears every component of every entity.
    ///
    ///////////////////////////////////////////////////////////////////////////
    ~Container();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    Container(
        const ::xrn::ecs::component::Container& other
    ) noexcept = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        const ::xrn::ecs::component::Container& other
    ) noexcept
        -> ::xrn::ecs::component::Container& = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    Container(
        ::xrn::ecs::component::Container&& that
    ) noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        ::xrn::ecs::component::Container&& that
    ) noexcept
        -> ::xrn::ecs::component::Container&;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Emplace
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Emplaces a component
    ///
    /// Creates a component and place it inside the container. This component
    /// will be linked to the entity given as parameter.
    ///
    /// \warning The reference might be unvalidated when another component is
    ///          created. Accessing the reference after a non const method
    ///          might lead to undefined behaviors.
    ///
    /// \return Reference to the component created
    ///
    /// \tparam ComponentType Type of the component to create
    ///
    /// \param entity Entity that contains the component
    /// \param args   Argument to perfect forward to the constructor of the
    ///               component
    ///
    /// \returns Reference to the component created
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent, ::xrn::ecs::entity::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > auto emplace(
        ::xrn::ecs::entity::Entity& entity,
        auto&&... args
    ) noexcept -> ::std::remove_cvref_t<::std::remove_pointer_t<ComponentType>>&;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Emplaces a component
    ///
    /// Creates a component and place it inside the container. This component
    /// will be linked to the entity given as parameter.
    ///
    /// \warning The reference might be unvalidated when another component is
    ///          created. Accessing the reference after a non const method
    ///          might lead to undefined behaviors.
    ///
    /// \return Reference to the component created
    ///
    /// \tparam ComponentType Type of the component to create
    ///
    /// \param entityId Id referencing the Entity that contains the component
    /// \param args     Argument to perfect forward to the constructor of the
    ///                 component
    ///
    /// \returns Reference to the component created
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > auto emplace(
        Container::EntityId entityId,
        auto&&... args
    ) noexcept -> ::std::remove_cvref_t<::std::remove_pointer_t<ComponentType>>&;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Emplaces multiple components
    ///
    /// Creates multiple component and place them inside the container. Those
    /// components will be linked to the entity given as parameter.
    ///
    /// \tparam ComponentTypes Type of the components to create
    ///
    /// \param entity Entity that contains the component
    /// \param args   Argument to perfect forward to the constructor of the
    ///               component
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent, ::xrn::ecs::entity::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void emplaceMany(
        ::xrn::ecs::entity::Entity& entity
    ) noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Emplaces multiple components
    ///
    /// Creates multiple component and place them inside the container. Those
    /// components will be linked to the entity given as parameter.
    ///
    /// \tparam ComponentTypes Type of the components to create
    ///
    /// \param entityId Id referencing the Entity that contains the component
    /// \param args     Argument to perfect forward to the constructor of the
    ///                 component
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void emplaceMany(
        Container::EntityId entityId
    ) noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Pushes an arleady existing component
    ///
    /// Moves an already existing component inside the container. This
    /// component will be linked to the entity given as parameter.
    ///
    /// \param entity    Entity that contains the component
    /// \param component Component to move inside the container
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent, ::xrn::ecs::entity::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    void push(
        ::xrn::ecs::entity::Entity& entity,
        ::xrn::ecs::detail::constraint::isComponent auto&& component
    ) noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Pushes an arleady existing component
    ///
    /// Moves an already existing component inside the container. This
    /// component will be linked to the entity given as parameter.
    ///
    /// \param entityId  Id referencing the Entity that contains the component
    /// \param component Component to move inside the container
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    void push(
        Container::EntityId entityId,
        ::xrn::ecs::detail::constraint::isComponent auto&& component
    ) noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Pushes arleady existing components
    ///
    /// Moves already existing components inside the container. Those
    /// components will be linked to the entity given as parameter.
    ///
    /// \param entity     Entity that contains the component
    /// \param components Components to move inside the container
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent, ::xrn::ecs::entity::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    void pushMany(
        ::xrn::ecs::entity::Entity& entity,
        ::xrn::ecs::detail::constraint::isComponent auto&&... components
    ) noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Pushes arleady existing components
    ///
    /// Moves already existing components inside the container. Those
    /// components will be linked to the entity given as parameter.
    ///
    /// \param entityId   Id referencing the Entity that contains the component
    /// \param components Components to move inside the container
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    void pushMany(
        Container::EntityId entityId,
        ::xrn::ecs::detail::constraint::isComponent auto&&... components
    ) noexcept;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Remove
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes a component
    ///
    /// Deletes the component of the entity given as parameter from the
    /// container. The destructor of the component will be called.
    ///
    /// \tparam ComponentType Type of the component to delete
    ///
    /// \param entity Entity that contains the component
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent, ::xrn::ecs::entity::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > void remove(
        ::xrn::ecs::entity::Entity& entity
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes a component
    ///
    /// Deletes the component of the entity given as parameter from the
    /// container. The destructor of the component will be called.
    ///
    /// \tparam ComponentType Type of the component to delete
    ///
    /// \param entityId Id referencing the Entity that contains the component
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > void remove(
        Container::EntityId entityId
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes a component
    ///
    /// Deletes the components of the entity given as parameter from the
    /// container. The destructor of the components will be called.
    ///
    /// \tparam ComponentTypes Type of the components to delete
    ///
    /// \param entity Entity that contains the components
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent, ::xrn::ecs::entity::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void removeMany(
        ::xrn::ecs::entity::Entity& entity
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes a component
    ///
    /// Deletes the components of the entity given as parameter from the
    /// container. The destructor of the components will be called.
    ///
    /// \tparam ComponentTypes Type of the components to delete
    ///
    /// \param entityId Id referencing the Entity that contains the components
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void removeMany(
        Container::EntityId entityId
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes all components from an entity
    ///
    /// Deletes all the components of the entity given as parameter from the
    /// container. The destructor of the components will be called.
    ///
    /// \param entity Entity that contains the components
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent, ::xrn::ecs::entity::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    void removeAll(
        ::xrn::ecs::entity::Entity& entity
    );



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Clear
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes all the components of the given type
    ///
    /// Deletes all the components of the type given as template parameter.
    /// The destructor of the components will be called.
    ///
    /// \tparam ComponentTypes Type of the components to delete
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > void clear();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes all the components of all the given type
    ///
    /// Deletes all the components of all the types given as template parameter.
    /// The destructor of the components will be called.
    ///
    /// \tparam ComponentTypes Type of the components to delete
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void clearMany();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes all the components of the container
    ///
    /// Deletes all the components of the container. The destructor of the
    /// components will be called.
    /// Same as clearAll().
    ///
    ///////////////////////////////////////////////////////////////////////////
    void clear();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes all the components of the container
    ///
    /// Deletes all the components of the container. The destructor of the
    /// components will be called.
    ///
    ///////////////////////////////////////////////////////////////////////////
    void clearAll();



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Accessors
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets a component
    ///
    /// Access a component inside the container. The type returned is a pointer
    /// initaized to nullptr if the component were not in the container.
    ///
    /// \warning The reference might be unvalidated when another component is
    ///          created. Accessing the reference after a non const method
    ///          might lead to undefined behaviors.
    ///
    /// \tparam ComponentTypes Type of the components to get
    ///
    /// \param entity Entity that contains the components
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent, ::xrn::ecs::entity::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto get(
        ::xrn::ecs::entity::Entity& entity
    ) -> ::std::remove_cvref_t<::std::remove_pointer_t<ComponentType>>*;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets a component
    ///
    /// Access a component inside the container. The type returned is a pointer
    /// initaized to nullptr if the component were not in the container.
    ///
    /// \warning The reference might be unvalidated when another component is
    ///          created. Accessing the reference after a non const method
    ///          might lead to undefined behaviors.
    ///
    /// \return Pointer to the component
    ///
    /// \tparam ComponentTypes Type of the components to get
    ///
    /// \param entityId Id referencing the Entity that contains the components
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto get(
        Container::EntityId entityId
    ) -> ::std::remove_cvref_t<::std::remove_pointer_t<ComponentType>>*;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets a component
    ///
    /// Access a component inside the container. The type returned is a pointer
    /// initaized to nullptr if the component were not in the container.
    ///
    /// \warning The reference might be unvalidated when another component is
    ///          created. Accessing the reference after a non const method
    ///          might lead to undefined behaviors.
    ///
    /// \tparam ComponentTypes Type of the components to get
    ///
    /// \param entity Entity that contains the components
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent, ::xrn::ecs::entity::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto get(
        ::xrn::ecs::entity::Entity& entity
    ) const
        -> const ::std::remove_cvref_t<::std::remove_pointer_t<ComponentType>>*;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets a component
    ///
    /// Access a component inside the container. The type returned is a pointer
    /// initaized to nullptr if the component were not in the container.
    ///
    /// \warning The reference might be unvalidated when another component is
    ///          created. Accessing the reference after a non const method
    ///          might lead to undefined behaviors.
    ///
    /// \return Pointer to the component
    ///
    /// \tparam ComponentTypes Type of the components to get
    ///
    /// \param entityId Id referencing the Entity that contains the components
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto get(
        Container::EntityId entityId
    ) const
        -> const ::std::remove_cvref_t<::std::remove_pointer_t<ComponentType>>*;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether a component is contained by the containred
    ///
    /// \return True if the component is contained
    ///
    /// \tparam ComponentType Type of the component to get
    ///
    /// \param entity Entity that contains the component
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent, ::xrn::ecs::entity::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto contains(
        ::xrn::ecs::entity::Entity& entity
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether a component is contained by the containred
    ///
    /// \return True if the component is contained
    ///
    /// \tparam ComponentType Type of the component to get
    ///
    /// \param entityId Id referencing the Entity that contains the component
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto contains(
        Container::EntityId entityId
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether components are contained by the containred
    ///
    /// \return True if all the components are contained
    ///
    /// \tparam ComponentTypes Types of the components to get
    ///
    /// \param entity Entity that contains the components
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent, ::xrn::ecs::entity::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > [[ nodiscard ]] auto containsMany(
        ::xrn::ecs::entity::Entity& entity
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether a component is contained by the containred
    ///
    /// \return True if the component is contained
    ///
    /// \tparam ComponentTypes Types of the components to get
    ///
    /// \param entityId Id referencing the Entity that contains the components
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > [[ nodiscard ]] auto containsMany(
        Container::EntityId entityId
    ) const
        -> bool;



private:

    static constexpr const auto defaultBaseSize{ 1024uz };
    ::xrn::ecs::component::detail::MemoryManager m_memoryManager;
    ::std::vector<::std::byte> m_data;

};

} // namespace xrn::ecs::component



///////////////////////////////////////////////////////////////////////////
// Header-implimentation
///////////////////////////////////////////////////////////////////////////
#include <Ecs/Component/Container.impl.hpp>
