#pragma once

#include <Meta/ForEach.hpp>
#include <Ecs/Component/Detail/Container.hpp>



// ------------------------------------------------------------------ Id

template <
    ::xrn::ecs::component::ConceptType RawComponentType
> constexpr auto ::xrn::ecs::component::Container::getId() const
    -> ::xrn::ecs::Id
{
    using ComponentType = ::std::remove_cvref_t<RawComponentType>;
    return ComponentType::getId();
}

constexpr auto ::xrn::ecs::component::Container::getMaxId()
    -> ::xrn::ecs::Id
{
    return ::xrn::ecs::component::maxId;
}



// ------------------------------------------------------------------ Emplace/Remove

template <
    ::xrn::ecs::component::ConceptType RawComponentType
> auto ::xrn::ecs::component::Container::emplace(
    ::xrn::ecs::Id entityId,
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
    ::xrn::ecs::component::ConceptType... ComponentTypes
> void ::xrn::ecs::component::Container::emplaceMany(
    ::xrn::ecs::Id entityId
)
{
    (this->emplace<ComponentTypes>(entityId), ...);
}

template <
    ::xrn::ecs::component::ConceptType RawComponentType
> void ::xrn::ecs::component::Container::push(
    ::xrn::ecs::Id entityId,
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
    ::xrn::ecs::component::ConceptType... ComponentTypes
> void ::xrn::ecs::component::Container::pushMany(
    ::xrn::ecs::Id entityId,
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
    ::xrn::ecs::component::ConceptType RawComponentType
> void ::xrn::ecs::component::Container::remove(
    ::xrn::ecs::Id entityId
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

template <
    ::xrn::ecs::component::ConceptType... ComponentTypes
> void ::xrn::ecs::component::Container::removeMany(
    ::xrn::ecs::Id entityId
)
{
    (this->remove<ComponentTypes>(entityId), ...);
}



// ------------------------------------------------------------------ Get

template <
    ::xrn::ecs::component::ConceptType RawComponentType
> auto ::xrn::ecs::component::Container::get(
    ::xrn::ecs::Id entityId
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
    ::xrn::ecs::component::ConceptType RawComponentType
> auto ::xrn::ecs::component::Container::get(
    ::xrn::ecs::Id entityId
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
    ::xrn::ecs::component::ConceptType RawComponentType
> auto ::xrn::ecs::component::Container::getIndex(
    ::xrn::ecs::Id entityId
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
    ::xrn::ecs::component::ConceptType RawComponentType
> auto ::xrn::ecs::component::Container::exists(
    ::xrn::ecs::Id entityId
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
    ::xrn::ecs::component::ConceptType RawComponentType
> auto ::xrn::ecs::component::Container::getVector() const
    -> const ::std::vector<RawComponentType>&
{
    using ComponentType = ::std::remove_cvref_t<RawComponentType>;
    auto& pairComponentContainer{ this->getUnsafePairSubContainer<ComponentType>() };
    return (*static_cast<Container::SubContainerType<ComponentType>*>(pairComponentContainer.second));
}

template <
    ::xrn::ecs::component::ConceptType RawComponentType
> auto ::xrn::ecs::component::Container::vectorExists() const
    -> bool
{
    using ComponentType = ::std::remove_cvref_t<RawComponentType>;
    return m_container.find(ComponentType::getId()) != m_container.end();
}



// ------------------------------------------------------------------ Private

template <
    ::xrn::ecs::component::ConceptType RawComponentType
> auto ::xrn::ecs::component::Container::getUnsafePairSubContainer()
    -> SubPairContainerType&
{
    using ComponentType = ::std::remove_cvref_t<RawComponentType>;

    return m_container.try_emplace(
        ComponentType::getId(),
        ::std::make_pair<::std::vector<::xrn::ecs::Id>, void*>(
            ::std::vector<::xrn::ecs::Id>{},
            new ::std::vector<ComponentType>{}
        )
    ).first->second;
}

template <
    ::xrn::ecs::component::ConceptType RawComponentType
> auto ::xrn::ecs::component::Container::getUnsafePairSubContainer() const
    -> const SubPairContainerType&
{
    using ComponentType = ::std::remove_cvref_t<RawComponentType>;
    return m_container.at(ComponentType::getId());
}
