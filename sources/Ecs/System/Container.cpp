///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Ecs/System/Container.hpp>



// ------------------------------------------------------------------ Run

void ::xrn::ecs::system::Container::run(
    ::xrn::Time t,
    ::xrn::ecs::Entity::Container& entities,
    ::xrn::ecs::component::Container& components
)
{
    for (auto& system : m_systems) {
        system->operator()(t, entities, components);
    }
}

void ::xrn::ecs::system::Container::run(
    ::xrn::Time t,
    const ::xrn::ecs::Entity::Container& entities,
    const ::xrn::ecs::component::Container& components
) const
{
    for (auto& system : m_systems) {
        system->operator()(t, entities, components);
    }
}
