// ------------------------------------------------------------------ HasComponent

template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> auto ::xrn::ecs::Entity::ConstReference::hasComponent() const
    -> bool
{
    return m_entity.hasComponent<ComponentType>();
}

template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> auto ::xrn::ecs::Entity::ConstReference::hasComponents() const
    -> bool
{
    return m_entity.hasComponents<ComponentTypes...>();
}
