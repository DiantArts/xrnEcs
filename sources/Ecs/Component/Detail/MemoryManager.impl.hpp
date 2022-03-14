#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Basic operations
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> auto ::xrn::ecs::component::detail::MemoryManager::alloc(
    const MemoryManager::EntityId entityId
) -> void*
{
    // search to recycle
    if (
        auto it{ ::std::ranges::find_if(
            m_deletedTable,
            [](const auto& componentInfos){ return ComponentType::getId() == componentInfos.id; }
        ) };
        it != m_deletedTable.end()
    ) {
        auto it2{ ::std::ranges::find_if(
            m_indexTable,
            [it](const auto& componentInfos){ return componentInfos.index == it->index; }
        ) };
        it2->ownerId = entityId;
        return &m_data[it->index];
    }

    // TODO: search to replace a missplaced component

    // else alloc new space
    const auto oldSize{ m_data.size() };
    m_data.resize(oldSize + sizeof(ComponentType));
    m_indexTable.emplace(ComponentType::getId(), oldSize, entityId);
    return m_data.data() + oldSize;
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> void ::xrn::ecs::component::detail::MemoryManager::free(
    const MemoryManager::EntityId entityId
)
{
    // search in non-deleted components and delete it if present
    auto nonDeletedComponents{ [](const auto& componentInfos){ return componentInfos.ownerId; } };
    ::std::ranges::find_if(
        m_indexTable | ::std::views::filter(nonDeletedComponents),
        [this, entityId](const auto& componentInfos){
            if (ComponentType::getId() == componentInfos.id && entityId == componentInfos.ownerId) {
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
    ::xrn::ecs::detail::constraint::isComponent ComponentTypes
> void ::xrn::ecs::component::detail::MemoryManager::clear()
{
    auto nonDeletedComponents{ [](const auto& componentInfos){ return componentInfos.ownerId; } };
    for (auto& componentInfos : m_indexTable | ::std::views::filter(nonDeletedComponents)) {
        ::xrn::ecs::component::ForEach::template find<
            []<::xrn::ecs::detail::constraint::isComponent ComponentType>(auto* addr){
                ::std::bit_cast<ComponentType*>(addr)->~ComponentType();
            }
        >(componentInfos.id, &m_data[componentInfos.index]);
        componentInfos.ownerId = 0;
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> auto ::xrn::ecs::component::detail::MemoryManager::contains(
    const MemoryManager::EntityId entityId
) const
    -> bool
{
    auto it{ ::std::ranges::find_if(
        m_indexTable,
        [entityId](const auto& componentInfos){
            return componentInfos.ownerId &&
                ComponentType::getId() == componentInfos.id &&
                entityId == componentInfos.ownerId;
        }
    ) };
    return it != m_indexTable.end();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> auto ::xrn::ecs::component::detail::MemoryManager::getAddr(
    const MemoryManager::EntityId entityId
) -> void*
{
    auto it{ ::std::ranges::find_if(
        m_indexTable,
        [entityId](const auto& componentInfos){
            return componentInfos.ownerId &&
                ComponentType::getId() == componentInfos.id &&
                entityId == componentInfos.ownerId;
        }
    ) };
    return it != m_indexTable.end() ? &m_data[it->index] : nullptr;
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> auto ::xrn::ecs::component::detail::MemoryManager::getAddr(
    const MemoryManager::EntityId entityId
) const
    -> const void*
{
    auto it{ ::std::ranges::find_if(
        m_indexTable,
        [entityId](const auto& componentInfos){
            return componentInfos.ownerId &&
                ComponentType::getId() == componentInfos.id &&
                entityId == componentInfos.ownerId;
        }
    ) };
    return it != m_indexTable.end() ? &m_data[it->index] : nullptr;
}
