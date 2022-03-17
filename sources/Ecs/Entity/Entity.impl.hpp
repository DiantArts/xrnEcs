#pragma once

#include <Ecs/Component/Container.hpp>


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// static elements
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> constexpr auto ::xrn::ecs::entity::Entity::generate(
    ::xrn::ecs::component::Container& components
)
    -> ::xrn::ecs::entity::Entity
{
    ::xrn::ecs::entity::Entity entity;
    ::xrn::meta::ForEach<Types...>::template run<[]<typename Type>(auto& components, auto& entity){
        static_assert(
            ::xrn::ecs::isComponent<Type> || ::xrn::ecs::isAbility<Type>,
            "Invalid type: Entity::generate takes only Component and Ability types."
        );
        if constexpr (::xrn::ecs::isComponent<Type>) {
            entity.template addComponents<Type>(components);
        } else {
            entity.template addAbility<Type>();
        }
    }>(components, entity);
    return entity;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Add
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> void ::xrn::ecs::entity::Entity::add(
    ::xrn::ecs::component::Container& components
)
{
    ::xrn::meta::ForEach<Types...>::template run<[]<typename Type>(auto& entity, auto& components){
        static_assert(
            ::xrn::ecs::isComponent<Type> || ::xrn::ecs::isAbility<Type>,
            "Invalid type: Entity::add takes only Component and Ability types."
        );
        if constexpr (::xrn::ecs::isComponent<Type>) {
            entity.template addComponents<Type>(components);
        } else {
            entity.template addAbility<Type>();
        }
    }>(*this, components);
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> void ::xrn::ecs::entity::Entity::addComponent(
    ::xrn::ecs::component::Container& components,
    auto&&... args
)
{
    components.emplace<ComponentType>(m_id, ::std::forward<decltype(args)>(args)...);
    m_signature.set<ComponentType>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> void ::xrn::ecs::entity::Entity::addComponents(
    ::xrn::ecs::component::Container& components
)
{
    components.emplaceMany<ComponentTypes...>(m_id);
    m_signature.set<ComponentTypes...>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> void ::xrn::ecs::entity::Entity::addComponents(
    ::xrn::ecs::component::Container& componentsContainer,
    ComponentTypes&&... components
)
{
    componentsContainer.pushMany<ComponentTypes...>(m_id, ::std::forward<ComponentTypes>(components)...);
    m_signature.set<ComponentTypes...>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isAbility AbilityType
> void ::xrn::ecs::entity::Entity::addAbility()
{
    m_signature.set<AbilityType>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isAbility... AbilityTypes
> void ::xrn::ecs::entity::Entity::addAbilities()
{
    m_signature.set<AbilityTypes...>();
}




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Has components
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> auto ::xrn::ecs::entity::Entity::has() const
    -> bool
{
    return m_signature.contains<Types...>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> auto ::xrn::ecs::entity::Entity::hasComponent() const
    -> bool
{
    return m_signature.contains<ComponentType>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> auto ::xrn::ecs::entity::Entity::hasComponents() const
    -> bool
{
    return m_signature.contains<ComponentTypes...>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isAbility AbilityType
> auto ::xrn::ecs::entity::Entity::hasAbility() const
    -> bool
{
    return m_signature.contains<AbilityType>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isAbility... AbilityTypes
> auto ::xrn::ecs::entity::Entity::hasAbilities() const
    -> bool
{
    return m_signature.contains<AbilityTypes...>();
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Remove components
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> void ::xrn::ecs::entity::Entity::remove(
    ::xrn::ecs::component::Container& components
)
{
    ::xrn::meta::ForEach<Types...>::template run<[]<typename Type>(auto& entity, auto& components){
        static_assert(
            ::xrn::ecs::isComponent<Type> || ::xrn::ecs::isAbility<Type>,
            "Invalid type: Entity::remove takes only Component and Ability types."
        );
        if constexpr (::xrn::ecs::isComponent<Type>) {
            entity.template removeComponent<Type>(components);
        } else {
            entity.template removeAbility<Type>();
        }
    }>(*this, components);
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> void ::xrn::ecs::entity::Entity::removeComponent(
    ::xrn::ecs::component::Container& components
)
{
    components.remove<ComponentType>(m_id);
    m_signature.reset<ComponentType>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> void ::xrn::ecs::entity::Entity::removeComponents(
    ::xrn::ecs::component::Container& components
)
{
    components.removeMany<ComponentTypes...>(m_id);
    m_signature.reset<ComponentTypes...>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isAbility AbilityType
> void ::xrn::ecs::entity::Entity::removeAbility()
{
    m_signature.reset<AbilityType>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isAbility... AbilityTypes
> void ::xrn::ecs::entity::Entity::removeAbilities()
{
    m_signature.reset<AbilityTypes...>();
}
