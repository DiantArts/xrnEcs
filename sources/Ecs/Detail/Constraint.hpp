#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Meta/Constraint.hpp>
#include <Meta/IsBaseOfTemplate.hpp>
#include <Util/Time.hpp>

///////////////////////////////////////////////////////////////////////////
// Forward declerations
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
/// \brief Checks whether the Type given as template parameter is an
///        ::xrn::util::Time
///
/// The comparison ignores cv-qualifiers and references (compares the type
/// referenced).
///
/// \tparam Type to check
///
/// \return True if the Type given as template parameter is an
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
/// \brief Checks whether the Type given as template parameter inherits
///        from ::xrn::ecs::component::AComponent
///
/// The comparison ignores cv-qualifiers and references (compares the type
/// referenced).
///
/// \tparam Type to check
///
/// \return True if the Type given as template parameter inherits from
///         ::xrn::ecs::component::AComponent. False otherwise
///
/// \see ::xrn::ecs::component::AComponent
///
///////////////////////////////////////////////////////////////////////////
template <
    typename Type
> concept isComponent =
    ::xrn::meta::IsBaseOfTemplate<::xrn::ecs::component::AComponent, Type>::value;

} // namespace xrn::ecs::detail::constraint
