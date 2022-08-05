#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <MemoryManager.hpp>



namespace xrn::ecs::component {

///////////////////////////////////////////////////////////////////////////
/// \brief Contains all the components
/// \ingroup ecs-component
///
/// \include Container.hpp <Ecs/Component/Container.hpp>
///
/// Contains all ::xrn::ecs::Component of the ::xrn::ecs::entity::Container and
/// ::xrn::ecs::Entity.
///
/// Usage example:
/// \code
/// TODO code example
/// \endcode
///
/// \see ::xrn::ecs::Entity
///
///////////////////////////////////////////////////////////////////////////
class MegaArray {

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
    MegaArray();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    /// Constructs an ::xrn::ecs::component::Container. The size given as
    /// parameter is the size of the first allocation.
    ///
    /// \param size Size to allocate
    ///
    ///////////////////////////////////////////////////////////////////////////
    explicit MegaArray(
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
    ~MegaArray();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    MegaArray(
        const ::xrn::ecs::component::MegaArray& other
    ) noexcept = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        const ::xrn::ecs::component::MegaArray& other
    ) noexcept
        -> ::xrn::ecs::component::MegaArray& = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    MegaArray(
        ::xrn::ecs::component::MegaArray&& that
    ) noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        ::xrn::ecs::component::MegaArray&& that
    ) noexcept
        -> ::xrn::ecs::component::MegaArray&;



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
    /// \see ::xrn::ecs::component::AComponent, ::xrn::ecs::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > auto emplace(
        ::xrn::ecs::Entity& entity,
        auto&&... args
    ) -> ::std::remove_cvref_t<::std::remove_pointer_t<ComponentType>>&;

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
    /// \see ::xrn::ecs::component::AComponent, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > auto emplace(
        MegaArray::EntityId entityId,
        auto&&... args
    ) -> ::std::remove_cvref_t<::std::remove_pointer_t<ComponentType>>&;

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
    /// \see ::xrn::ecs::component::AComponent, ::xrn::ecs::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void emplaceMany(
        ::xrn::ecs::Entity& entity
    );

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
    /// \see ::xrn::ecs::component::AComponent, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void emplaceMany(
        MegaArray::EntityId entityId
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Pushes an arleady existing component
    ///
    /// Moves an already existing component inside the container. This
    /// component will be linked to the entity given as parameter.
    ///
    /// \param entity    Entity that contains the component
    /// \param component Component to move inside the container
    ///
    /// \see ::xrn::ecs::component::AComponent, ::xrn::ecs::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    void push(
        ::xrn::ecs::Entity& entity,
        ::xrn::ecs::detail::constraint::isComponent auto&& component
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Pushes an arleady existing component
    ///
    /// Moves an already existing component inside the container. This
    /// component will be linked to the entity given as parameter.
    ///
    /// \param entityId  Id referencing the Entity that contains the component
    /// \param component Component to move inside the container
    ///
    /// \see ::xrn::ecs::component::AComponent, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    void push(
        MegaArray::EntityId entityId,
        ::xrn::ecs::detail::constraint::isComponent auto&& component
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Pushes arleady existing components
    ///
    /// Moves already existing components inside the container. Those
    /// components will be linked to the entity given as parameter.
    ///
    /// \param entity     Entity that contains the component
    /// \param components Components to move inside the container
    ///
    /// \see ::xrn::ecs::component::AComponent, ::xrn::ecs::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    void pushMany(
        ::xrn::ecs::Entity& entity,
        ::xrn::ecs::detail::constraint::isComponent auto&&... components
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Pushes arleady existing components
    ///
    /// Moves already existing components inside the container. Those
    /// components will be linked to the entity given as parameter.
    ///
    /// \param entityId   Id referencing the Entity that contains the component
    /// \param components Components to move inside the container
    ///
    /// \see ::xrn::ecs::component::AComponent, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    void pushMany(
        MegaArray::EntityId entityId,
        ::xrn::ecs::detail::constraint::isComponent auto&&... components
    );



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
    /// \see ::xrn::ecs::component::AComponent, ::xrn::ecs::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > void remove(
        ::xrn::ecs::Entity& entity
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
    /// \see ::xrn::ecs::component::AComponent, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > void remove(
        MegaArray::EntityId entityId
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
    /// \see ::xrn::ecs::component::AComponent, ::xrn::ecs::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void removeMany(
        ::xrn::ecs::Entity& entity
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
    /// \see ::xrn::ecs::component::AComponent, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void removeMany(
        MegaArray::EntityId entityId
    );



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Clear
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes all the components of a given type
    ///
    /// Deletes all the components of the type given as template parameter.
    /// The destructor of the components will be called.
    ///
    /// \tparam ComponentType Type of the components to delete
    ///
    /// \see ::xrn::ecs::component::AComponent
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
    /// Same as clearMany().
    ///
    /// \tparam ComponentTypes Type of the components to delete
    ///
    /// \see ::xrn::ecs::component::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void clear();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes all the components of all the given type
    ///
    /// Deletes all the components of all the types given as template parameter.
    /// The destructor of the components will be called.
    ///
    /// \tparam ComponentTypes Type of the components to delete
    ///
    /// \see ::xrn::ecs::component::AComponent
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
    /// \see ::xrn::ecs::component::AComponent, ::xrn::ecs::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto get(
        ::xrn::ecs::Entity& entity
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
    /// \see ::xrn::ecs::component::AComponent, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto get(
        MegaArray::EntityId entityId
    ) -> ::std::remove_cvref_t<::std::remove_pointer_t<ComponentType>>*;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether a component is contained by the containred
    ///
    /// \return True if the component is contained
    ///
    /// \tparam ComponentType Type of the component to get
    ///
    /// \param entity Entity that contains the component
    ///
    /// \see ::xrn::ecs::component::AComponent, ::xrn::ecs::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto contains(
        ::xrn::ecs::Entity& entity
    ) -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether a component is contained by the containred
    ///
    /// \return True if the component is contained
    ///
    /// \tparam ComponentType Type of the component to get
    ///
    /// \param entityId Id referencing the Entity that contains the component
    ///
    /// \see ::xrn::ecs::component::AComponent, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto contains(
        MegaArray::EntityId entityId
    ) -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether components are contained by the containred
    ///
    /// \return True if all the components are contained
    ///
    /// \tparam ComponentTypes Types of the components to get
    ///
    /// \param entity Entity that contains the components
    ///
    /// \see ::xrn::ecs::component::AComponent, ::xrn::ecs::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > [[ nodiscard ]] auto contains(
        ::xrn::ecs::Entity& entity
    ) -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether a component is contained by the containred
    ///
    /// \return True if the component is contained
    ///
    /// \tparam ComponentTypes Types of the components to get
    ///
    /// \param entityId Id referencing the Entity that contains the components
    ///
    /// \see ::xrn::ecs::component::AComponent, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > [[ nodiscard ]] auto contains(
        MegaArray::EntityId entityId
    ) -> bool;



private:

    static constexpr const auto defaultBaseSize{ 1024uz };
    ::xrn::ecs::component::detail::MemoryManager m_memoryManager;
    ::std::vector<::std::byte> m_data;

};

} // namespace xrn::ecs::component
