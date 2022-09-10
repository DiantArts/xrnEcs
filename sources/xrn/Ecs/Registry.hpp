#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Util.hpp>
#include <xrn/Ecs/Detail/MemoryManager.hpp>
#include <xrn/Ecs/Detail/Constraint.hpp>
#include <xrn/Ecs/Entity.hpp>
#include <xrn/Ecs/Signature.hpp>
// #include <xrn/Ecs/System/Detail/Meta/Function.hpp>



namespace xrn::ecs {

///////////////////////////////////////////////////////////////////////////
/// \brief Contains and handle all components and ::xrn::ecs::Entity
/// \ingroup ecs
///
/// \include Registry.hpp <xrn/Ecs/Registry.hpp>
///
/// Usage example:
/// \code
/// struct struct1 {};
/// struct struct2 {};
/// ::xrn::ecs::Registry<struct1, struct2> registry;
/// auto entity{ registry.createEntity() };
/// registry.emplace<ComponentA>(entity);
/// auto* component{ registry.get<ComponentA>(entity) }; // may return nullptr
/// registry.remove<ComponentA>(entity.getId());
/// registry.push(entity, ComponentA{}, ComponentB{ 5 });
/// \endcode
///
///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> class Registry {

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
    /// Since the size is not specified, the first allocation size will be
    /// Registry::defaultBaseSize.
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline Registry();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    /// \param size Size to allocate
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline explicit Registry(
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
    /// Clears the registry opon destruction.
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline ~Registry();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline Registry(
        const ::xrn::ecs::Registry<ComponentTypes...>& other
    ) noexcept = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline auto operator=(
        const ::xrn::ecs::Registry<ComponentTypes...>& other
    ) noexcept
        -> ::xrn::ecs::Registry<ComponentTypes...>& = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline Registry(
        ::xrn::ecs::Registry<ComponentTypes...>&& that
    ) noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline auto operator=(
        ::xrn::ecs::Registry<ComponentTypes...>&& that
    ) noexcept
        -> ::xrn::ecs::Registry<ComponentTypes...>&;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Entity management
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Create an entity with no component
    ///
    /// \return Entity created
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto createEntity() noexcept
        -> ::xrn::ecs::Entity;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Create an entity and emplace components into it
    ///
    /// Create components inside the container. Those components will be linked
    /// to the entity created.
    ///
    /// \tparam ComponentType Type of the component to create
    ///
    /// \param args   Argument to perfect forward to the constructor of the
    ///               component
    ///
    /// \return Reference to the component created
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...>... Types
    > [[ nodiscard ]] auto createEntity() noexcept
        -> ::xrn::ecs::Entity;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Create an entity and pushes into in already existing components
    ///
    /// Moves already existing components inside the container. Those
    /// components will be linked to the entity created.
    ///
    /// \param components Components to move inside the container
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto createEntity(
        ::xrn::meta::constraint::contains<ComponentTypes...> auto&&... components
    ) noexcept
        -> ::xrn::ecs::Entity;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Component management
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Emplaces a single component
    ///
    /// Creates a component linked to the entity given as parameter.
    ///
    /// \warning The component reference might be invalidated if an action
    ///          other than accessing is performed on the component container.
    ///
    /// \tparam ComponentType Type of the component to create
    ///
    /// \param entity Entity linked to the component
    /// \param args   Argument to perfect forward to the constructor of the
    ///               component
    ///
    /// \return Reference to the component created
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...> ComponentType
    > auto emplaceOne(
        ::xrn::ecs::Entity entity,
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
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...>... Types
    > void emplace(
        ::xrn::ecs::Entity entity
    ) noexcept;

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
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...>... Types
    > void add(
        ::xrn::ecs::Entity entity
    ) noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Pushes an already existing component
    ///
    /// Moves an already existing component inside the container. This
    /// component will be linked to the entity given as parameter.
    ///
    /// \param entity    Entity that contains the component
    /// \param component Component to move inside the container
    ///
    ///////////////////////////////////////////////////////////////////////////
    void pushOne(
        ::xrn::ecs::Entity entity,
        ::xrn::meta::constraint::contains<ComponentTypes...> auto&& component
    ) noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Pushes already existing components
    ///
    /// Moves already existing components inside the container. Those
    /// components will be linked to the entity given as parameter.
    ///
    /// \param entity     Entity that contains the component
    /// \param components Components to move inside the container
    ///
    ///////////////////////////////////////////////////////////////////////////
    void push(
        ::xrn::ecs::Entity entity,
        ::xrn::meta::constraint::contains<ComponentTypes...> auto&&... components
    ) noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Pushes already existing components
    ///
    /// Moves already existing components inside the container. Those
    /// components will be linked to the entity given as parameter.
    ///
    /// \param entity     Entity that contains the component
    /// \param components Components to move inside the container
    ///
    ///////////////////////////////////////////////////////////////////////////
    void add(
        ::xrn::ecs::Entity entity,
        ::xrn::meta::constraint::contains<ComponentTypes...> auto&&... components
    ) noexcept;

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
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...> ComponentType
    > void removeOne(
        ::xrn::ecs::Entity entity
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
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...>... Types
    > void remove(
        ::xrn::ecs::Entity entity
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes all components from an entity
    ///
    /// Deletes all the components of the entity given as parameter from the
    /// container. The destructor of the components will be called.
    ///
    /// \param entity Entity that contains the components
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline void clear(
        ::xrn::ecs::Entity entity
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes all the components of the given type
    ///
    /// Deletes all the components of the type given as template parameter.
    /// The destructor of the components will be called.
    ///
    /// \tparam ComponentTypes Type of the components to delete
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...> ComponentType
    > void clearOne();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes all the components of all the given type
    ///
    /// Deletes all the components of all the types given as template parameter.
    /// The destructor of the components will be called.
    ///
    /// \tparam ComponentTypes Type of the components to delete
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...>... Types
    > void clear();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes all the components of the container
    ///
    /// Deletes all the components of the container. The destructor of the
    /// components will be called.
    /// Same as clearAll().
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline void clear();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes all the components of the container
    ///
    /// Deletes all the components of the container. The destructor of the
    /// components will be called.
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline void clearAll();

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
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...> ComponentType
    > [[ nodiscard ]] auto get(
        ::xrn::ecs::Entity entity
    ) -> ::xrn::OptRef<::std::remove_cvref_t<::std::remove_pointer_t<ComponentType>>>;

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
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...> ComponentType
    > [[ nodiscard ]] auto get(
        ::xrn::ecs::Entity entity
    ) const
        -> ::xrn::OptRef<const ::std::remove_cvref_t<::std::remove_pointer_t<ComponentType>>>;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether a component is contained by the containred
    ///
    /// \return True if the component is contained
    ///
    /// \tparam ComponentType Type of the component to get
    ///
    /// \param entity Entity that contains the component
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...> ComponentType
    > [[ nodiscard ]] auto containsOne(
        ::xrn::ecs::Entity entity
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
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...>... Types
    > [[ nodiscard ]] auto contains(
        ::xrn::ecs::Entity entity
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
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...>... Types
    > [[ nodiscard ]] auto has(
        ::xrn::ecs::Entity entity
    ) const
        -> bool;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Systems
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Runs for each types passed as template parameters
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename FunctionType
    > void run(
        FunctionType function
    );



private:

    ::xrn::ecs::Entity m_currentEntityIndex{ 0 };
    ::std::map<::xrn::ecs::Entity, ::xrn::ecs::Signature<ComponentTypes...>> m_signatures;

    ::std::vector<::std::byte> m_data;
    static constexpr const auto defaultBaseSize{ 1'024uz };
    ::xrn::ecs::detail::MemoryManager<ComponentTypes...> m_memoryManager;

};

} // namespace xrn::ecs::component



///////////////////////////////////////////////////////////////////////////
// Header-implimentation
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs/Registry.impl.hpp>
