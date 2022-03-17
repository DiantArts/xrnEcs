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
namespace xrn::ecs::component { template <typename T> class AComponent; }



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
///        ::xrn::util::Time
///
/// The comparison ignores cv-qualifiers and references (compares the type
/// referenced).
///
/// \tparam Type to check
///
/// \return True if the Type given as template parameter is a
///         ::xrn::util::Time. False otherwise
///
/// \see ::xrn::util::Time
///
///////////////////////////////////////////////////////////////////////////
template <
    typename Type
> concept isTime =
    ::xrn::meta::constraint::sameAs<::xrn::Time, Type>;

///////////////////////////////////////////////////////////////////////////
/// \brief Checks whether the Type given as template parameter is an
///        ::xrn::util::Id
///
/// The comparison ignores cv-qualifiers and references (compares the type
/// referenced).
/// A ::xrn::util::Id::Type is concidered as an ::xrn::util::Id.
///
/// \tparam Type to check
///
/// \return True if the Type given as template parameter is an
///         ::xrn::util::Id. False otherwise
///
/// \see ::xrn::util::Id
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
/// \return True if the Type given as template parameter inherits from
///         ::xrn::ecs::component::declaration::detail::AComponent. False otherwise
///
/// \see ::xrn::ecs::component::declaration::detail::AComponent
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
/// \return True if the Type given as template parameter inherits from
///         ::xrn::ecs::component::declaration::detail::AComponent. False otherwise
///
/// \see ::xrn::ecs::component::declaration::detail::AComponent
///
///////////////////////////////////////////////////////////////////////////
template <
    typename Type
> concept isAbility =
    ::xrn::ecs::isAbility<::std::remove_cvref_t<::std::remove_pointer_t<Type>>>;

} // namespace xrn::ecs::detail::constraint
