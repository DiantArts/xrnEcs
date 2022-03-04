#pragma once

namespace xrn::ecs::component::detail {



template <
    ::xrn::ecs::detail::constraint::isComponent... RestComponentTypes
> class PushMany;



template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType,
    ::xrn::ecs::detail::constraint::isComponent... RestComponentTypes
> class PushMany<ComponentType, RestComponentTypes...>{

public:

    static void use(
        ::xrn::ecs::component::Container& components,
        ::xrn::Id entityId,
        ComponentType&& componentsArgs,
        RestComponentTypes&&... restComponentsArgs
    )
    {
        components.push<ComponentType>(entityId, ::std::move(componentsArgs));
        ::xrn::ecs::component::detail::PushMany<RestComponentTypes...>::use(
            components,
            entityId,
            ::std::forward<RestComponentTypes>(restComponentsArgs)...
        );
    }
};



template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> class PushMany<ComponentType>{

public:

    static void use(
        ::xrn::ecs::component::Container& components,
        ::xrn::Id entityId,
        ComponentType&& componentsArgs
    )
    {
        components.push<ComponentType>(entityId, ::std::forward<decltype(componentsArgs)>(componentsArgs));
    }
};



} // namespace xrn::ecs::component::detail
