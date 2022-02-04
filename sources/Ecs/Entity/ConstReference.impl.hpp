#pragma once



// ------------------------------------------------------------------ HasComponent

template <
    ::xrn::ecs::component::ConceptType ComponentType
> auto ::xrn::ecs::Entity::ConstReference::hasComponent() const
    -> bool
{
    return m_entity.hasComponent<ComponentType>();
}

template <
    ::xrn::ecs::component::ConceptType... ComponentTypes
> auto ::xrn::ecs::Entity::ConstReference::hasComponents() const
    -> bool
{
    return m_entity.hasComponents<ComponentTypes...>();
}
