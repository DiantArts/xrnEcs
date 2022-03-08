///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Emplace
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> auto ::xrn::ecs::Entity::Container::emplace()
    -> ::xrn::ecs::Entity::Reference
{
    auto& entity{ m_entities.emplace_back() };
    if constexpr (sizeof...(ComponentTypes) > 0) {
        entity.addComponents<ComponentTypes...>(m_components);
    }
    return ::xrn::ecs::Entity::Reference{ m_components, entity };
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> auto ::xrn::ecs::Entity::Container::emplace(
    ComponentTypes&&... components
) -> ::xrn::ecs::Entity::Reference
{
    auto& entity{ m_entities.emplace_back() };
    if constexpr (sizeof...(ComponentTypes) > 0) {
        entity.addComponents<ComponentTypes...>(
            m_components,
            ::std::forward<ComponentTypes>(components)...
        );
    }
    return ::xrn::ecs::Entity::Reference{ m_components, entity };
}
