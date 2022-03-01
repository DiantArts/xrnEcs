#include <pch.hpp>
#include <Ecs/Entity/Container.hpp>
#include <Ecs/Entity/Reference.hpp>
#include <Ecs/Entity/ConstReference.hpp>
#include <Ecs/Entity/Container.hpp>


// ------------------------------------------------------------------ Constructors

::xrn::ecs::entity::Container::Container(
    ::xrn::ecs::component::Container& components
)
    : m_components{ components }
{}

::xrn::ecs::entity::Container::~Container() = default;



// ------------------------------------------------------------------ Remove

void ::xrn::ecs::entity::Container::remove(
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

void ::xrn::ecs::entity::Container::remove(
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

[[ nodiscard ]] auto ::xrn::ecs::entity::Container::operator[](
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

[[ nodiscard ]] auto ::xrn::ecs::entity::Container::operator[](
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

[[ nodiscard ]] auto ::xrn::ecs::entity::Container::get(
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

[[ nodiscard ]] auto ::xrn::ecs::entity::Container::unsafeGet(
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

[[ nodiscard ]] auto ::xrn::ecs::entity::Container::unsafeGet(
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

[[ nodiscard ]] auto ::xrn::ecs::entity::Container::contains(
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

[[ nodiscard ]] auto ::xrn::ecs::entity::Container::begin()
    -> Container::Type::iterator
{
    return m_entities.begin();
}

[[ nodiscard ]] auto ::xrn::ecs::entity::Container::begin() const
    -> Container::Type::const_iterator
{
    return m_entities.begin();
}

[[ nodiscard ]] auto ::xrn::ecs::entity::Container::cbegin() const
    -> Container::Type::const_iterator
{
    return m_entities.cbegin();
}

[[ nodiscard ]] auto ::xrn::ecs::entity::Container::end()
    -> Container::Type::iterator
{
    return m_entities.end();
}

[[ nodiscard ]] auto ::xrn::ecs::entity::Container::end() const
    -> Container::Type::const_iterator
{
    return m_entities.end();
}

[[ nodiscard ]] auto ::xrn::ecs::entity::Container::cend() const
    -> Container::Type::const_iterator
{
    return m_entities.cend();
}
