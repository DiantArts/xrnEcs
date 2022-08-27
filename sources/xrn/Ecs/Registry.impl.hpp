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
> ::xrn::ecs::Registry<ComponentTypes...>::Registry()
    : m_data{}
    , m_memoryManager{ m_data }
{
    m_data.reserve(Registry::defaultBaseSize);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> ::xrn::ecs::Registry<ComponentTypes...>::Registry(
    ::std::size_t size
)
    : m_data{}
    , m_memoryManager{ m_data }
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
template <
    typename... ComponentTypes
> ::xrn::ecs::Registry<ComponentTypes...>::~Registry()
{
    this->clearAll();
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> ::xrn::ecs::Registry<ComponentTypes...>::Registry(
    ::xrn::ecs::Registry<ComponentTypes...>&& that
) noexcept = default;

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> auto ::xrn::ecs::Registry<ComponentTypes...>::operator=(
    ::xrn::ecs::Registry<ComponentTypes...>&& that
) noexcept
    -> ::xrn::ecs::Registry<ComponentTypes...>& = default;



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Entity management
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> auto ::xrn::ecs::Registry<ComponentTypes...>::createEntity() noexcept
    -> ::xrn::ecs::Entity
{
    m_signatures.insert(::std::pair{
        ++m_currentEntityIndex,
        ::xrn::ecs::Signature<ComponentTypes...>{}
    });
    return m_currentEntityIndex;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...>... Types
> auto ::xrn::ecs::Registry<ComponentTypes...>::createEntity() noexcept
    -> ::xrn::ecs::Entity
{
    auto entity{ this->createEntity() };
    this->emplace<Types...>();
    return entity;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> auto ::xrn::ecs::Registry<ComponentTypes...>::createEntity(
    ::xrn::meta::constraint::contains<ComponentTypes...> auto&&... components
) noexcept
    -> ::xrn::ecs::Entity
{
    auto entity{ this->createEntity() };
    this->push(::std::forward<decltype(components)>(components)...);
    return entity;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Component management
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...> RawComponentType
> auto ::xrn::ecs::Registry<ComponentTypes...>::emplaceOne(
    ::xrn::ecs::Entity entity,
    auto&&... args
) noexcept -> ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>&
{
    using ComponentType = ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>;
    m_signatures.at(entity).template add<ComponentType>();
    return *new(m_memoryManager.template alloc<ComponentType>(entity)) ComponentType{
        ::std::forward<decltype(args)>(args)...
    };
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...>... Types
> void ::xrn::ecs::Registry<ComponentTypes...>::emplace(
    ::xrn::ecs::Entity entity
) noexcept
{
    static_assert(sizeof...(Types), "Emplace many called with 0 template arguments");
    (this->emplaceOne<Types>(entity), ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...>... Types
> void ::xrn::ecs::Registry<ComponentTypes...>::add(
    ::xrn::ecs::Entity entity
) noexcept
{
    static_assert(sizeof...(Types), "Emplace many called with 0 template arguments");
    (this->emplaceOne<Types>(entity), ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> void ::xrn::ecs::Registry<ComponentTypes...>::pushOne(
    ::xrn::ecs::Entity entity,
    ::xrn::meta::constraint::contains<ComponentTypes...> auto&& component
) noexcept
{
    using ComponentType = ::std::remove_cvref_t<::std::remove_pointer_t<decltype(component)>>;
    m_signatures.at(entity).template add<ComponentType>();
    new(m_memoryManager.template alloc<ComponentType>(entity)) ComponentType{ ::std::move(component) };
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...>... Types
> void ::xrn::ecs::Registry<ComponentTypes...>::push(
    ::xrn::ecs::Entity entity,
    Types&&... components
) noexcept
{
    static_assert(sizeof...(Types), "Push many called with 0 arguments");
    (this->pushOne(entity, ::std::forward<decltype(components)>(components)), ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...>... Types
> void ::xrn::ecs::Registry<ComponentTypes...>::add(
    ::xrn::ecs::Entity entity,
    Types&&... components
) noexcept
{
    static_assert(sizeof...(Types), "Push many called with 0 arguments");
    (this->pushOne(entity, ::std::forward<decltype(components)>(components)), ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...> RawComponentType
> void ::xrn::ecs::Registry<ComponentTypes...>::removeOne(
    ::xrn::ecs::Entity entity
)
{
    using ComponentType = ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>;
    m_memoryManager.template free<ComponentType>(entity);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...>... Types
> void ::xrn::ecs::Registry<ComponentTypes...>::remove(
    ::xrn::ecs::Entity entity
)
{
    static_assert(sizeof...(Types), "Remove many called with 0 template arguments");
    (this->removeOne<Types>(entity), ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> void ::xrn::ecs::Registry<ComponentTypes...>::clear(
    ::xrn::ecs::Entity entity
)
{
    // TODO entity.getSignature()
    ::xrn::ecs::Signature signature;
    ::xrn::ecs::detail::ForEach<ComponentTypes...>::template runIfSignature<
        [] <::xrn::meta::constraint::contains<ComponentTypes...> ComponentType>
        (auto& components, auto& entity){
            components.template remove<decltype(components)>(entity);
        }
    >(signature, *this, entity);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...> RawComponentType
> void ::xrn::ecs::Registry<ComponentTypes...>::clearOne()
{
    using ComponentType = ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>;
    m_memoryManager.template clear<ComponentType>();
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...>... Types
> void ::xrn::ecs::Registry<ComponentTypes...>::clear()
{
    static_assert(sizeof...(Types), "Clear many called with 0 template arguments");
    this->clearOne<Types...>();
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> void ::xrn::ecs::Registry<ComponentTypes...>::clear()
{
    this->clearAll();
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> void ::xrn::ecs::Registry<ComponentTypes...>::clearAll()
{
    m_memoryManager.clearAll();
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...> RawComponentType
> auto ::xrn::ecs::Registry<ComponentTypes...>::get(
    ::xrn::ecs::Entity entity
) -> ::xrn::OptRef<::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>>
{
    using ComponentType = ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>;
    return static_cast<ComponentType*>(m_memoryManager.template getAddr<ComponentType>(entity));
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...> RawComponentType
> auto ::xrn::ecs::Registry<ComponentTypes...>::get(
    ::xrn::ecs::Entity entity
) const
    -> ::xrn::OptRef<const ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>>
{
    using ComponentType = ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>;
    return static_cast<ComponentType*>(m_memoryManager.template getAddr<ComponentType>(entity));
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...> RawComponentType
> auto ::xrn::ecs::Registry<ComponentTypes...>::containsOne(
    ::xrn::ecs::Entity entity
) const
    -> bool
{
    using ComponentType = ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>;
    return m_signatures.at(entity).template contains<ComponentType>();
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...>... Types
> auto ::xrn::ecs::Registry<ComponentTypes...>::contains(
    ::xrn::ecs::Entity entity
) const
    -> bool
{
    static_assert(sizeof...(Types), "Contains many called with 0 template arguments");
    return (this->containsOne<Types>(entity) && ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...>... Types
> auto ::xrn::ecs::Registry<ComponentTypes...>::has(
    ::xrn::ecs::Entity entity
) const
    -> bool
{
    static_assert(sizeof...(Types), "Contains many called with 0 template arguments");
    return (this->containsOne<Types>(entity) && ...);
}
