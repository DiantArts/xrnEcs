#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs/Component/Container.hpp>
#include <xrn/Ecs/Entity/Entity.hpp>
#include <xrn/Ecs/Entity/Reference.hpp>



namespace xrn::ecs::entity {

///////////////////////////////////////////////////////////////////////////
/// \brief Contains all the entities
/// \ingroup ecs-entity
///
/// \include Container.hpp <xrn/Ecs/Entity/Container.hpp>
///
/// Contains all ::xrn::ecs::entity::Entity needed for the ECS architecture. All the
/// entity components are placed in the ::xrn::ecs::component::Container passed
/// as constructor argument. This container is kept as reference.
///
/// Usage example:
/// \code
/// ::xrn::ecs::component::Container components;
/// ::xrn::ecs::entity::Container entities{ components };
/// auto entity1{ entities.emplace<::xrn::ecs::component::test::ComponentA>() };
/// auto entity2{ entities.get(entity1.getId()) }; // same as entity1
/// auto entity3{ entities[entity1.getId()] }; // same as entity1
///
/// entities.contains(entity1.getId()); // true
/// &entities.unsafeGet(entity1.getId()).get() == &entity1.get(); // true
/// &entity1.get() == &entity2.get(); // true
/// &entity1.get() == &entity3.get(); // true
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
    using Type = ::std::vector<::xrn::ecs::entity::Entity>;




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
    /// Constructs an ::xrn::ecs::entity::Container.
    ///
    /// \param amount Time in milliseconds
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline explicit Container(
        ::xrn::ecs::component::Container& componentContainer
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
    inline ~Container();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    Container(
        const ::xrn::ecs::entity::Container& other
    ) noexcept = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        const ::xrn::ecs::entity::Container& other
    ) noexcept
        -> ::xrn::ecs::entity::Container& = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    Container(
        ::xrn::ecs::entity::Container&& that
    ) noexcept = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        ::xrn::ecs::entity::Container&& that
    ) noexcept
        -> ::xrn::ecs::entity::Container& = delete;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Emplace
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Emplaces an entity
    ///
    /// Creates an entity from the component given as template parameter.
    ///
    /// \warning The returned ::xrn::ecs::entity::Reference may be invalid.
    ///          The user must call ::xrn::ecs::entity::Reference::isValid()
    ///          if he isn't certain that the entity is present in the
    ///          container to check its validity.
    /// \warning This reference may be invalidated when an entity is created.
    ///
    /// \tparam ComponentTypes Type of components to emplace inside the
    /// ::xrn::ecs::entity::Entity when creating it
    ///
    /// \param amount Time in milliseconds
    ///
    /// \returns An ::xrn::ecs::entity::Reference to the entity emplaced
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isEcsRegistered... ComponentTypes
    > auto emplace()
        -> ::xrn::ecs::entity::Reference;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Emplaces an entity
    ///
    /// Creates an entity from the component given as template parameter.
    ///
    /// \warning The returned ::xrn::ecs::entity::Reference may be invalid.
    ///          The user must call ::xrn::ecs::entity::Reference::isValid()
    ///          if he isn't certain that the entity is present in the
    ///          container to check its validity.
    /// \warning This reference may be invalidated when an entity is created.
    ///
    /// \param components Components to emplace inside the entity created
    ///
    /// \returns An ::xrn::ecs::entity::Reference to the entity emplaced
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline auto emplace(
        ::xrn::ecs::detail::constraint::isComponent auto&&... components
    ) -> ::xrn::ecs::entity::Reference;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Remove
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes an ::xrn::ecs::entity::Entity from the container
    ///
    /// Remove the entity that matches the ::xrn::util::BasicForwardId given as
    /// parameter.
    ///
    /// \param Entity entity to find and delete
    ///
    /// \see ::xrn::ecs::entity::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline void remove(
        ::xrn::Id entityId
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes an ::xrn::ecs::entity::Entity from the container
    ///
    /// Remove the entity that matches the ::xrn::util::BasicForwardId given as
    /// parameter.
    ///
    /// \param entity Id to find and delete
    ///
    /// \see ::xrn::util::BasicForwardId
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline void remove(
        const ::xrn::ecs::Entity& entity
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes an ::xrn::ecs::entity::Entity from the container
    ///
    /// Remove the entity referenced by the ::xrn::ecs::entity::Reference.
    ///
    /// \param entityReference Entity to find and delete
    ///
    /// \see ::xrn::ecs::entity::Reference
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline void remove(
        const ::xrn::ecs::entity::Reference& entityReference
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes an ::xrn::ecs::entity::Entity from the container
    ///
    /// Remove the entity referenced by the ::xrn::ecs::entity::ConstReference.
    ///
    /// \param entityReference Entity to find and delete
    ///
    /// \see ::xrn::ecs::entity::ConstReference
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline void remove(
        const ::xrn::ecs::entity::ConstReference& entityReference
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes all ::xrn::ecs::entity::Entity from the container
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline void clear();



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Get
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets a ::xrn::ecs::entity::ConstReference to an entity contained
    /// it the container
    ///
    /// \param entityId Entity to find and return
    ///
    /// \warning The returned ::xrn::ecs::entity::Reference may be invalid.
    ///          The user must call ::xrn::ecs::entity::Reference::isValid()
    ///          if he isn't certain that the entity is present in the
    ///          container to check its validity.
    /// \warning This reference may be invalidated when an entity is created.
    ///
    /// \see ::xrn::util::BasicForwardId, ::xrn::ecs::entity::ConstReference
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] inline auto operator[](
        ::xrn::Id entityId
    ) const
        -> ::xrn::ecs::entity::ConstReference;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets a mutable ::xrn::ecs::entity::Reference to an entity
    /// contained it the container
    ///
    /// \param entityId Entity to find and return
    ///
    /// \warning The returned ::xrn::ecs::entity::Reference may be invalid.
    ///          The user must call ::xrn::ecs::entity::Reference::isValid()
    ///          if he isn't certain that the entity is present in the
    ///          container to check its validity.
    /// \warning This reference may be invalidated when an entity is created.
    ///
    /// \see ::xrn::util::BasicForwardId, ::xrn::ecs::entity::Reference
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] inline auto operator[](
        ::xrn::Id entityId
    ) -> ::xrn::ecs::entity::Reference;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets a ::xrn::ecs::entity::ConstReference to an entity contained
    /// it the container
    ///
    /// \param entityId Entity to find and return
    ///
    /// \warning The returned ::xrn::ecs::entity::Reference may be invalid.
    ///          The user must call ::xrn::ecs::entity::Reference::isValid()
    ///          if he isn't certain that the entity is present in the
    ///          container to check its validity.
    /// \warning This reference may be invalidated when an entity is created.
    ///
    /// \see ::xrn::util::BasicForwardId, ::xrn::ecs::entity::ConstReference
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] inline auto get(
        ::xrn::Id entityId
    ) const
        -> ::xrn::ecs::entity::ConstReference;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets a mutable ::xrn::ecs::entity::Reference to an entity
    /// contained it the container
    ///
    /// \param entityId Entity to find and return
    ///
    /// \warning The returned ::xrn::ecs::entity::Reference may be invalid.
    ///          The user must call ::xrn::ecs::entity::Reference::isValid()
    ///          if he isn't certain that the entity is present in the
    ///          container to check its validity.
    /// \warning This reference may be invalidated when an entity is created.
    ///
    /// \see ::xrn::util::BasicForwardId, ::xrn::ecs::entity::Reference
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] inline auto get(
        ::xrn::Id entityId
    ) -> ::xrn::ecs::entity::Reference;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets a ::xrn::ecs::entity::ConstReference to an entity contained
    /// it the container
    ///
    /// \warning Calling this function while the entity is not present in the
    ///          container leads to undefined behaviors.
    /// \warning This reference may be invalidated when an entity is created.
    ///
    /// \param entityId Entity to find and return
    ///
    /// \see ::xrn::util::BasicForwardId, ::xrn::ecs::entity::ConstReference
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] inline auto unsafeGet(
        ::xrn::Id entityId
    ) const
        -> ::xrn::ecs::entity::ConstReference;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets a mutable ::xrn::ecs::entity::Reference to an entity
    /// contained it the container
    ///
    /// \warning Calling this function while the entity is not present in the
    ///          container leads to undefined behaviors.
    /// \warning This reference may be invalidated when an entity is created.
    ///
    /// \param entityId Entity to find and return
    ///
    /// \see ::xrn::util::BasicForwardId, ::xrn::ecs::entity::Reference
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] inline auto unsafeGet(
        ::xrn::Id entityId
    ) -> ::xrn::ecs::entity::Reference;



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
    /// \param entityId Entity to find
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
        ::xrn::Id entityId
    ) const
        -> const ::std::remove_cvref_t<::std::remove_pointer_t<ComponentType>>*;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the entity component
    ///
    /// \warning The component pointer might be invalidated if an action other
    ///          than accessing is performed on the component container.
    ///
    /// \tparam ComponentType Component to search in the container and return
    ///         if existing
    ///
    /// \param entity Reference to the Entity
    ///
    /// \return Pointer to the component, or nullptr if the component does not
    ///         exist.
    ///
    /// \see ::xrn::ecs::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto getComponent(
        const ::xrn::ecs::Entity& entity
    ) const
        -> const ::std::remove_cvref_t<::std::remove_pointer_t<ComponentType>>*;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the entity component
    ///
    /// \warning The component pointer might be invalidated if an action other
    ///          than accessing is performed on the component container.
    ///
    /// \tparam ComponentType Component to search in the container and return
    ///         if existing
    ///
    /// \param entityReference Reference to the Entity
    ///
    /// \return Pointer to the component, or nullptr if the component does not
    ///         exist.
    ///
    /// \see ::xrn::ecs::entity::Reference
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto getComponent(
        const ::xrn::ecs::entity::Reference& entityReference
    ) const
        -> const ::std::remove_cvref_t<::std::remove_pointer_t<ComponentType>>*;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the entity component
    ///
    /// \warning The component pointer might be invalidated if an action other
    ///          than accessing is performed on the component container.
    ///
    /// \tparam ComponentType Component to search in the container and return
    ///         if existing
    ///
    /// \param entityReference Reference to the Entity
    ///
    /// \return Pointer to the component, or nullptr if the component does not
    ///         exist.
    ///
    /// \see ::xrn::ecs::entity::Reference
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto getComponent(
        const ::xrn::ecs::entity::ConstReference& entityReference
    ) const
        -> const ::std::remove_cvref_t<::std::remove_pointer_t<ComponentType>>*;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the mutable entity component
    ///
    /// \warning The component pointer might be invalidated if an action other
    ///          than accessing is performed on the component container.
    ///
    /// \tparam ComponentType Component to search in the container and return
    ///         if existing
    ///
    /// \param entityId Entity to find
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
        ::xrn::Id entityId
    ) -> ::std::remove_cvref_t<::std::remove_pointer_t<ComponentType>>*;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the mutable entity component
    ///
    /// \warning The component pointer might be invalidated if an action other
    ///          than accessing is performed on the component container.
    ///
    /// \tparam ComponentType Component to search in the container and return
    ///         if existing
    ///
    /// \param entity Reference to the Entity
    ///
    /// \return Pointer to the component, or nullptr if the component does not
    ///         exist.
    ///
    /// \see ::xrn::ecs::Entity
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto getComponent(
        const ::xrn::ecs::Entity& entity
    ) -> ::std::remove_cvref_t<::std::remove_pointer_t<ComponentType>>*;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the mutable entity component
    ///
    /// \warning The component pointer might be invalidated if an action other
    ///          than accessing is performed on the component container.
    ///
    /// \tparam ComponentType Component to search in the container and return
    ///         if existing
    ///
    /// \param entityReference Reference to the Entity
    ///
    /// \return Pointer to the component, or nullptr if the component does not
    ///         exist.
    ///
    /// \see ::xrn::ecs::entity::Reference
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto getComponent(
        const ::xrn::ecs::entity::Reference& entityReference
    ) -> ::std::remove_cvref_t<::std::remove_pointer_t<ComponentType>>*;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the mutable entity component
    ///
    /// \warning The component pointer might be invalidated if an action other
    ///          than accessing is performed on the component container.
    ///
    /// \tparam ComponentType Component to search in the container and return
    ///         if existing
    ///
    /// \param entityReference Reference to the Entity
    ///
    /// \return Pointer to the component, or nullptr if the component does not
    ///         exist.
    ///
    /// \see ::xrn::ecs::entity::ConstReference
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto getComponent(
        const ::xrn::ecs::entity::ConstReference& entityReference
    ) -> ::std::remove_cvref_t<::std::remove_pointer_t<ComponentType>>*;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Contains
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether the entityId given as parameter is contained by
    /// the container
    ///
    /// \param entityId Entity to find
    ///
    /// \return True if the entity is contained. False otherwise
    ///
    /// \see ::xrn::util::BasicForwardId, ::xrn::ecs::entity::Reference
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] inline auto contains(
        ::xrn::Id entityId
    ) const
        -> bool;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Iterators support
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets an iterator to the begining of the vector of entities
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] inline auto begin()
        -> Container::Type::iterator;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets an iterator to the begining of the vector of entities
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] inline auto begin() const
        -> Container::Type::const_iterator;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets an iterator to the begining of the vector of entities
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] inline auto cbegin() const
        -> Container::Type::const_iterator;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets an iterator to the end of the vector of entities
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] inline auto end()
        -> Container::Type::iterator;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets an iterator to the end of the vector of entities
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] inline auto end() const
        -> Container::Type::const_iterator;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets an iterator to the end of the vector of entities
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] inline auto cend() const
        -> Container::Type::const_iterator;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Component Container
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the linked component container
    ///
    /// \see ::xrn::ecs::component::Container
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] inline auto getComponentContainer()
        -> ::xrn::ecs::component::Container&;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the linked component container
    ///
    /// \see ::xrn::ecs::component::Container
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] inline auto getComponentContainer() const
        -> const ::xrn::ecs::component::Container&;



private:

    Container::Type m_entities{};

    ///////////////////////////////////////////////////////////////////////////
    // Container where components will be emplaced
    ///////////////////////////////////////////////////////////////////////////
    ::xrn::ecs::component::Container& m_components;

};

} // namespace xrn::ecs::entity



///////////////////////////////////////////////////////////////////////////
// Header-implimentation
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs/Entity/Container.impl.hpp>
