#pragma once

#include <xrn/Ecs/Component/Container.hpp>


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// static elements
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isEcsRegistered... Types
> constexpr auto ::xrn::ecs::entity::Entity::generate(
    ::xrn::ecs::component::Container& components
)
    -> ::xrn::ecs::entity::Entity
{
    ::xrn::ecs::entity::Entity entity;
    ::xrn::meta::ForEach<Types...>::template run<
        []<::xrn::ecs::detail::constraint::isEcsRegistered Type>(auto& components, auto& entity){
            if constexpr (::xrn::ecs::isComponent<Type>) {
                entity.template addComponents<Type>(components);
            } else {
                entity.template addAbility<Type>();
            }
        }
    >(components, entity);
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
    ::xrn::ecs::detail::constraint::isEcsRegistered... Types
> void ::xrn::ecs::entity::Entity::add(
    ::xrn::ecs::component::Container& components
)
{
    static_assert(sizeof...(Types), "Add called with 0 arguments");
    ::xrn::meta::ForEach<Types...>::template run<
        []<::xrn::ecs::detail::constraint::isEcsRegistered Type>(auto& entity, auto& components){
            if constexpr (::xrn::ecs::isComponent<Type>) {
                entity.template addComponents<Type>(components);
            } else {
                entity.template addAbility<Type>();
            }
        }
    >(*this, components);
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
    static_assert(sizeof...(ComponentTypes), "Add components called with 0 arguments");
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
    static_assert(sizeof...(ComponentTypes), "Add components called with 0 arguments");
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
    static_assert(sizeof...(AbilityTypes), "Add ability called with 0 arguments");
    m_signature.set<AbilityTypes...>();
}




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Has
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isEcsRegistered... Types
> auto ::xrn::ecs::entity::Entity::has() const
    -> bool
{
    static_assert(sizeof...(Types), "Has called with 0 arguments");
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
    static_assert(sizeof...(ComponentTypes), "Has components called with 0 arguments");
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
    static_assert(sizeof...(AbilityTypes), "Has abilities called with 0 arguments");
    return m_signature.contains<AbilityTypes...>();
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Remove
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isEcsRegistered... Types
> void ::xrn::ecs::entity::Entity::remove(
    ::xrn::ecs::component::Container& components
)
{
    static_assert(sizeof...(Types), "Remove called with 0 arguments");
    ::xrn::meta::ForEach<Types...>::template run<
        []<::xrn::ecs::detail::constraint::isEcsRegistered Type>(auto& entity, auto& components){
            if constexpr (::xrn::ecs::isComponent<Type>) {
                entity.template removeComponent<Type>(components);
            } else {
                entity.template removeAbility<Type>();
            }
        }
    >(*this, components);
}

///////////////////////////////////////////////////////////////////////////
void ::xrn::ecs::entity::Entity::removeAbilitiesAndComponents(
    ::xrn::ecs::component::Container& components
)
{
    components.removeAll(*this);
    m_signature.reset();
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
    static_assert(sizeof...(ComponentTypes), "Remove components called with 0 arguments");
    components.removeMany<ComponentTypes...>(m_id);
    m_signature.reset<ComponentTypes...>();
}


///////////////////////////////////////////////////////////////////////////
void ::xrn::ecs::entity::Entity::removeComponents(
    ::xrn::ecs::component::Container& components
)
{
    ::xrn::ecs::component::detail::ForEach::template runIfSignature<
        []<::xrn::ecs::detail::constraint::isComponent RawComponentType>(auto& entity, auto& components){
            using ComponentType = ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>;
            components.template remove<ComponentType>(entity);
            entity.m_signature.reset(ComponentType::getId());
        }
    >(m_signature, *this, components);
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
    static_assert(sizeof...(AbilityTypes), "Remove abilities called with 0 arguments");
    m_signature.reset<AbilityTypes...>();
}

///////////////////////////////////////////////////////////////////////////
void ::xrn::ecs::entity::Entity::removeAbilities()
{
    ::xrn::ecs::ability::detail::ForEach::template runIfSignature<
        []<::xrn::ecs::detail::constraint::isAbility RawAbilityType>(auto& entity){
            using AbilityType = ::std::remove_cvref_t<::std::remove_pointer_t<RawAbilityType>>;
            entity.m_signature.reset(AbilityType::getId());
        }
    >(m_signature, *this);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Getters
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
auto ::xrn::ecs::entity::Entity::getSignature() const
    -> const ::xrn::ecs::Signature&
{
    return m_signature;
}

///////////////////////////////////////////////////////////////////////////
auto ::xrn::ecs::entity::Entity::getId() const
    -> ::xrn::Id
{
    return m_id;
}
