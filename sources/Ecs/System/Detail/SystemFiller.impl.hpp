#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Meta/UniqueTypes.hpp>
#include <Ecs/Detail/Constraint.hpp>



namespace xrn::ecs::system::detail {

///////////////////////////////////////////////////////////////////////////
/// \brief Helps with filling the systems with the correct arguments
///
/// Fills the following arguments:
///     - Components
///
/// \see ::xrn::ecs::system::ASystem, ::xrn::ecs::system::Container,
///      ::xrn::ecs::entity::Container
///
///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isEcsRegistered... Types
> requires
    ::xrn::meta::UniqueTypes<Types...>::value
struct SystemFiller<
    ::std::tuple<Types...>
> {
    static inline constexpr auto fill(
        ::xrn::Time,
        ::xrn::ecs::component::Container& components,
        ::xrn::ecs::Entity& entity
    ) -> ::std::tuple<Types...>
    {
        return { *components.get<Types>(entity.getId()) ... };
    }

    static inline constexpr auto fill(
        ::xrn::Time,
        const ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::Entity& entity
    ) -> ::std::tuple<Types...>
    {
        return { *components.get<Types>(entity.getId()) ... };
    }
};



///////////////////////////////////////////////////////////////////////////
/// \brief Helps with filling the systems with the correct arguments
///
/// Fills the following arguments:
///     - Entity
///     - Components
///
/// \see ::xrn::ecs::entity::Entity
///
///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isEntity Entity,
    ::xrn::ecs::detail::constraint::isEcsRegistered... Types
> requires
    ::xrn::meta::UniqueTypes<Types...>::value
struct SystemFiller<
    ::std::tuple<Entity, Types...>
> {
    static inline constexpr auto fill(
        ::xrn::Time,
        ::xrn::ecs::component::Container& components,
        Entity& entity
    ) -> ::std::tuple<Entity, Types...>
    {
        return { entity, *components.get<Types>(entity.getId()) ... };
    }

    static inline constexpr auto fill(
        ::xrn::Time,
        const ::xrn::ecs::component::Container& components,
        Entity& entity
    ) -> ::std::tuple<Entity, Types...>
    {
        return { entity, *components.get<Types>(entity.getId()) ... };
    }
};



///////////////////////////////////////////////////////////////////////////
/// \brief Helps with filling the systems with the correct arguments
///
/// Fills the following arguments:
///     - Time
///     - Components
///
/// \see ::xrn::util::Time, ::xrn::ecs::entity::Entity
///
///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isTime Time,
    ::xrn::ecs::detail::constraint::isEcsRegistered... Types
> requires
    ::xrn::meta::UniqueTypes<Types...>::value
struct SystemFiller<
    ::std::tuple<Time, Types...>
> {
    static inline constexpr auto fill(
        ::xrn::Time t,
        ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::Entity& entity
    ) -> ::std::tuple<Time, Types...>
    {
        return { t, *components.get<Types>(entity.getId()) ... };
    }

    static inline constexpr auto fill(
        ::xrn::Time t,
        const ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::Entity& entity
    ) -> ::std::tuple<Time, Types...>
    {
        return { t, *components.get<Types>(entity.getId()) ... };
    }
};



///////////////////////////////////////////////////////////////////////////
/// \brief Helps with filling the systems with the correct arguments
///
/// Fills the following arguments:
///     - Time
///     - Entity
///     - Components
///
/// \see ::xrn::util::Time, ::xrn::ecs::entity::Entity
///
///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isTime Time,
    ::xrn::ecs::detail::constraint::isEntity Entity,
    ::xrn::ecs::detail::constraint::isEcsRegistered... Types
> requires
    ::xrn::meta::UniqueTypes<Types...>::value
struct SystemFiller<
    ::std::tuple<Time, Entity, Types...>
> {
    static inline constexpr auto fill(
        ::xrn::Time t,
        ::xrn::ecs::component::Container& components,
        Entity& entity
    ) -> ::std::tuple<Time, Entity, Types...>
    {
        return { t, entity, *components.get<Types>(entity.getId()) ... };
    }

    static inline constexpr auto fill(
        ::xrn::Time t,
        const ::xrn::ecs::component::Container& components,
        Entity& entity
    ) -> ::std::tuple<Time, Entity, Types...>
    {
        return { t, entity, *components.get<Types>(entity.getId()) ... };
    }
};



///////////////////////////////////////////////////////////////////////////
/// \brief Helps with filling the systems with the correct arguments
///
/// Fills the following arguments:
///     - Entity
///     - Time
///     - Components
///
/// \see ::xrn::util::Time, ::xrn::ecs::entity::Entity
///
///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isTime Time,
    ::xrn::ecs::detail::constraint::isEntity Entity,
    ::xrn::ecs::detail::constraint::isEcsRegistered... Types
> requires
    ::xrn::meta::UniqueTypes<Types...>::value
struct SystemFiller<
    ::std::tuple<Entity, Time, Types...>
> {
    static inline constexpr auto fill(
        ::xrn::Time t,
        ::xrn::ecs::component::Container& components,
        Entity& entity
    ) -> ::std::tuple<Entity, Time, Types...>
    {
        return { entity, t, *components.get<Types>(entity.getId()) ... };
    }

    static inline constexpr auto fill(
        ::xrn::Time t,
        const ::xrn::ecs::component::Container& components,
        Entity& entity
    ) -> ::std::tuple<Entity, Time, Types...>
    {
        return { entity, t, *components.get<Types>(entity.getId()) ... };
    }
};

} // namespace xrn::ecs::system
