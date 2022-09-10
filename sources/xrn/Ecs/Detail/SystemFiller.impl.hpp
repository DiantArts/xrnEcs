#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Meta/UniqueTypes.hpp>
#include <xrn/Ecs/Detail/Constraint.hpp>



namespace xrn::ecs::system::detail {

///////////////////////////////////////////////////////////////////////////
/// \internal
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
    typename... Types
> requires
    ::xrn::meta::UniqueTypes<Types...>::value
struct SystemFiller<
    ::std::tuple<Types...>
> {
    template <
        typename... ComponentTypes
    > static inline constexpr auto fill(
        ::xrn::Time,
        ::xrn::ecs::Registry<ComponentTypes...>& registry,
        ::xrn::ecs::Entity entity
    ) -> ::std::tuple<Types...>
    {
        return { registry.template get<Types>(entity).unsafeGet() ... };
    }

    template <
        typename... ComponentTypes
    > static inline constexpr auto fill(
        ::xrn::Time,
        const ::xrn::ecs::Registry<ComponentTypes...>& registry,
        ::xrn::ecs::Entity entity
    ) -> ::std::tuple<Types...>
    {
        return { registry.template get<Types>(entity).unsafeGet() ... };
    }
};



///////////////////////////////////////////////////////////////////////////
/// \internal
/// \brief Helps with filling the systems with the correct arguments
///
/// Fills the following arguments:
///     - Entity
///     - Components
///
/// \see ::xrn::ecs::Entity
///
///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> requires
    ::xrn::meta::UniqueTypes<Types...>::value
struct SystemFiller<
    ::std::tuple<::xrn::ecs::Entity, Types...>
> {
    template <
        typename... ComponentTypes
    > static inline constexpr auto fill(
        ::xrn::Time,
        ::xrn::ecs::Registry<ComponentTypes...>& registry,
        ::xrn::ecs::Entity entity
    ) -> ::std::tuple<Entity, Types...>
    {
        return { entity, registry.template get<Types>(entity).unsafeGet() ... };
    }

    template <
        typename... ComponentTypes
    > static inline constexpr auto fill(
        ::xrn::Time,
        const ::xrn::ecs::Registry<ComponentTypes...>& registry,
        ::xrn::ecs::Entity entity
    ) -> ::std::tuple<Entity, Types...>
    {
        return { entity, registry.template get<Types>(entity).unsafeGet() ... };
    }
};



///////////////////////////////////////////////////////////////////////////
/// \internal
/// \brief Helps with filling the systems with the correct arguments
///
/// Fills the following arguments:
///     - Time
///     - Components
///
/// \see ::xrn::util::BasicTime, ::xrn::ecs::Entity
///
///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> requires
    ::xrn::meta::UniqueTypes<Types...>::value
struct SystemFiller<
    ::std::tuple<::xrn::Time, Types...>
> {
    template <
        typename... ComponentTypes
    > static inline constexpr auto fill(
        ::xrn::Time t,
        ::xrn::ecs::Registry<ComponentTypes...>& registry,
        ::xrn::ecs::Entity entity
    ) -> ::std::tuple<Time, Types...>
    {
        return { t, registry.template get<Types>(entity).unsafeGet() ... };
    }

    template <
        typename... ComponentTypes
    > static inline constexpr auto fill(
        ::xrn::Time t,
        const ::xrn::ecs::Registry<ComponentTypes...>& registry,
        ::xrn::ecs::Entity entity
    ) -> ::std::tuple<Time, Types...>
    {
        return { t, registry.template get<Types>(entity).unsafeGet() ... };
    }
};



///////////////////////////////////////////////////////////////////////////
/// \internal
/// \brief Helps with filling the systems with the correct arguments
///
/// Fills the following arguments:
///     - Time
///     - Entity
///     - Components
///
/// \see ::xrn::util::BasicTime, ::xrn::ecs::Entity
///
///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> requires
    ::xrn::meta::UniqueTypes<Types...>::value
struct SystemFiller<
    ::std::tuple<::xrn::Time, ::xrn::ecs::Entity, Types...>
> {
    template <
        typename... ComponentTypes
    > static inline constexpr auto fill(
        ::xrn::Time t,
        ::xrn::ecs::Registry<ComponentTypes...>& registry,
        ::xrn::ecs::Entity entity
    ) -> ::std::tuple<Time, Entity, Types...>
    {
        return { t, entity, registry.template get<Types>(entity).unsafeGet() ... };
    }

    template <
        typename... ComponentTypes
    > static inline constexpr auto fill(
        ::xrn::Time t,
        const ::xrn::ecs::Registry<ComponentTypes...>& registry,
        ::xrn::ecs::Entity entity
    ) -> ::std::tuple<Time, Entity, Types...>
    {
        return { t, entity, registry.template get<Types>(entity).unsafeGet() ... };
    }
};



///////////////////////////////////////////////////////////////////////////
/// \internal
/// \brief Helps with filling the systems with the correct arguments
///
/// Fills the following arguments:
///     - Entity
///     - Time
///     - Components
///
/// \see ::xrn::util::BasicTime, ::xrn::ecs::Entity
///
///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> requires
    ::xrn::meta::UniqueTypes<Types...>::value
struct SystemFiller<
    ::std::tuple<::xrn::ecs::Entity, ::xrn::Time, Types...>
> {
    template <
        typename... ComponentTypes
    > static inline constexpr auto fill(
        ::xrn::Time t,
        ::xrn::ecs::Registry<ComponentTypes...>& registry,
        ::xrn::ecs::Entity entity
    ) -> ::std::tuple<Entity, Time, Types...>
    {
        return { entity, t, registry.template get<Types>(entity).unsafeGet() ... };
    }

    template <
        typename... ComponentTypes
    > static inline constexpr auto fill(
        ::xrn::Time t,
        const ::xrn::ecs::Registry<ComponentTypes...>& registry,
        ::xrn::ecs::Entity entity
    ) -> ::std::tuple<Entity, Time, Types...>
    {
        return { entity, t, registry.template get<Types>(entity).unsafeGet() ... };
    }
};

} // namespace xrn::ecs::system
