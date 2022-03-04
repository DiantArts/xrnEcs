// ------------------------------------------------------------------ AddComponent

template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> void ::xrn::ecs::Entity::Reference::addComponent(
    auto&&... args
) const
{
    return m_entity.addComponent<ComponentType>(m_components, ::std::forward<decltype(args)>(args)...);
}

template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> void ::xrn::ecs::Entity::Reference::addComponents()
{
    m_entity.addComponents<ComponentTypes...>(m_components);
}




// ------------------------------------------------------------------ HasComponent

template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> auto ::xrn::ecs::Entity::Reference::hasComponent() const
    -> bool
{
    return m_entity.hasComponent<ComponentType>();
}

template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> auto ::xrn::ecs::Entity::Reference::hasComponents() const
    -> bool
{
    return m_entity.hasComponents<ComponentTypes...>();
}



// ------------------------------------------------------------------ RemoveComponent

template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> void ::xrn::ecs::Entity::Reference::removeComponent()
{
    m_entity.removeComponent<ComponentType>(m_components);
}

template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> void ::xrn::ecs::Entity::Reference::removeComponents()
{
    m_entity.removeComponents<ComponentTypes...>(m_components);
}
