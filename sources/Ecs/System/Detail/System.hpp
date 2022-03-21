#pragma once

#include <Meta/UniqueTypes.hpp>

namespace xrn::ecs::system::detail {



template <
    auto func,
    typename T
> struct TupleHelper
{};

template <
    auto func,
    typename... Types
> requires
    ((
        ::xrn::ecs::detail::constraint::isComponent<Types> ||
        ::xrn::ecs::detail::constraint::isAbility<Types>
    ) && ...) &&
    ::xrn::meta::UniqueTypes<Types...>::value
struct TupleHelper<
    func,
    ::std::tuple<Types...>
> {
    static inline constexpr auto fill(
        ::xrn::Time t,
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



template <
    auto func,
    typename... Types
> requires
    ((
        ::xrn::ecs::detail::constraint::isComponent<Types> ||
        ::xrn::ecs::detail::constraint::isAbility<Types>
    ) && ...) &&
    ::xrn::meta::UniqueTypes<Types...>::value
struct TupleHelper<
    func,
    ::std::tuple<const ::xrn::ecs::Entity&, Types...>
> {
    static inline constexpr auto fill(
        ::xrn::Time,
        ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::Entity& entity
    ) -> ::std::tuple<const ::xrn::ecs::Entity&, Types...>
    {
        return { entity, *components.get<Types>(entity.getId()) ... };
    }

    static inline constexpr auto fill(
        ::xrn::Time,
        const ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::Entity& entity
    ) -> ::std::tuple<const ::xrn::ecs::Entity&, Types...>
    {
        return { entity, *components.get<Types>(entity.getId()) ... };
    }
};

template <
    auto func,
    typename... Types
> requires
    ((
        ::xrn::ecs::detail::constraint::isComponent<Types> ||
        ::xrn::ecs::detail::constraint::isAbility<Types>
    ) && ...) &&
    ::xrn::meta::UniqueTypes<Types...>::value
struct TupleHelper<
    func,
    ::std::tuple<::xrn::ecs::Entity&, Types...>
> {
    static inline constexpr auto fill(
        ::xrn::Time,
        ::xrn::ecs::component::Container& components,
        ::xrn::ecs::Entity& entity
    ) -> ::std::tuple<::xrn::ecs::Entity&, Types...>
    {
        return { entity, *components.get<Types>(entity.getId()) ... };
    }

    static inline constexpr auto fill(
        ::xrn::Time,
        const ::xrn::ecs::component::Container& components,
        ::xrn::ecs::Entity& entity
    ) -> ::std::tuple<::xrn::ecs::Entity&, Types...>
    {
        return { entity, *components.get<Types>(entity.getId()) ... };
    }
};




template <
    auto func,
    typename... Types
> requires
    ((
        ::xrn::ecs::detail::constraint::isComponent<Types> ||
        ::xrn::ecs::detail::constraint::isAbility<Types>
    ) && ...) &&
    ::xrn::meta::UniqueTypes<Types...>::value
struct TupleHelper<
    func,
    ::std::tuple<::xrn::Time, Types...>
> {
    static inline constexpr auto fill(
        ::xrn::Time t,
        ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::Entity& entity
    ) -> ::std::tuple<::xrn::Time, Types...>
    {
        return { t, *components.get<Types>(entity.getId()) ... };
    }

    static inline constexpr auto fill(
        ::xrn::Time t,
        const ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::Entity& entity
    ) -> ::std::tuple<::xrn::Time, Types...>
    {
        return { t, *components.get<Types>(entity.getId()) ... };
    }
};

template <
    auto func,
    typename... Types
> requires
    ((
        ::xrn::ecs::detail::constraint::isComponent<Types> ||
        ::xrn::ecs::detail::constraint::isAbility<Types>
    ) && ...) &&
    ::xrn::meta::UniqueTypes<Types...>::value
struct TupleHelper<
    func,
    ::std::tuple<::xrn::Time, const ::xrn::ecs::Entity&, Types...>
> {
    static inline constexpr auto fill(
        ::xrn::Time t,
        ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::Entity& entity
    ) -> ::std::tuple<::xrn::Time, const ::xrn::ecs::Entity&, Types...>
    {
        return { t, entity, *components.get<Types>(entity.getId()) ... };
    }

    static inline constexpr auto fill(
        ::xrn::Time t,
        const ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::Entity& entity
    ) -> ::std::tuple<::xrn::Time, const ::xrn::ecs::Entity&, Types...>
    {
        return { t, entity, *components.get<Types>(entity.getId()) ... };
    }
};

template <
    auto func,
    typename... Types
> requires
    ((
        ::xrn::ecs::detail::constraint::isComponent<Types> ||
        ::xrn::ecs::detail::constraint::isAbility<Types>
    ) && ...) &&
    ::xrn::meta::UniqueTypes<Types...>::value
struct TupleHelper<
    func,
    ::std::tuple<::xrn::Time, ::xrn::ecs::Entity&, Types...>
> {
    static inline constexpr auto fill(
        ::xrn::Time t,
        ::xrn::ecs::component::Container& components,
        ::xrn::ecs::Entity& entity
    ) -> ::std::tuple<::xrn::Time, ::xrn::ecs::Entity&, Types...>
    {
        return { t, entity, *components.get<Types>(entity.getId()) ... };
    }

    static inline constexpr auto fill(
        ::xrn::Time t,
        const ::xrn::ecs::component::Container& components,
        ::xrn::ecs::Entity& entity
    ) -> ::std::tuple<::xrn::Time, ::xrn::ecs::Entity&, Types...>
    {
        return { t, entity, *components.get<Types>(entity.getId()) ... };
    }
};



template <
    auto func,
    typename... Types
> requires
    ((
        ::xrn::ecs::detail::constraint::isComponent<Types> ||
        ::xrn::ecs::detail::constraint::isAbility<Types>
    ) && ...) &&
    ::xrn::meta::UniqueTypes<Types...>::value
struct TupleHelper<
    func,
    ::std::tuple<const ::xrn::ecs::Entity&, ::xrn::Time, Types...>
> {
    static inline constexpr auto fill(
        ::xrn::Time t,
        ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::Entity& entity
    ) -> ::std::tuple<const ::xrn::ecs::Entity&, ::xrn::Time, Types...>
    {
        return { entity, t, *components.get<Types>(entity.getId()) ... };
    }

    static inline constexpr auto fill(
        ::xrn::Time t,
        const ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::Entity& entity
    ) -> ::std::tuple<const ::xrn::ecs::Entity&, ::xrn::Time, Types...>
    {
        return { entity, t, *components.get<Types>(entity.getId()) ... };
    }
};

template <
    auto func,
    typename... Types
> requires
    ((
        ::xrn::ecs::detail::constraint::isComponent<Types> ||
        ::xrn::ecs::detail::constraint::isAbility<Types>
    ) && ...) &&
    ::xrn::meta::UniqueTypes<Types...>::value
struct TupleHelper<
    func,
    ::std::tuple<::xrn::ecs::Entity&, ::xrn::Time, Types...>
> {
    static inline constexpr auto fill(
        ::xrn::Time t,
        ::xrn::ecs::component::Container& components,
        ::xrn::ecs::Entity& entity
    ) -> ::std::tuple<::xrn::ecs::Entity&, ::xrn::Time, Types...>
    {
        return { entity, t, *components.get<Types>(entity.getId()) ... };
    }

    static inline constexpr auto fill(
        ::xrn::Time t,
        const ::xrn::ecs::component::Container& components,
        ::xrn::ecs::Entity& entity
    ) -> ::std::tuple<::xrn::ecs::Entity&, ::xrn::Time, Types...>
    {
        return { entity, t, *components.get<Types>(entity.getId()) ... };
    }
};




} // namespace xrn::ecs::system
