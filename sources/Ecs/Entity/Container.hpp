#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Ecs/Component/Container.hpp>
#include <Ecs/Entity/Entity.hpp>
#include <Ecs/Entity/Reference.hpp>



namespace xrn::ecs::entity {

///////////////////////////////////////////////////////////////////////////
/// \brief Contains all the entities
/// \ingroup ecs-entity
///
/// \include Container.hpp <Ecs/Entity/Container.hpp>
///
/// Contains all ::xrn::ecs::Entity needed for the ECS architecture. All the
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
/// \see ::xrn::ecs::Entity
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
    /// Constructs an ::xrn::ecs::entity::Container.
    ///
    /// \param amount Time in milliseconds
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    explicit Container(
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
    ~Container();

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
    /// \warning The returned ::xrn::ecs::Entity::Reference may be invalid.
    ///          The user must call ::xrn::ecs::Entity::Reference::isValid()
    ///          if he isn't certain that the entity is present in the
    ///          container to check its validity.
    /// \warning This reference may be invalidated when an entity is created.
    ///
    /// \tparam ComponentTypes Type of components to emplace inside the
    /// ::xrn::ecs::Entity when creating it
    ///
    /// \param amount Time in milliseconds
    ///
    /// \returns An ::xrn::ecs::Entity::Reference to the entity emplaced
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > auto emplace()
        -> ::xrn::ecs::Entity::Reference;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Emplaces an entity
    ///
    /// Creates an entity from the component given as template parameter.
    ///
    /// \warning The returned ::xrn::ecs::Entity::Reference may be invalid.
    ///          The user must call ::xrn::ecs::Entity::Reference::isValid()
    ///          if he isn't certain that the entity is present in the
    ///          container to check its validity.
    /// \warning This reference may be invalidated when an entity is created.
    ///
    /// \param components Components to emplace inside the entity created
    ///
    /// \returns An ::xrn::ecs::Entity::Reference to the entity emplaced
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto emplace(
        ::xrn::ecs::detail::constraint::isComponent auto&&... components
    ) -> ::xrn::ecs::Entity::Reference;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Remove
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes an ::xrn::ecs::Entity from the container
    ///
    /// Remove the entity that matches the ::xrn::Id given as parameter.
    ///
    /// \param entityId Id to find and delete
    ///
    /// \see ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    void remove(
        ::xrn::Id entityId
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes an ::xrn::ecs::Entity from the container
    ///
    /// Remove the entity referenced by the ::xrn::ecs::Entity::Reference.
    ///
    /// \param entityReference Entity to find and delete
    ///
    /// \see ::xrn::ecs::Entity::Reference
    ///
    ///////////////////////////////////////////////////////////////////////////
    void remove(
        const ::xrn::ecs::Entity::Reference& entityReference
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes an ::xrn::ecs::Entity from the container
    ///
    /// Remove the entity referenced by the ::xrn::ecs::Entity::ConstReference.
    ///
    /// \param entityReference Entity to find and delete
    ///
    /// \see ::xrn::ecs::Entity::ConstReference
    ///
    ///////////////////////////////////////////////////////////////////////////
    void remove(
        const ::xrn::ecs::Entity::ConstReference& entityReference
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes all ::xrn::ecs::Entity from the container
    ///
    ///////////////////////////////////////////////////////////////////////////
    void clear();



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Get
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets a ::xrn::ecs::Entity::ConstReference to an entity contained
    /// it the container
    ///
    /// \param entityId Entity to find and return
    ///
    /// \warning The returned ::xrn::ecs::Entity::Reference may be invalid.
    ///          The user must call ::xrn::ecs::Entity::Reference::isValid()
    ///          if he isn't certain that the entity is present in the
    ///          container to check its validity.
    /// \warning This reference may be invalidated when an entity is created.
    ///
    /// \see ::xrn::Id, ::xrn::ecs::Entity::ConstReference
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto operator[](
        ::xrn::Id entityId
    ) const
        -> ::xrn::ecs::Entity::ConstReference;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets a mutable ::xrn::ecs::Entity::Reference to an entity
    /// contained it the container
    ///
    /// \param entityId Entity to find and return
    ///
    /// \warning The returned ::xrn::ecs::Entity::Reference may be invalid.
    ///          The user must call ::xrn::ecs::Entity::Reference::isValid()
    ///          if he isn't certain that the entity is present in the
    ///          container to check its validity.
    /// \warning This reference may be invalidated when an entity is created.
    ///
    /// \see ::xrn::Id, ::xrn::ecs::Entity::Reference
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto operator[](
        ::xrn::Id entityId
    ) -> ::xrn::ecs::Entity::Reference;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets a ::xrn::ecs::Entity::ConstReference to an entity contained
    /// it the container
    ///
    /// \param entityId Entity to find and return
    ///
    /// \warning The returned ::xrn::ecs::Entity::Reference may be invalid.
    ///          The user must call ::xrn::ecs::Entity::Reference::isValid()
    ///          if he isn't certain that the entity is present in the
    ///          container to check its validity.
    /// \warning This reference may be invalidated when an entity is created.
    ///
    /// \see ::xrn::Id, ::xrn::ecs::Entity::ConstReference
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto get(
        ::xrn::Id entityId
    ) const
        -> ::xrn::ecs::Entity::ConstReference;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets a mutable ::xrn::ecs::Entity::Reference to an entity
    /// contained it the container
    ///
    /// \param entityId Entity to find and return
    ///
    /// \warning The returned ::xrn::ecs::Entity::Reference may be invalid.
    ///          The user must call ::xrn::ecs::Entity::Reference::isValid()
    ///          if he isn't certain that the entity is present in the
    ///          container to check its validity.
    /// \warning This reference may be invalidated when an entity is created.
    ///
    /// \see ::xrn::Id, ::xrn::ecs::Entity::Reference
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto get(
        ::xrn::Id entityId
    ) -> ::xrn::ecs::Entity::Reference;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets a ::xrn::ecs::Entity::ConstReference to an entity contained
    /// it the container
    ///
    /// \warning Calling this function while the entity is not present in the
    ///          container leads to undefined behaviors.
    /// \warning This reference may be invalidated when an entity is created.
    ///
    /// \param entityId Entity to find and return
    ///
    /// \see ::xrn::Id, ::xrn::ecs::Entity::ConstReference
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto unsafeGet(
        ::xrn::Id entityId
    ) const
        -> ::xrn::ecs::Entity::ConstReference;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets a mutable ::xrn::ecs::Entity::Reference to an entity
    /// contained it the container
    ///
    /// \warning Calling this function while the entity is not present in the
    ///          container leads to undefined behaviors.
    /// \warning This reference may be invalidated when an entity is created.
    ///
    /// \param entityId Entity to find and return
    ///
    /// \see ::xrn::Id, ::xrn::ecs::Entity::Reference
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto unsafeGet(
        ::xrn::Id entityId
    ) -> ::xrn::ecs::Entity::Reference;



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
    /// \see ::xrn::Id, ::xrn::ecs::Entity::Reference
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto contains(
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
    [[ nodiscard ]] auto begin()
        -> Container::Type::iterator;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets an iterator to the begining of the vector of entities
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto begin() const
        -> Container::Type::const_iterator;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets an iterator to the begining of the vector of entities
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto cbegin() const
        -> Container::Type::const_iterator;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets an iterator to the end of the vector of entities
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto end()
        -> Container::Type::iterator;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets an iterator to the end of the vector of entities
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto end() const
        -> Container::Type::const_iterator;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets an iterator to the end of the vector of entities
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto cend() const
        -> Container::Type::const_iterator;



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
#include <Ecs/Entity/Container.impl.hpp>
