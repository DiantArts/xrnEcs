#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Meta/Constraint.hpp>
#include <Meta/IsBaseOfTemplate.hpp>
#include <Util/Time.hpp>
#include <Ecs/Component/Detail/Declaration.hpp>

///////////////////////////////////////////////////////////////////////////
// Forward declarations
///////////////////////////////////////////////////////////////////////////
namespace xrn::ecs::entity { class Entity; }



namespace xrn::ecs::detail::constraint {

///////////////////////////////////////////////////////////////////////////
/// \brief Checks whether the Type given as template parameter is an
///        ::xrn::ecs::entity::Entity
///
/// The comparison ignores cv-qualifiers and references (compares the type
/// referenced).
///
/// \tparam Type to check
///
/// \return True if the Type given as template parameter is an
///         ::xrn::ecs::entity::Entity. False otherwise
///
/// \see ::xrn::ecs::entity::Entity
///
///////////////////////////////////////////////////////////////////////////
template <
    typename Type
> concept isEntity =
    ::xrn::meta::constraint::sameAs<::xrn::ecs::entity::Entity, Type>;

///////////////////////////////////////////////////////////////////////////
/// \brief Checks whether the Type given as template parameter is a
///        ::xrn::util::BasicTime
///
/// The comparison ignores cv-qualifiers and references (compares the type
/// referenced).
///
/// \tparam Type to check
///
/// \return True if the Type given as template parameter is a
///         ::xrn::util::BasicTime. False otherwise
///
/// \see ::xrn::util::BasicTime
///
///////////////////////////////////////////////////////////////////////////
template <
    typename Type
> concept isTime =
    ::xrn::meta::constraint::sameAs<::xrn::Time, Type>;

///////////////////////////////////////////////////////////////////////////
/// \brief Checks whether the Type given as template parameter is an
///        ::xrn::util::BasicForwardId
///
/// The comparison ignores cv-qualifiers and references (compares the type
/// referenced).
/// A ::xrn::util::BasicForwardId::Type is concidered as an
/// ::xrn::util::BasicForwardId.
///
/// \tparam Type to check
///
/// \return True if the Type given as template parameter is an
///         ::xrn::util::BasicForwardId. False otherwise
///
/// \see ::xrn::util::BasicForwardId
///
///////////////////////////////////////////////////////////////////////////
template <
    typename Type
> concept isId =
    ::xrn::meta::constraint::sameAs<::xrn::Id, Type> ||
    ::xrn::meta::constraint::sameAs<::xrn::Id::Type, Type>;

///////////////////////////////////////////////////////////////////////////
/// \brief Checks whether the Type given as template parameter is a
///        component.
///
/// The comparison ignores cv-qualifiers and references (compares the type
/// referenced).
///
/// \tparam Type to check
///
/// \return True if the Type given as template parameter is declared by
///         COMPONENT or COMPONENT_IN_NAMESPACE macros. False otherwise
///
///////////////////////////////////////////////////////////////////////////
template <
    typename Type
> concept isComponent =
    ::xrn::ecs::isComponent<::std::remove_cvref_t<::std::remove_pointer_t<Type>>>;

///////////////////////////////////////////////////////////////////////////
/// \brief Checks whether the Type given as template parameter is an
///        ability.
///
/// Abilities are empty uninstantiable componens only providing a functionality to
/// the linked entity.
/// The comparison ignores cv-qualifiers and references (compares the type
/// referenced).
///
/// \tparam Type to check
///
/// \return True if the Type given as template parameter is declared by
///         ABILITY or ABILITY_IN_NAMESPACE macros. False otherwise
///
///////////////////////////////////////////////////////////////////////////
template <
    typename Type
> concept isAbility =
    ::xrn::ecs::isAbility<::std::remove_cvref_t<::std::remove_pointer_t<Type>>>;

///////////////////////////////////////////////////////////////////////////
/// \brief Checks whether the Type given as template parameter is an
///        ability or a component.
///
/// The comparison ignores cv-qualifiers and references (compares the type
/// referenced).
///
/// \tparam Type to check
///
/// \return True if the Type given as template parameter is declared by
///         COMPONENT, COMPONENT_IN_NAMESPACE, ABILITY or
///         ABILITY_IN_NAMESPACE macros. False otherwise
///
///////////////////////////////////////////////////////////////////////////
template <
    typename Type
> concept isEcsRegistered =
    ::xrn::ecs::detail::constraint::isComponent<Type> || ::xrn::ecs::detail::constraint::isAbility<Type>;

} // namespace xrn::ecs::detail::constraint
