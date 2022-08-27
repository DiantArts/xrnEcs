#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Meta/Constraint.hpp>
#include <xrn/Util/Time.hpp>
#include <xrn/Util/Id.hpp>

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

} // namespace xrn::ecs::detail::constraint
