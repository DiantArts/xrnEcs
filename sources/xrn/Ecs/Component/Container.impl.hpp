#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs/Entity/Entity.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::xrn::ecs::component::Container::Container()
    : m_memoryManager{ m_data }
    , m_data{}
{
    m_data.reserve(Container::defaultBaseSize);
}

///////////////////////////////////////////////////////////////////////////
::xrn::ecs::component::Container::Container(
    ::std::size_t size
)
    : m_memoryManager{ m_data }
    , m_data{}
{
    m_data.reserve(size);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Rule of 5
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::xrn::ecs::component::Container::~Container()
{
    this->clearAll();
}

///////////////////////////////////////////////////////////////////////////
::xrn::ecs::component::Container::Container(
    ::xrn::ecs::component::Container&& that
) noexcept = default;

///////////////////////////////////////////////////////////////////////////
auto ::xrn::ecs::component::Container::operator=(
    ::xrn::ecs::component::Container&& that
) noexcept
    -> ::xrn::ecs::component::Container& = default;



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Emplace
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent RawComponentType
> auto ::xrn::ecs::component::Container::emplace(
    ::xrn::ecs::entity::Entity& entity,
    auto&&... args
) noexcept -> ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>&
{
    return this->emplace<RawComponentType>(entity.getId(), ::std::forward<decltype(args)>(args)...);
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent RawComponentType
> auto ::xrn::ecs::component::Container::emplace(
    const Container::EntityId entityId,
    auto&&... args
) noexcept -> ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>&
{
    using ComponentType = ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>;
    return *new(m_memoryManager.alloc<ComponentType>(entityId)) ComponentType{
        ::std::forward<decltype(args)>(args)...
    };
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> void ::xrn::ecs::component::Container::emplaceMany(
    ::xrn::ecs::entity::Entity& entity
) noexcept
{
    static_assert(sizeof...(ComponentTypes), "Emplace many called with 0 arguments");
    (this->emplace<ComponentTypes>(entity.getId()), ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> void ::xrn::ecs::component::Container::emplaceMany(
    const Container::EntityId entityId
) noexcept
{
    static_assert(sizeof...(ComponentTypes), "Emplace many called with 0 arguments");
    (this->emplace<ComponentTypes>(entityId), ...);
}

///////////////////////////////////////////////////////////////////////////
void ::xrn::ecs::component::Container::push(
    ::xrn::ecs::entity::Entity& entity,
    ::xrn::ecs::detail::constraint::isComponent auto&& component
) noexcept
{
    return this->push(entity.getId(), ::std::forward<decltype(component)>(component));
}

///////////////////////////////////////////////////////////////////////////
void ::xrn::ecs::component::Container::push(
    const Container::EntityId entityId,
    ::xrn::ecs::detail::constraint::isComponent auto&& component
) noexcept
{
    using ComponentType = ::std::remove_cvref_t<::std::remove_pointer_t<decltype(component)>>;
    new(m_memoryManager.alloc<ComponentType>(entityId)) ComponentType{ ::std::move(component) };
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> void ::xrn::ecs::component::Container::pushMany(
    ::xrn::ecs::entity::Entity& entity,
    ComponentTypes&&... components
) noexcept
{
    static_assert(sizeof...(ComponentTypes), "Push many called with 0 arguments");
    (this->push(entity.getId(), components), ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> void ::xrn::ecs::component::Container::pushMany(
    const Container::EntityId entityId,
    ComponentTypes&&... components
) noexcept
{
    static_assert(sizeof...(ComponentTypes), "Push many called with 0 arguments");
    (this->push(entityId, components), ...);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Remove
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent RawComponentType
> void ::xrn::ecs::component::Container::remove(
    ::xrn::ecs::entity::Entity& entity
)
{
    this->remove<RawComponentType>(entity.getId());
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent RawComponentType
> void ::xrn::ecs::component::Container::remove(
    const Container::EntityId entityId
)
{
    using ComponentType = ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>;
    m_memoryManager.free<ComponentType>(entityId);
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> void ::xrn::ecs::component::Container::removeMany(
    ::xrn::ecs::entity::Entity& entity
)
{
    static_assert(sizeof...(ComponentTypes), "Remove many called with 0 arguments");
    (this->remove<ComponentTypes>(entity.getId()), ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> void ::xrn::ecs::component::Container::removeMany(
    const Container::EntityId entityId
)
{
    static_assert(sizeof...(ComponentTypes), "Remove many called with 0 arguments");
    (this->remove<ComponentTypes>(entityId), ...);
}

///////////////////////////////////////////////////////////////////////////
void ::xrn::ecs::component::Container::removeAll(
    ::xrn::ecs::entity::Entity& entity
)
{
    ::xrn::ecs::component::detail::ForEach::template runIfSignature<
        []<::xrn::ecs::detail::constraint::isComponent ComponentType>(auto& components, auto& entity){
            components.template remove<ComponentType>(entity);
        }
    >(entity.getSignature(), *this, entity);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Clear
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent RawComponentType
> void ::xrn::ecs::component::Container::clear()
{
    using ComponentType = ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>;
    m_memoryManager.clear<ComponentType>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> void ::xrn::ecs::component::Container::clearMany()
{
    static_assert(sizeof...(ComponentTypes), "Clear many called with 0 arguments");
    this->clear<ComponentTypes...>();
}

///////////////////////////////////////////////////////////////////////////
void ::xrn::ecs::component::Container::clear()
{
    this->clearAll();
}

///////////////////////////////////////////////////////////////////////////
void ::xrn::ecs::component::Container::clearAll()
{
    m_memoryManager.clearAll();
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Accessors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> auto ::xrn::ecs::component::Container::get(
    ::xrn::ecs::entity::Entity& entity
) -> ::std::remove_cvref_t<::std::remove_pointer_t<ComponentType>>*
{
    return this->get<ComponentType>(entity.getId());
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent RawComponentType
> auto ::xrn::ecs::component::Container::get(
    const Container::EntityId entityId
) -> ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>*
{
    using ComponentType = ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>;
    return static_cast<ComponentType*>(m_memoryManager.getAddr<ComponentType>(entityId));
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> auto ::xrn::ecs::component::Container::get(
    ::xrn::ecs::entity::Entity& entity
) const
    -> const ::std::remove_cvref_t<::std::remove_pointer_t<ComponentType>>*
{
    return this->get<ComponentType>(entity.getId());
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent RawComponentType
> auto ::xrn::ecs::component::Container::get(
    const Container::EntityId entityId
) const
    -> const ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>*
{
    using ComponentType = ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>;
    return static_cast<const ComponentType*>(m_memoryManager.getAddr<ComponentType>(entityId));
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> auto ::xrn::ecs::component::Container::contains(
    ::xrn::ecs::entity::Entity& entity
) const
    -> bool
{
    return this->contains<ComponentType>(entity.getId());
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent RawComponentType
> auto ::xrn::ecs::component::Container::contains(
    const Container::EntityId entityId
) const
    -> bool
{
    using ComponentType = ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>;
    return m_memoryManager.contains<ComponentType>(entityId);
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> auto ::xrn::ecs::component::Container::containsMany(
    ::xrn::ecs::entity::Entity& entity
) const
    -> bool
{
    static_assert(sizeof...(ComponentTypes), "Contains many called with 0 arguments");
    return (this->contains<ComponentTypes>(entity.getId()) && ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> auto ::xrn::ecs::component::Container::containsMany(
    const Container::EntityId entityId
) const
    -> bool
{
    static_assert(sizeof...(ComponentTypes), "Contains many called with 0 arguments");
    return (this->contains<ComponentTypes>(entityId) && ...);
}
