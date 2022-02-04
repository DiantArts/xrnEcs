#pragma once

namespace xrn::ecs::system::detail {



template <
    auto func,
    typename
> struct TupleHelper;

template <
    auto func,
    ::xrn::ecs::component::ConceptType... ComponentTypes
> requires
    ::xrn::meta::UniqueTypes<ComponentTypes...>::value
struct TupleHelper<
    func,
    ::std::tuple<ComponentTypes...>
> {
    static inline constexpr auto fill(
        ::xrn::ecs::Time t,
        ::xrn::ecs::component::Container& components,
        ::xrn::ecs::Entity& entity
    )
        -> ::std::tuple<ComponentTypes...>
    {
        return { components.get<ComponentTypes>(entity.getId()) ... };
    }

    static inline constexpr auto fill(
        ::xrn::ecs::Time,
        const ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::Entity& entity
    )
        -> ::std::tuple<ComponentTypes...>
    {
        return { components.get<ComponentTypes>(entity.getId()) ... };
    }
};



template <
    auto func,
    ::xrn::ecs::component::ConceptType... ComponentTypes
> requires
    ::xrn::meta::UniqueTypes<ComponentTypes...>::value
struct TupleHelper<
    func,
    ::std::tuple<const ::xrn::ecs::Entity&, ComponentTypes...>
> {
    static inline constexpr auto fill(
        ::xrn::ecs::Time,
        ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::Entity& entity
    )
        -> ::std::tuple<const ::xrn::ecs::Entity&, ComponentTypes...>
    {
        return { entity, components.get<ComponentTypes>(entity.getId()) ... };
    }

    static inline constexpr auto fill(
        ::xrn::ecs::Time,
        const ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::Entity& entity
    )
        -> ::std::tuple<const ::xrn::ecs::Entity&, ComponentTypes...>
    {
        return { entity, components.get<ComponentTypes>(entity.getId()) ... };
    }
};

template <
    auto func,
    ::xrn::ecs::component::ConceptType... ComponentTypes
> requires
    ::xrn::meta::UniqueTypes<ComponentTypes...>::value
struct TupleHelper<
    func,
    ::std::tuple<::xrn::ecs::Entity&, ComponentTypes...>
> {
    static inline constexpr auto fill(
        ::xrn::ecs::Time,
        ::xrn::ecs::component::Container& components,
        ::xrn::ecs::Entity& entity
    )
        -> ::std::tuple<::xrn::ecs::Entity&, ComponentTypes...>
    {
        return { entity, components.get<ComponentTypes>(entity.getId()) ... };
    }

    static inline constexpr auto fill(
        ::xrn::ecs::Time,
        const ::xrn::ecs::component::Container& components,
        ::xrn::ecs::Entity& entity
    )
        -> ::std::tuple<::xrn::ecs::Entity&, ComponentTypes...>
    {
        return { entity, components.get<ComponentTypes>(entity.getId()) ... };
    }
};




template <
    auto func,
    ::xrn::ecs::component::ConceptType... ComponentTypes
> requires
    ::xrn::meta::UniqueTypes<ComponentTypes...>::value
struct TupleHelper<
    func,
    ::std::tuple<::xrn::ecs::Time, ComponentTypes...>
> {
    static inline constexpr auto fill(
        ::xrn::ecs::Time t,
        ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::Entity& entity
    )
        -> ::std::tuple<::xrn::ecs::Time, ComponentTypes...>
    {
        return { t, components.get<ComponentTypes>(entity.getId()) ... };
    }

    static inline constexpr auto fill(
        ::xrn::ecs::Time t,
        const ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::Entity& entity
    )
        -> ::std::tuple<::xrn::ecs::Time, ComponentTypes...>
    {
        return { t, components.get<ComponentTypes>(entity.getId()) ... };
    }
};

template <
    auto func,
    ::xrn::ecs::component::ConceptType... ComponentTypes
> requires
    ::xrn::meta::UniqueTypes<ComponentTypes...>::value
struct TupleHelper<
    func,
    ::std::tuple<::xrn::ecs::Time, const ::xrn::ecs::Entity&, ComponentTypes...>
> {
    static inline constexpr auto fill(
        ::xrn::ecs::Time t,
        ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::Entity& entity
    )
        -> ::std::tuple<::xrn::ecs::Time, const ::xrn::ecs::Entity&, ComponentTypes...>
    {
        return { t, entity, components.get<ComponentTypes>(entity.getId()) ... };
    }

    static inline constexpr auto fill(
        ::xrn::ecs::Time t,
        const ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::Entity& entity
    )
        -> ::std::tuple<::xrn::ecs::Time, const ::xrn::ecs::Entity&, ComponentTypes...>
    {
        return { t, entity, components.get<ComponentTypes>(entity.getId()) ... };
    }
};

template <
    auto func,
    ::xrn::ecs::component::ConceptType... ComponentTypes
> requires
    ::xrn::meta::UniqueTypes<ComponentTypes...>::value
struct TupleHelper<
    func,
    ::std::tuple<::xrn::ecs::Time, ::xrn::ecs::Entity&, ComponentTypes...>
> {
    static inline constexpr auto fill(
        ::xrn::ecs::Time t,
        ::xrn::ecs::component::Container& components,
        ::xrn::ecs::Entity& entity
    )
        -> ::std::tuple<::xrn::ecs::Time, ::xrn::ecs::Entity&, ComponentTypes...>
    {
        return { t, entity, components.get<ComponentTypes>(entity.getId()) ... };
    }

    static inline constexpr auto fill(
        ::xrn::ecs::Time t,
        const ::xrn::ecs::component::Container& components,
        ::xrn::ecs::Entity& entity
    )
        -> ::std::tuple<::xrn::ecs::Time, ::xrn::ecs::Entity&, ComponentTypes...>
    {
        return { t, entity, components.get<ComponentTypes>(entity.getId()) ... };
    }
};



template <
    auto func,
    ::xrn::ecs::component::ConceptType... ComponentTypes
> requires
    ::xrn::meta::UniqueTypes<ComponentTypes...>::value
struct TupleHelper<
    func,
    ::std::tuple<const ::xrn::ecs::Entity&, ::xrn::ecs::Time, ComponentTypes...>
> {
    static inline constexpr auto fill(
        ::xrn::ecs::Time t,
        ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::Entity& entity
    )
        -> ::std::tuple<const ::xrn::ecs::Entity&, ::xrn::ecs::Time, ComponentTypes...>
    {
        return { entity, t, components.get<ComponentTypes>(entity.getId()) ... };
    }

    static inline constexpr auto fill(
        ::xrn::ecs::Time t,
        const ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::Entity& entity
    )
        -> ::std::tuple<const ::xrn::ecs::Entity&, ::xrn::ecs::Time, ComponentTypes...>
    {
        return { entity, t, components.get<ComponentTypes>(entity.getId()) ... };
    }
};

template <
    auto func,
    ::xrn::ecs::component::ConceptType... ComponentTypes
> requires
    ::xrn::meta::UniqueTypes<ComponentTypes...>::value
struct TupleHelper<
    func,
    ::std::tuple<::xrn::ecs::Entity&, ::xrn::ecs::Time, ComponentTypes...>
> {
    static inline constexpr auto fill(
        ::xrn::ecs::Time t,
        ::xrn::ecs::component::Container& components,
        ::xrn::ecs::Entity& entity
    )
        -> ::std::tuple<::xrn::ecs::Entity&, ::xrn::ecs::Time, ComponentTypes...>
    {
        return { entity, t, components.get<ComponentTypes>(entity.getId()) ... };
    }

    static inline constexpr auto fill(
        ::xrn::ecs::Time t,
        const ::xrn::ecs::component::Container& components,
        ::xrn::ecs::Entity& entity
    )
        -> ::std::tuple<::xrn::ecs::Entity&, ::xrn::ecs::Time, ComponentTypes...>
    {
        return { entity, t, components.get<ComponentTypes>(entity.getId()) ... };
    }
};




} // namespace xrn::ecs::system
