// ------------------------------------------------------------------ AddComponent

template <
    ::xrn::ecs::component::ConceptType ComponentType
> auto ::xrn::ecs::Entity::Reference::addComponent() const
    -> ComponentType&
{
    return m_entity.addComponent<ComponentType>(m_components);
}

template <
    ::xrn::ecs::component::ConceptType... ComponentTypes
> void ::xrn::ecs::Entity::Reference::addComponents()
{
    m_entity.addComponents<ComponentTypes...>(m_components);
}




// ------------------------------------------------------------------ HasComponent

template <
    ::xrn::ecs::component::ConceptType ComponentType
> auto ::xrn::ecs::Entity::Reference::hasComponent() const
    -> bool
{
    return m_entity.hasComponent<ComponentType>();
}

template <
    ::xrn::ecs::component::ConceptType... ComponentTypes
> auto ::xrn::ecs::Entity::Reference::hasComponents() const
    -> bool
{
    return m_entity.hasComponents<ComponentTypes...>();
}



// ------------------------------------------------------------------ RemoveComponent

template <
    ::xrn::ecs::component::ConceptType ComponentType
> void ::xrn::ecs::Entity::Reference::removeComponent()
{
    m_entity.removeComponent<ComponentType>(m_components);
}

template <
    ::xrn::ecs::component::ConceptType... ComponentTypes
> void ::xrn::ecs::Entity::Reference::removeComponents()
{
    m_entity.removeComponents<ComponentTypes...>(m_components);
}
