#pragma once

#include <Meta/ForEach.hpp>
#include <Ecs/Component/Detail/Container.hpp>
#include <Ecs/Component/ForEach.hpp>


// ------------------------------------------------------------------ Id

template <
    ::xrn::ecs::detail::constraint::isComponent RawComponentType
> consteval auto ::xrn::ecs::component::Container::getId() const
    -> ::xrn::Id
{
    using ComponentType = ::std::remove_cvref_t<RawComponentType>;
    return ComponentType::getId();
}

consteval auto ::xrn::ecs::component::Container::getMaxId()
    -> ::xrn::Id
{
    return ::xrn::ecs::component::maxId;
}



// ------------------------------------------------------------------ Emplace/Remove

template <
    ::xrn::ecs::detail::constraint::isComponent RawComponentType
> auto ::xrn::ecs::component::Container::emplace(
    ::xrn::Id entityId,
    auto&&... args
)
    -> RawComponentType&
{
    using ComponentType = ::std::remove_cvref_t<RawComponentType>;
    auto& pairComponentContainer{ this->getUnsafePairSubContainer<ComponentType>() };
    auto it{ ::std::ranges::find(pairComponentContainer.first, entityId) };
    if (it != pairComponentContainer.first.end()) {
        throw ::std::runtime_error(
            "Entity '"s + static_cast<::std::string>(entityId) + "' already contain an '"s +
                boost::typeindex::type_id<ComponentType>().pretty_name() + "' component"
        );
    }
    pairComponentContainer.first.push_back(::std::move(entityId));
    return (*static_cast<Container::SubContainerType<ComponentType>*>(pairComponentContainer.second)).
        emplace_back(::std::forward<decltype(args)>(args)...);
}

template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> void ::xrn::ecs::component::Container::emplaceMany(
    ::xrn::Id entityId
)
{
    (this->emplace<ComponentTypes>(entityId), ...);
}

template <
    ::xrn::ecs::detail::constraint::isComponent RawComponentType
> void ::xrn::ecs::component::Container::push(
    ::xrn::Id entityId,
    RawComponentType&& component
)
{
    using ComponentType = ::std::remove_cvref_t<RawComponentType>;
    auto& pairComponentContainer{ this->getUnsafePairSubContainer<ComponentType>() };
    auto it{ ::std::ranges::find(pairComponentContainer.first, entityId) };
    if (it != pairComponentContainer.first.end()) {
        throw ::std::runtime_error(
            "Entity '"s + static_cast<::std::string>(entityId) + "' already contain an '"s +
                boost::typeindex::type_id<ComponentType>().pretty_name() + "' component"
        );
    }
    pairComponentContainer.first.push_back(::std::move(entityId));
    (*static_cast<Container::SubContainerType<ComponentType>*>(pairComponentContainer.second)).
        push_back(::std::forward<decltype(component)>(component));
}

template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> void ::xrn::ecs::component::Container::pushMany(
    ::xrn::Id entityId,
    ComponentTypes&&... components
)
{
    ::xrn::ecs::component::detail::PushMany<ComponentTypes...>::use(
        *this,
        entityId,
        ::std::forward<ComponentTypes>(components)...
    );
}

template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> void ::xrn::ecs::component::Container::removeMany(
    ::xrn::Id entityId
)
{
    (this->remove<ComponentTypes>(entityId), ...);
}

void ::xrn::ecs::component::Container::removeMany(
    const ::xrn::Id entityId,
    ::xrn::ecs::detail::constraint::isId auto... componentIds
)
{
    (this->remove(entityId, componentIds), ...);
}

template <
    ::xrn::ecs::detail::constraint::isComponent RawComponentType
> void ::xrn::ecs::component::Container::remove(
    const ::xrn::Id entityId
)
{
    using ComponentType = ::std::remove_cvref_t<RawComponentType>;
    auto& pairComponentContainer{ this->getUnsafePairSubContainer<ComponentType>() };
    auto it{ ::std::ranges::find(pairComponentContainer.first, entityId) };
    if (it == pairComponentContainer.first.end()) {
        throw ::std::runtime_error(
            "Entity '"s + static_cast<::std::string>(entityId) + "' doesn't contain an '"s +
                boost::typeindex::type_id<ComponentType>().pretty_name() + "' component"
        );
    }
    pairComponentContainer.first.erase(it);
}

void ::xrn::ecs::component::Container::clear()
{
    // ::xrn::ecs::component::ForEach::template runWithId<
        // []<::xrn::ecs::detail::constraint::isComponent ComponentType> (
            // ::xrn::Id componentId,
            // ::xrn::ecs::component::Container& components
        // ){
            // components.removeVector<ComponentType>(componentId);
        // }
   // >(*this);
}



// ------------------------------------------------------------------ Get

template <
    ::xrn::ecs::detail::constraint::isComponent RawComponentType
