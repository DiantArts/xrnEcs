#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Meta/Constraint.hpp>
#include <Meta/IsBaseOfTemplate.hpp>
#include <Util/Time.hpp>
#include <Ecs/Component/Detail/Declaration.hpp>

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

// template <
    // typename ComponentType,
    // ::xrn::Id::Type componentIndex = 0
// > consteval auto find()
    // -> bool
// {
    // if constexpr (componentIndex < xrn::ecs::component::maxId) {
        // if (::xrn::meta::constraint::sameAs<
            // typename ::xrn::ecs::component::IdInfo<componentIndex>::Type,
            // ComponentType
        // >) {
            // return true;
        // }
        // return find<func, componentIndex + 1>(
            // signature,
            // ::std::forward<decltype(args)>(args)...
        // );
    // }
    // return false
    // return ::xrn::meta::constraint::sameAs<
        // typename ::xrn::ecs::component::IdInfo<componentIndex>::Type,
        // ComponentType
    // > || find<componentType;
// }

template <
    typename Type
> concept isComponent =
    ::xrn::ecs::IsComponent<Type>::value;
    // ::xrn::meta::IsBaseOfTemplate<::xrn::ecs::component::AComponent, Type>::value;
    // ::xrn::ecs::IsComponent<Type>::value ||
    // ::xrn::meta::constraint::sameAs<::xrn::ecs::component::AComponent, Type>;
    // true;
    // ::xrn::ecs::component::ForEach::find<Type>();
    // ::xrn::meta::constraint::sameAs<xrn::ecs::component::IdInfo<Type::getId()>::Type, Type>;

} // namespace xrn::ecs::detail::constraint
