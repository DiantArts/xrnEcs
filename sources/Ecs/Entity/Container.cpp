///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>
#include <Ecs/Entity/Container.hpp>
#include <Ecs/Entity/Reference.hpp>
#include <Ecs/Entity/ConstReference.hpp>
#include <Ecs/Entity/Container.hpp>


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::xrn::ecs::Entity::Container::Container(
    ::xrn::ecs::component::Container& components
)
    : m_components{ components }
{}



// ------------------------------------------------------------------ Remove

///////////////////////////////////////////////////////////////////////////
void ::xrn::ecs::Entity::Container::remove(
    ::xrn::Id entityId
)
{
    m_entities.erase(::std::ranges::find_if(m_entities,
        [
            entityId{ ::std::move(entityId) }
        ](
            const ::xrn::ecs::Entity& entity
        ){
            return entity.getId() == entityId;
        }
    ));
}

///////////////////////////////////////////////////////////////////////////
void ::xrn::ecs::Entity::Container::remove(
    ::xrn::ecs::Entity::Reference&& reference
)
{
    m_entities.erase(::std::ranges::find_if(m_entities,
        [
            reference{ ::std::move(reference) }
        ](
            const ::xrn::ecs::Entity& entity
        ){
            return &entity == &reference.get();
        }
    ));
}



// ------------------------------------------------------------------ Get

///////////////////////////////////////////////////////////////////////////
auto ::xrn::ecs::Entity::Container::operator[](
    ::xrn::Id entityId
) const
    -> ::xrn::ecs::Entity::ConstReference
{
    auto it{ ::std::ranges::find_if(m_entities,
        [entityId](const ::xrn::ecs::Entity& entity){
            return entity.getId() == entityId;
        }
    ) };
    if (it == m_entities.end()) {
        throw ::std::runtime_error("Entity '"s + static_cast<::std::string>(entityId) +
                "' inst't present in the EntityContainer");
    }
    return ::xrn::ecs::Entity::ConstReference{ *it };
}

///////////////////////////////////////////////////////////////////////////
auto ::xrn::ecs::Entity::Container::operator[](
    ::xrn::Id entityId
)
    -> ::xrn::ecs::Entity::Reference
{
    auto it{ ::std::ranges::find_if(m_entities,
        [entityId](const ::xrn::ecs::Entity& entity){
            return entity.getId() == entityId;
        }
    ) };
    if (it == m_entities.end()) {
        throw ::std::runtime_error("Entity '"s + static_cast<::std::string>(entityId) +
                "' inst't present in the EntityContainer");
    }
    return ::xrn::ecs::Entity::Reference{m_components, *it };
}

///////////////////////////////////////////////////////////////////////////
auto ::xrn::ecs::Entity::Container::get(
    ::xrn::Id entityId
) const
    -> ::xrn::ecs::Entity::ConstReference
{
    auto it{ ::std::ranges::find_if(m_entities,
        [entityId](const ::xrn::ecs::Entity& entity){
            return entity.getId() == entityId;
        }
    ) };
    if (it == m_entities.end()) {
        throw ::std::runtime_error("Entity '"s + static_cast<::std::string>(entityId) +
                "' inst't present in the EntityContainer");
    }
    return ::xrn::ecs::Entity::ConstReference{ *it };
}

///////////////////////////////////////////////////////////////////////////
auto ::xrn::ecs::Entity::Container::unsafeGet(
    ::xrn::Id entityId
)
    -> ::xrn::ecs::Entity::Reference
{
    return ::xrn::ecs::Entity::Reference{ m_components, *::std::ranges::find_if(m_entities,
        [entityId](const ::xrn::ecs::Entity& entity){
            return entity.getId() == entityId;
        }
    ) };
}

///////////////////////////////////////////////////////////////////////////
auto ::xrn::ecs::Entity::Container::unsafeGet(
    ::xrn::Id entityId
) const
    -> ::xrn::ecs::Entity::ConstReference
{
    return ::xrn::ecs::Entity::ConstReference{ *::std::ranges::find_if(m_entities,
        [entityId](const ::xrn::ecs::Entity& entity){
            return entity.getId() == entityId;
        }
    ) };
}



// ------------------------------------------------------------------ Contains

///////////////////////////////////////////////////////////////////////////
auto ::xrn::ecs::Entity::Container::contains(
    ::xrn::Id entityId
) const
    -> bool
{
    return ::std::ranges::find_if(m_entities,
        [entityId](const ::xrn::ecs::Entity& entity){
            return entity.getId() == entityId;
        }
    ) != m_entities.end();
}



// ------------------------------------------------------------------ Iterator

///////////////////////////////////////////////////////////////////////////
auto ::xrn::ecs::Entity::Container::begin()
    -> Container::Type::iterator
{
    return m_entities.begin();
}

///////////////////////////////////////////////////////////////////////////
auto ::xrn::ecs::Entity::Container::begin() const
    -> Container::Type::const_iterator
{
    return m_entities.begin();
}

///////////////////////////////////////////////////////////////////////////
auto ::xrn::ecs::Entity::Container::cbegin() const
    -> Container::Type::const_iterator
{
    return m_entities.cbegin();
}

///////////////////////////////////////////////////////////////////////////
auto ::xrn::ecs::Entity::Container::end()
    -> Container::Type::iterator
{
    return m_entities.end();
}

///////////////////////////////////////////////////////////////////////////
auto ::xrn::ecs::Entity::Container::end() const
    -> Container::Type::const_iterator
{
    return m_entities.end();
}

///////////////////////////////////////////////////////////////////////////
auto ::xrn::ecs::Entity::Container::cend() const
    -> Container::Type::const_iterator
{
    return m_entities.cend();
}
