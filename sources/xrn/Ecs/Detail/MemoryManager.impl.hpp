#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::MemoryManager(
    ::std::vector<::std::byte>& data
)
    : m_data{ data }
{}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Rule of 5
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::~MemoryManager() noexcept
{
    this->clearAll();
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::MemoryManager(
    ::xrn::ecs::detail::MemoryManager<ComponentTypes...>&& that
) noexcept = default;

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> auto ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::operator=(
    ::xrn::ecs::detail::MemoryManager<ComponentTypes...>&& that
) noexcept
    -> ::xrn::ecs::detail::MemoryManager<ComponentTypes...>&
{
    this->swap(::std::move(that));
    return *this;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> void ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::swap(
    ::xrn::ecs::detail::MemoryManager<ComponentTypes...>&& that
) noexcept
{
    ::std::swap(m_data, that.m_data);
    ::std::swap(m_indexTable, that.m_indexTable);
    ::std::swap(m_deletedTable, that.m_deletedTable);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Basic operations
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...> ComponentType
> auto ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::alloc(
    const MemoryManager::EntityId entity
) -> void*
{
    // search to recycle
    if (
        auto it{ ::std::ranges::find_if(
            m_deletedTable,
            [](const auto& componentInfos){ return ::xrn::meta::ForEach<ComponentTypes...>::template getPosition<ComponentType>() == componentInfos.id; }
        ) };
        it != m_deletedTable.end()
    ) {
        auto it2{ ::std::ranges::find_if(
            m_indexTable,
            [it](const auto& componentInfos){ return componentInfos.index == it->index; }
        ) };
        it2->ownerId = entity;
        return &m_data[it->index];
    }

    // TODO: search to replace a missplaced component

    // else alloc new space
    const auto oldSize{ m_data.size() };
    m_data.resize(oldSize + sizeof(ComponentType));
    m_indexTable.emplace(::xrn::meta::ForEach<ComponentTypes...>::template getPosition<ComponentType>(), oldSize, entity);
    return m_data.data() + oldSize;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...> ComponentType
> void ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::free(
    const MemoryManager::EntityId entity
)
{
    // search in non-deleted components and delete it if present
    auto nonDeletedComponents{ [](const auto& componentInfos){ return componentInfos.ownerId; } };
    ::std::ranges::find_if(
        m_indexTable | ::std::views::filter(nonDeletedComponents),
        [this, entity](const auto& componentInfos){
            if (::xrn::meta::ForEach<ComponentTypes...>::template getPosition<ComponentType>() == componentInfos.id && entity == componentInfos.ownerId) {
                componentInfos.ownerId = 0;
                m_deletedTable.emplace_back(componentInfos);
                ::std::bit_cast<ComponentType*>(&m_data[componentInfos.index])->~ComponentType();
                return true;
            }
            return false;
        }
    );
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...> ComponentType
> void ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::clear()
{
    auto nonDeletedComponents{ [](const auto& componentInfos){ return componentInfos.ownerId; } };
    for (auto& componentInfos : m_indexTable | ::std::views::filter(nonDeletedComponents)) {
        ::xrn::meta::ForEach<ComponentTypes...>::template runForTypes<
            []<::xrn::meta::constraint::contains<ComponentTypes...> MatchingType>(auto* addr) {
                ::std::bit_cast<MatchingType*>(addr)->~MatchingType();
            },
            ComponentType // type to search
        >(&m_data[componentInfos.index]);
        componentInfos.ownerId = 0;
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> void ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::clearAll()
{
    // auto nonDeletedComponents{ [](const auto& componentInfos){ return componentInfos.ownerId; } };
    // for (auto& componentInfos : m_indexTable | ::std::views::filter(nonDeletedComponents)) {
        // ::xrn::ecs::detail::ForEach<ComponentTypes...>::template findId<
            // []<::xrn::meta::constraint::contains<ComponentTypes...> MatchingType>(auto* addr){
                // ::std::bit_cast<MatchingType*>(addr)->~MatchingType();
            // }
        // >(componentInfos.ownerId, &m_data[componentInfos.index]);
        // componentInfos.ownerId = 0;
    // }
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...> ComponentType
> auto ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::contains(
    const MemoryManager::EntityId entity
) const
    -> bool
{
    auto it{ ::std::ranges::find_if(
        m_indexTable,
        [entity](const auto& componentInfos){
            return componentInfos.ownerId &&
                ::xrn::meta::ForEach<ComponentTypes...>::template getPosition<ComponentType>() == componentInfos.id &&
                entity == componentInfos.ownerId;
        }
    ) };
    return it != m_indexTable.end();
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...> ComponentType
> auto ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::getAddr(
    const MemoryManager::EntityId entity
) -> void*
{
    auto it{ ::std::ranges::find_if(
        m_indexTable,
        [entity](const auto& componentInfos){
            return componentInfos.ownerId &&
                ::xrn::meta::ForEach<ComponentTypes...>::template getPosition<ComponentType>() == componentInfos.id &&
                entity == componentInfos.ownerId;
        }
    ) };
    return it != m_indexTable.end() ? &m_data[it->index] : nullptr;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...> ComponentType
> auto ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::getAddr(
    const MemoryManager::EntityId entity
) const
    -> const void*
{
    auto it{ ::std::ranges::find_if(
        m_indexTable,
        [entity](const auto& componentInfos){
            return componentInfos.ownerId &&
                ::xrn::meta::ForEach<ComponentTypes...>::template getPosition<ComponentType>() == componentInfos.id &&
                entity == componentInfos.ownerId;
        }
    ) };
    return it != m_indexTable.end() ? &m_data[it->index] : nullptr;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// private static elements
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::OwnedComponentInfo::OwnedComponentInfo(
    ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::ComponentId thatId,
    ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::ComponentIndex thatIndex,
    ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::EntityId thatOwnerId
)
    : ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::ComponentInfo{ .id = thatId, .index = thatIndex }
    , ownerId{ thatOwnerId }
{}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> auto ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::OwnedComponentInfo::operator<=>(
    const ::xrn::ecs::detail::MemoryManager<ComponentTypes...>::OwnedComponentInfo& other
) const
    -> ::std::strong_ordering
{
    return this->id <=> other.id;
}
