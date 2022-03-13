#pragma once

namespace xrn::ecs::component::detail {

///////////////////////////////////////////////////////////////////////////
/// \brief Manages the memory of the ::xrn::ecs::component::Container
/// \ingroup ecs-component
///
/// \include MemoryManager.hpp <Ecs/Component/Detail/MemoryManager.hpp>
///
/// Manages the memory of the ::xrn::ecs::component::MegaArray. This is
/// the class that does memory optimization.
/// This class being an implementation detail, users are not supposed to
/// look at it.
///
/// Usage example:
/// \code
/// TODO code example
/// \endcode
///
/// \see ::xrn::ecs::component::MegaArray
///
///////////////////////////////////////////////////////////////////////////
class MemoryManager {

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
    /// \param data Reference to the memory that the memory MemoryManager
    ///        handles
    ///
    /// \see ::xrn::ecs::component::MegaArray
    ///
    ///////////////////////////////////////////////////////////////////////////
    explicit MemoryManager(
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
    /// Clears every component of every entity.
    ///
    ///////////////////////////////////////////////////////////////////////////
    ~MemoryManager();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    MemoryManager(
        const ::xrn::ecs::component::detail::MemoryManager& other
    ) noexcept = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        const ::xrn::ecs::component::detail::MemoryManager& other
    ) noexcept
        -> ::xrn::ecs::component::detail::MemoryManager& = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    MemoryManager(
        ::xrn::ecs::component::detail::MemoryManager&& that
    ) noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        ::xrn::ecs::component::detail::MemoryManager&& that
    ) noexcept
        -> ::xrn::ecs::component::detail::MemoryManager&;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Swaps the containers
    ///
    /// Required for the assignement operator.
    ///
    ///////////////////////////////////////////////////////////////////////////
    void swap(
        ::xrn::ecs::component::detail::MemoryManager&& that
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
    /// \see ::xrn::ecs::component::AComponent, ::xrn::ecs::Entity, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
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
    /// \see ::xrn::ecs::component::AComponent, ::xrn::ecs::Entity, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > void free(
        MemoryManager::EntityId entityId
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Deallocates the memory of all the components given
    ///
    /// Deallocates the memory of all the components given as template
    /// parameter and internally unlink them from all the entities related.
    /// Implementation detail: the deallocation is not required, some
    /// optimizations like for the component recycle can be done. However, the
    /// unlink is requiered.
    ///
    /// \tparam ComponentTypes Types of the components to deallocate
    ///
    /// \see ::xrn::ecs::component::AComponent, ::xrn::ecs::Entity, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void clear();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Deallocates the memory of all the components
    ///
    /// Deallocates the memory of all the components internally unlink them from
    /// all the entities related.
    /// Implementation detail: the deallocation is not required, some
    /// optimizations like for the component recycle can be done. However, the
    /// unlink is requiered.
    ///
    /// \see ::xrn::ecs::component::AComponent, ::xrn::ecs::Entity, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    void clear();

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
    /// \see ::xrn::ecs::component::AComponent, ::xrn::ecs::Entity, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto exists(
        MemoryManager::EntityId entityId
    ) -> bool;

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
    /// \see ::xrn::ecs::component::AComponent, ::xrn::ecs::Entity, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto getAddr(
        MemoryManager::EntityId entityId
    ) -> void*;



private:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // private static elements
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Tracks the requiered informations of a component
    ///
    /// This struct is used when a component is not linked to an entity. It
    /// allows component recycling.
    ///
    /// \see ::xrn::ecs::component::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    struct ComponentInfo {
        ::xrn::ecs::component::detail::MemoryManager::ComponentId id;
        ::xrn::ecs::component::detail::MemoryManager::ComponentAddr addr;
    };

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Tracks the requiered informations of a component
    ///
    /// This struct is used when a component is linked to an entity.
    ///
    /// \see ::xrn::ecs::component::AComponent, ::xrn::ecs::Entity, ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    struct OwnedComponentInfo : ComponentInfo {

        ///////////////////////////////////////////////////////////////////////////
        /// \brief Constructor
        ///
        ///////////////////////////////////////////////////////////////////////////
        OwnedComponentInfo(
            ::xrn::ecs::component::detail::MemoryManager::ComponentId id,
            ::xrn::ecs::component::detail::MemoryManager::ComponentAddr addr,
            ::xrn::ecs::component::detail::MemoryManager::EntityId ownerId
        );

        ///////////////////////////////////////////////////////////////////////////
        /// \brief Comparator
        ///
        /// compares only component id
        ///
        ///////////////////////////////////////////////////////////////////////////
        [[ nodiscard ]] auto operator<=>(
            const ::xrn::ecs::component::detail::MemoryManager::OwnedComponentInfo& other
        ) const;

        ///////////////////////////////////////////////////////////////////////////
        // Data
        ///////////////////////////////////////////////////////////////////////////
        using ::xrn::ecs::component::detail::MemoryManager::ComponentInfo::id;
        using ::xrn::ecs::component::detail::MemoryManager::ComponentInfo::addr;
        mutable ::xrn::ecs::component::detail::MemoryManager::EntityId ownerId;
    };



private:

    ::std::vector<::std::byte>& m_data;
    ::std::multiset<OwnedComponentInfo> m_indexTable{};
    ::std::vector<ComponentInfo> m_deletedTable{};

};

} // namespace xrn::ecs:nt
