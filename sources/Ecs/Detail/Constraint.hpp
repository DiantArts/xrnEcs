#pragma once

#include <Meta/Constraint.hpp>
#include <Meta/IsBaseOfTemplate.hpp>
#include <Util/Time.hpp>


namespace xrn::ecs::entity { class Entity; }
namespace xrn::ecs::component { template <typename T> class AComponent; }



namespace xrn::ecs::detail::constraint {



template <
    typename Type
> concept isEntity =
    ::xrn::meta::constraint::sameAs<::xrn::ecs::entity::Entity, Type>;

template <
    typename Type
> concept isComponent =
    ::xrn::meta::IsBaseOfTemplate<::xrn::ecs::component::AComponent, Type>::value;

template <
    typename Type
> concept isTime =
    ::xrn::meta::constraint::sameAs<::xrn::Time, Type>;





} // namespace xrn::ecs::detail::constraint
