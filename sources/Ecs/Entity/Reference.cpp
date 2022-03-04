#include <pch.hpp>
#include <Ecs/Entity/Reference.hpp>



// ------------------------------------------------------------------ Constructors

::xrn::ecs::Entity::Reference::Reference(
    ::xrn::ecs::component::Container& components,
    ::xrn::ecs::Entity& entity
)
    : m_components{ components }, m_entity{ entity }
{}

::xrn::ecs::Entity::Reference::Reference(
    ::xrn::ecs::Entity& entity,
    ::xrn::ecs::component::Container& components
)
    : m_components{ components }, m_entity{ entity }
{}

::xrn::ecs::Entity::Reference::~Reference() = default;



// ------------------------------------------------------------------ Signature

auto ::xrn::ecs::Entity::Reference::getSignature() const
    -> const ::xrn::ecs::Signature&
{
    return m_entity.getSignature();
}



// ------------------------------------------------------------------ Id

auto ::xrn::ecs::Entity::Reference::getId() const
    -> ::xrn::Id
{
    return m_entity.getId();
}


// ------------------------------------------------------------------ Conversion

auto ::xrn::ecs::Entity::Reference::get() const
    -> const ::xrn::ecs::Entity&
{
    return m_entity;
}

::xrn::ecs::Entity::Reference::operator ::xrn::ecs::Entity&()
{
    return m_entity;
}

::xrn::ecs::Entity::Reference::operator const ::xrn::ecs::Entity&() const
{
    return m_entity;
}
