#pragma once

namespace xrn::ecs::system::detail {

///////////////////////////////////////////////////////////////////////////
/// \internal
/// \brief Helps with filling the systems with the correct arguments
/// \ingroup ecs-system
///
/// \include SystemFiller.hpp <xrn/Ecs/System/Detail/SystemFiller.hpp>
///
/// Helper class. It helps by filling systems with the correct arguments
/// acording to the type of the function system carry.
///
/// Usage example:
/// \code
/// using TupleType = ::xrn::ecs::detail::meta::Function<decltype(function)>::Arguments::Type;
/// auto args{ ::xrn::ecs::system::detail::SystemFiller<TupleType>::fill(
///     deltaTime, entities.getComponentContainer(), entity
/// ) };
/// \endcode
///
/// \see ::xrn::ecs::system::ASystem, ::xrn::ecs::system::Container,
///      ::xrn::ecs::entity::Container
///
///////////////////////////////////////////////////////////////////////////
template <
    typename T
> struct SystemFiller;

} // namespace xrn::ecs::system



///////////////////////////////////////////////////////////////////////////
// Header-implimentation
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs/System/Detail/SystemFiller.impl.hpp>
