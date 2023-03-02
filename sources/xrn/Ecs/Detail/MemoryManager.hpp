#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs/Detail/ForEach.hpp>



namespace xrn::ecs::detail {

///////////////////////////////////////////////////////////////////////////
/// \internal
/// \brief Manages the memory of the ::xrn::ecs::component::Container
/// \ingroup ecs-component
///
/// \include MemoryManager.hpp <xrn/Ecs/Component/Detail/MemoryManager.hpp>
///
/// Manages the memory of the ::xrn::ecs::component::Container. This is
/// the class that does memory optimization.
/// This class being an implementation detail, users are not supposed to
/// look at it.
///
/// Usage example:
/// \code
/// using ComponentType = ::xrn::ecs::component::test::ComponentA
/// ::xrn::ecs::Entity entity;
/// ::std::vector<::std::byte> data{ 1024 };
/// ::xrn::ecs::detail::MemoryManager memoryManager{ data }
/// auto component{ *new(memoryManager.alloc<ComponentType>(entity.getId())) ComponentType{} };
/// memoryManager.getAddr<COmponentType>(enity.getId());
/// memoryManager.free<COmponentType>(enity.getId());
/// \endcode
///
/// \see ::xrn::ecs::component::Container
///
///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> class MemoryManager {

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
    using ComponentIndex = ::std::size_t;
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
    /// \param data Reference to the memory that the memory MemoryManager
    ///        handles
    ///
    /// \see ::xrn::ecs::component::Container
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline explicit MemoryManager(
        ::std::vector<::std::byte>& data
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
    /// Does NOT clears any component.
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline ~MemoryManager() noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    MemoryManager(
        const ::xrn::ecs::detail::MemoryManager<ComponentTypes...>& other
    ) noexcept = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        const ::xrn::ecs::detail::MemoryManager<ComponentTypes...>& other
    ) noexcept
        -> ::xrn::ecs::detail::MemoryManager<ComponentTypes...>& = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline MemoryManager(
        ::xrn::ecs::detail::MemoryManager<ComponentTypes...>&& that
    ) noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline auto operator=(
        ::xrn::ecs::detail::MemoryManager<ComponentTypes...>&& that
    ) noexcept
        -> ::xrn::ecs::detail::MemoryManager<ComponentTypes...>&;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Swaps the containers
    ///
    /// Required for the assignement operator.
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline void swap(
        ::xrn::ecs::detail::MemoryManager<ComponentTypes...>&& that
    ) noexcept;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Basic operations
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Allocates the memory for the component
    ///
    /// Allocates the memory for the component given as template parameter and
    /// internally link it to the entity Id given as parameter.
    ///
    /// \tparam ComponentType Type of the component to allocate
    ///
    /// \param entityId Id of the entity that will be linked to the component
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent,
    ///      ::xrn::ecs::entity::Entity, ::xrn::util::BasicForwardId
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...> ComponentType
    > [[ nodiscard ]] auto alloc(
        MemoryManager::EntityId entityId
    ) -> void*;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Deallocates the memory for the component
    ///
    /// Deallocates the memory for the component given as template parameter
    /// and internally unlink it from the entity Id given as parameter.
    /// Implementation detail: the deallocation is not required, some
    /// optimizations like for the component recycle can be done. However, the
    /// unlink is requiered.
    ///
    /// \tparam ComponentType Type of the component to deallocate
    ///
    /// \param entityId Id of the entity that will be unlinked from the
    ///        component
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent,
    ///      ::xrn::ecs::entity::Entity, ::xrn::util::BasicForwardId
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...> ComponentType
    > void free(
        MemoryManager::EntityId entityId
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Deallocates the memory of all the components given
    ///
    /// Deallocates the memory of all the components of type given as template
    /// parameter and internally unlink them from all the entities related.
    /// Implementation detail: the deallocation is not required, some
    /// optimizations like for the component recycle can be done. However, the
    /// unlink is requiered.
    ///
    /// \tparam ComponentType Type of the components to deallocate
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent,
    ///      ::xrn::ecs::entity::Entity, ::xrn::util::BasicForwardId
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...> ComponentType
    > void clear();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Deallocates the memory of all the components
    ///
    /// Deallocates the memory of all the components and internally unlink them
    /// from all the entities related.
    /// Implementation detail: the deallocation is not required, some
    /// optimizations like for the component recycle can be done. However, the
    /// unlink is requiered.
    ///
    /// \tparam ComponentType Type of the components to deallocate
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent,
    ///      ::xrn::ecs::entity::Entity, ::xrn::util::BasicForwardId
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline void clearAll();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether the component is linked to the entity
    ///
    /// Checks whether the component given as template parameter is linked to
    /// the entity Id given as parameter.
    ///
    /// \return True if the component is linked to the entity, false otherwise
    ///
    /// \tparam ComponentType Type of the component to check
    ///
    /// \param entityId Id of the entity to check
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent,
    ///      ::xrn::ecs::entity::Entity, ::xrn::util::BasicForwardId
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...> ComponentType
    > [[ nodiscard ]] auto contains(
        MemoryManager::EntityId entityId
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get a pointer to the component of the entity
    ///
    /// Get a pointer to the component given as template parameter linked to
    /// the entity Id given as parameter if it exists.
    ///
    /// \return Pointer to the entity component, nullptr if the said component
    ///         does not exist
    ///
    /// \tparam ComponentType Type of the component to check
    ///
    /// \param entityId Id of the entity to check
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent,
    ///      ::xrn::ecs::entity::Entity, ::xrn::util::BasicForwardId
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...> ComponentType
    > [[ nodiscard ]] auto getAddr(
        MemoryManager::EntityId entityId
    ) -> void*;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get a pointer to the component of the entity
    ///
    /// Get a pointer to the component given as template parameter linked to
    /// the entity Id given as parameter if it exists.
    ///
    /// \return Pointer to the entity component, nullptr if the said component
    ///         does not exist
    ///
    /// \tparam ComponentType Type of the component to check
    ///
    /// \param entityId Id of the entity to check
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent,
    ///      ::xrn::ecs::entity::Entity, ::xrn::util::BasicForwardId
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...> ComponentType
    > [[ nodiscard ]] auto getAddr(
        MemoryManager::EntityId entityId
    ) const
        -> const void*;



private:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // private static elements
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \internal
    /// \brief Tracks the requiered informations of a component
    ///
    /// This struct is used when a component is not linked to an entity. It
    /// allows component recycling.
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    struct ComponentInfo {
        ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::ComponentId id;
        ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::ComponentIndex index;
    };

    ///////////////////////////////////////////////////////////////////////////
    /// \internal
    /// \brief Tracks the requiered informations of a component
    ///
    /// This struct is used when a component is linked to an entity.
    ///
    /// \see ::xrn::ecs::component::declaration::detail::AComponent,
    ///      ::xrn::ecs::entity::Entity, ::xrn::util::BasicForwardId
    ///
    ///////////////////////////////////////////////////////////////////////////
    struct OwnedComponentInfo : ComponentInfo {

        ///////////////////////////////////////////////////////////////////////////
        /// \brief Constructor
        ///
        ///////////////////////////////////////////////////////////////////////////
        inline explicit OwnedComponentInfo(
            ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::ComponentId id,
            ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::ComponentIndex index,
            ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::EntityId ownerId
        );

        ///////////////////////////////////////////////////////////////////////////
        /// \brief Comparator
        ///
        /// compares only component id
        ///
        ///////////////////////////////////////////////////////////////////////////
        [[ nodiscard ]] inline auto operator<=>(
            const ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::OwnedComponentInfo& other
        ) const
            -> ::std::strong_ordering;

        ///////////////////////////////////////////////////////////////////////////
        // Data
        ///////////////////////////////////////////////////////////////////////////
        using ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::ComponentInfo::id;
        using ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::ComponentInfo::index;
        mutable ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::EntityId ownerId;
    };



private:

    ::std::vector<::std::byte>& m_data;
    ::std::multiset<OwnedComponentInfo> m_indexTable{};
    ::std::vector<ComponentInfo> m_deletedTable{};

};

} // namespace xrn::ecs::detail



///////////////////////////////////////////////////////////////////////////
// Header-implimentation
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs/Detail/MemoryManager.impl.hpp>
