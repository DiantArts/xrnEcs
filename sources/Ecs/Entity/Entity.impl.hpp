// ------------------------------------------------------------------ Genetate

template <
    ::xrn::ecs::component::ConceptType... ComponentTypes
> [[ nodiscard ]] constexpr auto ::xrn::ecs::entity::Entity::generate(
    ::xrn::ecs::component::Container& components
)
    -> ::xrn::ecs::entity::Entity
{
    ::xrn::ecs::entity::Entity entity;

    ::xrn::meta::ForEach<ComponentTypes...>::template run<
        []<
            ::xrn::ecs::component::ConceptType ComponentType
        >(
            ::xrn::ecs::entity::Entity& entity,
            ::xrn::ecs::component::Container& components
        ){
            entity.addComponent<ComponentType>(components);
        }
    >(entity, components);

    return entity;
}



// ------------------------------------------------------------------ AddComponent

template <
    ::xrn::ecs::component::ConceptType RawComponentType
> auto ::xrn::ecs::entity::Entity::addComponent(
    ::xrn::ecs::component::Container& components
)
    -> RawComponentType&
{
    using ComponentType =::std::remove_reference_t<RawComponentType>;
    m_signature.set<ComponentType>();
    return components.emplace<ComponentType>(m_id);
}

template <
    ::xrn::ecs::component::ConceptType... ComponentTypes
> void ::xrn::ecs::entity::Entity::addComponents(
    ::xrn::ecs::component::Container& components
)
{
    m_signature.set<ComponentTypes...>();
    components.emplaceMany<ComponentTypes...>(m_id);
}

template <
    ::xrn::ecs::component::ConceptType... ComponentTypes
> void ::xrn::ecs::entity::Entity::addComponents(
    ::xrn::ecs::component::Container& componentsContainer,
    ComponentTypes&&... components
)
{
    m_signature.set<ComponentTypes...>();
    componentsContainer.pushMany<ComponentTypes...>(m_id, ::std::forward<ComponentTypes>(components)...);
}




// ------------------------------------------------------------------ HasComponent

template <
    ::xrn::ecs::component::ConceptType RawComponentType
> [[ nodiscard ]] auto ::xrn::ecs::entity::Entity::hasComponent() const
    -> bool
{
    using ComponentType =::std::remove_reference_t<RawComponentType>;
    return m_signature.contains<ComponentType>();
}

template <
    ::xrn::ecs::component::ConceptType... ComponentTypes
> [[ nodiscard ]] auto ::xrn::ecs::entity::Entity::hasComponents() const
    -> bool
{
    return m_signature.contains<ComponentTypes...>();
}



// ------------------------------------------------------------------ RemoveComponent

template <
    ::xrn::ecs::component::ConceptType RawComponentType
> void ::xrn::ecs::entity::Entity::removeComponent(
    ::xrn::ecs::component::Container& components
)
{
    using ComponentType =::std::remove_reference_t<RawComponentType>;
    m_signature.reset<ComponentType>();
    components.remove<ComponentType>(m_id);
}

template <
    ::xrn::ecs::component::ConceptType... ComponentTypes
> void ::xrn::ecs::entity::Entity::removeComponents(
    ::xrn::ecs::component::Container& components
)
{
    m_signature.reset<ComponentTypes...>();
    components.removeMany<ComponentTypes...>(m_id);
}