> auto ::xrn::ecs::component::Container::get(
    ::xrn::Id entityId
) const
    -> const RawComponentType&
{
    using ComponentType = ::std::remove_cvref_t<RawComponentType>;
    auto& pairComponentContainer{ this->getUnsafePairSubContainer<ComponentType>() };
    auto it{ ::std::ranges::find(pairComponentContainer.first, entityId) };
    if (it == pairComponentContainer.first.end()) {
        throw ::std::runtime_error(
            "Entity '"s + static_cast<::std::string>(entityId) + "' doesn't contain an '"s +
                boost::typeindex::type_id<ComponentType>().pretty_name() + "' component"
        );
    }
    return (*static_cast<Container::SubContainerType<ComponentType>*>(pairComponentContainer.second)).at(
        it - pairComponentContainer.first.begin()
    );
}

template <
    ::xrn::ecs::detail::constraint::isComponent RawComponentType
> auto ::xrn::ecs::component::Container::get(
    ::xrn::Id entityId
)
    -> RawComponentType&
{
    using ComponentType = ::std::remove_cvref_t<RawComponentType>;
    auto& pairComponentContainer{ this->getUnsafePairSubContainer<ComponentType>() };
    auto it{ ::std::ranges::find(pairComponentContainer.first, entityId) };
    if (it == pairComponentContainer.first.end()) {
        throw ::std::runtime_error(
            "Entity '"s + static_cast<::std::string>(entityId) + "' doesn't contain an '"s +
                boost::typeindex::type_id<ComponentType>().pretty_name() + "' component"
        );
    }
    return (*static_cast<Container::SubContainerType<ComponentType>*>(pairComponentContainer.second)).at(
        it - pairComponentContainer.first.begin()
    );
}

template <
    ::xrn::ecs::detail::constraint::isComponent RawComponentType
> auto ::xrn::ecs::component::Container::getIndex(
    ::xrn::Id entityId
) const
    -> ::std::size_t
{
    using ComponentType = ::std::remove_cvref_t<RawComponentType>;
    auto& IdContainer{ this->getUnsafePairSubContainer<ComponentType>().first };
    auto it{ ::std::ranges::find(IdContainer, entityId) };
    if (it == IdContainer.end()) {
        throw ::std::runtime_error(
            "Entity '"s + static_cast<::std::string>(entityId) + "' doesn't contain an '"s +
                boost::typeindex::type_id<ComponentType>().pretty_name() + "' component"
        );
    }
    return it - IdContainer.begin();
}

template <
    ::xrn::ecs::detail::constraint::isComponent RawComponentType
> auto ::xrn::ecs::component::Container::exists(
    ::xrn::Id entityId
) const
    -> bool
{
    using ComponentType = ::std::remove_cvref_t<RawComponentType>;
    auto it{ m_container.find(ComponentType::getId()) };
    if (it == m_container.end()) {
        return false;
    }
    return ::std::ranges::find(it->second.first, entityId) != it->second.first.end();
}



template <
    ::xrn::ecs::detail::constraint::isComponent RawComponentType
> auto ::xrn::ecs::component::Container::getVector() const
    -> const ::std::vector<RawComponentType>&
{
    using ComponentType = ::std::remove_cvref_t<RawComponentType>;
    auto& pairComponentContainer{ this->getUnsafePairSubContainer<ComponentType>() };
    return (*static_cast<Container::SubContainerType<ComponentType>*>(pairComponentContainer.second));
}

template <
    ::xrn::ecs::detail::constraint::isComponent RawComponentType
> void ::xrn::ecs::component::Container::removeVector()
{
    // using ComponentType = ::std::remove_cvref_t<RawComponentType>;
    // auto& pairComponentContainer{ this->getUnsafePairSubContainer<ComponentType>() };
    // delete static_cast<Container::SubContainerType<ComponentType>*>(pairComponentContainer.second);
}

template <
    ::xrn::ecs::detail::constraint::isComponent RawComponentType
> void ::xrn::ecs::component::Container::removeVector(
    ::xrn::Id componentId
)
{
    // using ComponentType = ::std::remove_cvref_t<RawComponentType>;
    // auto& pairComponentContainer{ this->getUnsafePairSubContainer(componentId) };
    // delete static_cast<Container::SubContainerType<ComponentType>*>(pairComponentContainer.second);
}

template <
    ::xrn::ecs::detail::constraint::isComponent RawComponentType
> auto ::xrn::ecs::component::Container::vectorExists() const
    -> bool
{
    using ComponentType = ::std::remove_cvref_t<RawComponentType>;
    return m_container.find(ComponentType::getId()) != m_container.end();
}



// ------------------------------------------------------------------ Private

template <
    ::xrn::ecs::detail::constraint::isComponent RawComponentType
> auto ::xrn::ecs::component::Container::getUnsafePairSubContainer()
    -> SubPairContainerType&
{
    using ComponentType = ::std::remove_cvref_t<RawComponentType>;

    return m_container.try_emplace(
        ComponentType::getId(),
        ::std::make_pair<::std::vector<::xrn::Id>, void*>(
            ::std::vector<::xrn::Id>{},
            new ::std::vector<ComponentType>{}
        )
    ).first->second;
}

template <
    ::xrn::ecs::detail::constraint::isComponent RawComponentType
> auto ::xrn::ecs::component::Container::getUnsafePairSubContainer() const
    -> const SubPairContainerType&
{
    using ComponentType = ::std::remove_cvref_t<RawComponentType>;
    return m_container.at(ComponentType::getId());
}
