#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::xrn::ecs::component::detail::MemoryManager::MemoryManager(
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
::xrn::ecs::component::detail::MemoryManager::~MemoryManager()
{
    this->clear();
}

///////////////////////////////////////////////////////////////////////////
::xrn::ecs::component::detail::MemoryManager::MemoryManager(
    ::xrn::ecs::component::detail::MemoryManager&& that
) noexcept = default;

///////////////////////////////////////////////////////////////////////////
auto ::xrn::ecs::component::detail::MemoryManager::operator=(
    ::xrn::ecs::component::detail::MemoryManager&& that
) noexcept
    -> ::xrn::ecs::component::detail::MemoryManager&
{
    this->swap(::std::move(that));
    return *this;
}

///////////////////////////////////////////////////////////////////////////
void ::xrn::ecs::component::detail::MemoryManager::swap(
    ::xrn::ecs::component::detail::MemoryManager&& that
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
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> auto ::xrn::ecs::component::detail::MemoryManager::alloc(
    const MemoryManager::EntityId entityId
) -> void*
{
    // search to recycle
    if (
        auto it{ ::std::ranges::find_if(
            m_deletedTable, [](const auto& index){ return ComponentType::getId() == index.id; }
        ) };
        it != m_deletedTable.end()
    ) {
        auto it2{ ::std::ranges::find_if(
            m_indexTable,
            [it](const auto& index){
                return index.addr == it->addr;
            }
        ) };
        it2->ownerId = entityId;
        return it->addr;
    }

    // TODO: search to replace a missplaced component

    // else alloc new space
    m_data.resize(m_data.size() + sizeof(ComponentType));
    auto* addr{ m_data.data() + m_data.size() - sizeof(ComponentType) };
    m_indexTable.emplace(ComponentType::getId(), addr, entityId);
    return addr;
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> void ::xrn::ecs::component::detail::MemoryManager::free(
    const MemoryManager::EntityId entityId
)
{
    // find the component and delete it
    ::std::ranges::find_if(
        m_indexTable | ::std::views::filter([](const auto& index){ return index.ownerId; }),
        [this, entityId](const auto& index){
            if (ComponentType::getId() == index.id && entityId == index.ownerId) {
                index.ownerId = 0;
                m_deletedTable.emplace_back(index);
                static_cast<ComponentType*>(index.addr)->~ComponentType();
                return true;
            }
            return false;
        }
    );
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> void ::xrn::ecs::component::detail::MemoryManager::clear()
{
    auto isCorrectType{ [](const auto& index){
        return index.ownerId && ((ComponentTypes::getId() == index.id) || ...); }
    };
    for (auto& index : m_indexTable | ::std::views::filter(isCorrectType)) {
        ::xrn::ecs::component::ForEach::template find<
            []<::xrn::ecs::detail::constraint::isComponent ComponentType>(auto* addr){
                static_cast<ComponentType*>(addr)->~ComponentType();
            }
        >(index.id, index.addr);
        index.ownerId = 0;
    }
}

///////////////////////////////////////////////////////////////////////////
void ::xrn::ecs::component::detail::MemoryManager::clear()
{
    for (auto& index : m_indexTable | ::std::views::filter([](const auto& index){ return index.ownerId; })) {
        ::xrn::ecs::component::ForEach::template find<
            []<::xrn::ecs::detail::constraint::isComponent ComponentType>(auto* addr){
                static_cast<ComponentType*>(addr)->~ComponentType();
            }
        >(index.id, index.addr);
        index.ownerId = 0;
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> auto ::xrn::ecs::component::detail::MemoryManager::exists(
    const MemoryManager::EntityId entityId
) -> bool
{
    auto it{ ::std::ranges::find_if(
        m_indexTable | ::std::views::filter([](const auto& index){ return index.ownerId; }),
        [entityId](const auto& index){
            return ComponentType::getId() == index.id && entityId == index.ownerId;
        }
    ) };
    return it == m_indexTable.end();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> auto ::xrn::ecs::component::detail::MemoryManager::getAddr(
    const MemoryManager::EntityId entityId
) -> void*
{
    auto it{ ::std::ranges::find_if(
        m_indexTable | ::std::views::filter([](const auto& index){ return index.ownerId; }),
        [entityId](const auto& index){
            return ComponentType::getId() == index.id && entityId == index.ownerId;
        }
    ) };
    return it == m_indexTable.end() ? nullptr : it->addr;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// private static elements
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

::xrn::ecs::component::detail::MemoryManager::OwnedComponentInfo::OwnedComponentInfo(
    ::xrn::ecs::component::detail::MemoryManager::ComponentId thatId,
    ::xrn::ecs::component::detail::MemoryManager::ComponentAddr thatAddr,
    ::xrn::ecs::component::detail::MemoryManager::EntityId thatOwnerId
)
    : ::xrn::ecs::component::detail::MemoryManager::ComponentInfo{ .id = thatId, .addr = thatAddr }
    , ownerId{ thatOwnerId }
{}

auto ::xrn::ecs::component::detail::MemoryManager::OwnedComponentInfo::operator<=>(
    const ::xrn::ecs::component::detail::MemoryManager::OwnedComponentInfo& other
) const {
    return this->id <=> other.id;
}
