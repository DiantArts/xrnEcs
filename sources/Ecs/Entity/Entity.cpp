#include <pch.hpp>
#include <Ecs/Entity/Entity.hpp>



// ------------------------------------------------------------------ Signature

auto ::xrn::ecs::entity::Entity::getSignature() const
    -> const ::xrn::ecs::Signature&
{
    return m_signature;
}



// ------------------------------------------------------------------ Id

auto ::xrn::ecs::entity::Entity::getId() const
    -> ::xrn::Id
{
    return m_id;
}
