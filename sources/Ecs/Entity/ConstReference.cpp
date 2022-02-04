#include <pch.hpp>
#include <Ecs/Entity/ConstReference.hpp>



// ------------------------------------------------------------------ *structors

::xrn::ecs::Entity::ConstReference::ConstReference(
    const ::xrn::ecs::Entity& entity
)
    : m_entity{ entity }
{}

::xrn::ecs::Entity::ConstReference::~ConstReference() = default;



// ------------------------------------------------------------------ Signature

auto ::xrn::ecs::Entity::ConstReference::getSignature() const
    -> const ::xrn::ecs::Signature&
{
    return m_entity.getSignature();
}



// ------------------------------------------------------------------ Id

auto ::xrn::ecs::Entity::ConstReference::getId() const
    -> ::xrn::ecs::Id
{
    return m_entity.getId();
}


// ------------------------------------------------------------------ Conversion

[[ nodiscard ]] auto ::xrn::ecs::Entity::ConstReference::get() const
    -> const ::xrn::ecs::Entity&
{
    return m_entity;
}

[[ nodiscard ]] ::xrn::ecs::Entity::ConstReference::operator
    const ::xrn::ecs::Entity&() const
{
    return m_entity;
}
