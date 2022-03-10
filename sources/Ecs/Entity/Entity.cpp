///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Ecs/Entity/Entity.hpp>
#include <Ecs/Component/ForEach.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Remove components
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::xrn::ecs::entity::Entity::clearComponents(
    ::xrn::ecs::component::Container& container
)
{
    // ::xrn::ecs::component::ForEach::template run<
        // []<::xrn::ecs::detail::constraint::isComponent ComponentType>
        // (::xrn::ecs::entity::Entity& entity, ::xrn::ecs::component::Container& container){
            // entity.removeComponent<ComponentType>(container);
        // }
   // >(m_signature, *this, container);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Getters components
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
