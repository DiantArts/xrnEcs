#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// HasComponents
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isEcsRegistered... Types
> auto ::xrn::ecs::entity::ConstReference::has() const
    -> bool
{
    return m_entity->has<Types...>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> auto ::xrn::ecs::entity::ConstReference::hasComponent() const
    -> bool
{
    return m_entity->hasComponent<ComponentType>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> auto ::xrn::ecs::entity::ConstReference::hasComponents() const
    -> bool
{
    return m_entity->hasComponents<ComponentTypes...>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isAbility AbilityType
> auto ::xrn::ecs::entity::ConstReference::hasAbility() const
    -> bool
{
    return m_entity->hasAbility<AbilityType>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isAbility... AbilityTypes
> auto ::xrn::ecs::entity::ConstReference::hasAbilities() const
    -> bool
{
    return m_entity->hasAbilities<AbilityTypes...>();
}

