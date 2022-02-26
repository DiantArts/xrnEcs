#include <pch.hpp>
#include <Ecs/Signature.hpp>

// ------------------------------------------------------------------

::xrn::ecs::Signature::Signature() noexcept = default;



// ------------------------------------------------------------------

auto ::xrn::ecs::Signature::get(
    ::xrn::ecs::component::ConceptType auto& component
)
    -> bool
{
    return m_bitset[component.getId()];
}

auto ::xrn::ecs::Signature::get(
    ::xrn::Id id
)
    -> bool
{
    return m_bitset[id];
}



// ------------------------------------------------------------------ Get

auto ::xrn::ecs::Signature::operator[](
    ::xrn::ecs::component::ConceptType auto& component
)
    -> bool
{
    return m_bitset[component.getId()];
}

auto ::xrn::ecs::Signature::operator[](
    ::xrn::Id id
)
    -> bool
{
    return m_bitset[id];
}
