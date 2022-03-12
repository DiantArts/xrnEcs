#pragma once

// ------------------------------------------------------------------ Constructors

template <
    auto func
> ::xrn::ecs::system::System<func>::System() = default;



// ------------------------------------------------------------------ Run

template <
    auto func
> void ::xrn::ecs::system::System<func>::operator()(
    ::xrn::Time t,
    ::xrn::ecs::entity::Container& entities,
    ::xrn::ecs::component::Container& components
)
{
    auto isMatching{ [](const ::xrn::ecs::Entity& entity) {
        return entity.getSignature().contains(::xrn::ecs::system::System<func>::getSignature());
    } };

    for (auto& entity : entities |::std::views::filter(isMatching)) {
        // get every args into a tupple
        using TupleType = ::xrn::ecs::detail::meta::Function<decltype(func)>::Arguments::Type;
        auto args{
            ::xrn::ecs::system::detail::TupleHelper<func, TupleType>::fill(t, components, entity)
        };

        // exec the func
        ::std::apply(func, args);
    }
}

template <
    auto func
> void ::xrn::ecs::system::System<func>::operator()(
    ::xrn::Time t,
    ::xrn::ecs::component::Container& components,
    ::xrn::ecs::entity::Container& entities
)
{
    this->operator()(t, entities, components);
}



template <
    auto func
> void ::xrn::ecs::system::System<func>::operator()(
    ::xrn::Time t,
    const ::xrn::ecs::entity::Container& entities,
    const ::xrn::ecs::component::Container& components
) const
{
    auto isMatching{ [](const ::xrn::ecs::Entity& entity) {
        return entity.getSignature().contains(::xrn::ecs::system::System<func>::getSignature());
    } };

    if constexpr (::xrn::ecs::detail::meta::Function<decltype(func)>::Arguments::areConst) {
        for (auto& entity : entities |::std::views::filter(isMatching)) {
            // get every args into a tupple
            using TupleType = ::xrn::ecs::detail::meta::Function<decltype(func)>::Arguments::Type;
            auto args{
                ::xrn::ecs::system::detail::TupleHelper<func, TupleType>::fill(t, components, entity)
            };

            // exec the func
            ::std::apply(func, args);
        }
    } else {
        throw ::std::runtime_error{ "System called as const but doesn't contain const argments" };
    }
}

template <
    auto func
> void ::xrn::ecs::system::System<func>::operator()(
    ::xrn::Time t,
    const ::xrn::ecs::component::Container& components,
    const ::xrn::ecs::entity::Container& entities
) const
{
    this->operator()(t, entities, components);
}



// ------------------------------------------------------------------ Signature

template <
    auto func
> constexpr auto ::xrn::ecs::system::System<func>::getSignature()
    -> const ::xrn::ecs::Signature&
{
    return ::xrn::ecs::detail::meta::Function<decltype(func)>::Arguments::signature;
}



// ---------------------------------------------------------------------------- Banished

// ------------------------------------------------------------------ Constructors

template <
    auto func,
    ::xrn::ecs::detail::constraint::isComponent... BanishedComponentTypes
> ::xrn::ecs::system::System<func, BanishedComponentTypes...>::System()
{
    static_assert(
        !::xrn::ecs::system::System<
            func,
            BanishedComponentTypes...
        >::getSignature().containsAny(::xrn::ecs::system::System<
            func,
            BanishedComponentTypes...
        >::getBanishedSignature()),
        "System signature contains a banished component"
    );
};



// ------------------------------------------------------------------ Run

template <
    auto func,
    ::xrn::ecs::detail::constraint::isComponent... BanishedComponentTypes
> void ::xrn::ecs::system::System<func, BanishedComponentTypes...>::operator()(
    ::xrn::Time t,
    ::xrn::ecs::entity::Container& entities,
    ::xrn::ecs::component::Container& components
)
{
    auto isMatching{ [](const ::xrn::ecs::Entity& entity) {
        auto& signature{ entity.getSignature() };
        return signature.contains(
                ::xrn::ecs::system::System<func, BanishedComponentTypes...>::getSignature()
            ) &&
            !signature.containsAny(
                ::xrn::ecs::system::System<func, BanishedComponentTypes...>::getBanishedSignature()
            );
    } };

    for (auto& entity : entities |::std::views::filter(isMatching)) {
        // get every args into a tupple
        using TupleType = ::xrn::ecs::detail::meta::Function<decltype(func)>::Arguments::Type;
        auto args{
            ::xrn::ecs::system::detail::TupleHelper<func, TupleType>::fill(t, components, entity)
        };

        // exec the func
        ::std::apply(func, args);
    }
}

template <
    auto func,
    ::xrn::ecs::detail::constraint::isComponent... BanishedComponentTypes
> void ::xrn::ecs::system::System<func, BanishedComponentTypes...>::operator()(
    ::xrn::Time t,
    ::xrn::ecs::component::Container& components,
    ::xrn::ecs::entity::Container& entities
)
{
    this->operator()(t, entities, components);
}



template <
    auto func,
    ::xrn::ecs::detail::constraint::isComponent... BanishedComponentTypes
> void ::xrn::ecs::system::System<func, BanishedComponentTypes...>::operator()(
    ::xrn::Time t,
    const ::xrn::ecs::entity::Container& entities,
    const ::xrn::ecs::component::Container& components
) const
{
    auto isMatching{ [](const ::xrn::ecs::Entity& entity) {
        auto& signature{ entity.getSignature() };
        return signature.contains(
                ::xrn::ecs::system::System<func, BanishedComponentTypes...>::getSignature()
            ) &&
            !signature.containsAny(
                ::xrn::ecs::system::System<func, BanishedComponentTypes...>::getBanishedSignature()
            );
    } };

    if constexpr (::xrn::ecs::detail::meta::Function<decltype(func)>::Arguments::areConst) {
        for (auto& entity : entities |::std::views::filter(isMatching)) {
            // get every args into a tupple
            using TupleType = ::xrn::ecs::detail::meta::Function<decltype(func)>::Arguments::Type;
            auto args{
                ::xrn::ecs::system::detail::TupleHelper<func, TupleType>::fill(t, components, entity)
            };

            // exec the func
            ::std::apply(func, args);
        }
    } else {
        throw ::std::runtime_error{ "System (with banished types) called as const but doesn't contain const argments" };
    }
}

template <
    auto func,
    ::xrn::ecs::detail::constraint::isComponent... BanishedComponentTypes
> void ::xrn::ecs::system::System<func, BanishedComponentTypes...>::operator()(
    ::xrn::Time t,
    const ::xrn::ecs::component::Container& components,
    const ::xrn::ecs::entity::Container& entities
) const
{
    this->operator()(t, entities, components);
}



// ------------------------------------------------------------------ Signature

template <
    auto func,
    ::xrn::ecs::detail::constraint::isComponent... BanishedComponentTypes
> constexpr auto ::xrn::ecs::system::System<func, BanishedComponentTypes...>::getSignature()
    -> const ::xrn::ecs::Signature&
{
    return ::xrn::ecs::detail::meta::Function<decltype(func)>::Arguments::signature;
}

template <
    auto func,
    ::xrn::ecs::detail::constraint::isComponent... BanishedComponentTypes
> constexpr auto ::xrn::ecs::system::System<func, BanishedComponentTypes...>::getBanishedSignature()
    -> const ::xrn::ecs::Signature&
{
    return m_banishedSignature;
}
