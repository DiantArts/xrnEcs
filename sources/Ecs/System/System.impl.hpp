#pragma once

// ------------------------------------------------------------------ Constructors

template <
    auto func,
    typename... Types
> constexpr ::xrn::ecs::system::System<func, Types...>::System() = default;



// ------------------------------------------------------------------ Run

template <
    auto func,
    typename... Types
> constexpr void ::xrn::ecs::system::System<func, Types...>::operator()(
    ::xrn::Time t,
    ::xrn::ecs::entity::Container& entities,
    ::xrn::ecs::component::Container& components
)
{
    // static_assert(
        // !::xrn::ecs::system::System<
            // func,
            // BanishedComponentTypes...
        // >::getSignature().containsAny(::xrn::ecs::system::System<
            // func,
            // BanishedComponentTypes...
        // >::getBanishedSignature()),
        // "System signature contains a banished component"
    // );

    auto isMatching{ [](const ::xrn::ecs::Entity& entity) {
        return entity.getSignature().contains(::xrn::ecs::system::System<func, Types...>::getSignature());
    } };

    for (auto& entity : entities | ::std::views::filter(isMatching)) {
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
    typename... Types
> constexpr void ::xrn::ecs::system::System<func, Types...>::operator()(
    ::xrn::Time t,
    ::xrn::ecs::component::Container& components,
    ::xrn::ecs::entity::Container& entities
)
{
    this->operator()(t, entities, components);
}



template <
    auto func,
    typename... Types
> constexpr void ::xrn::ecs::system::System<func, Types...>::operator()(
    ::xrn::Time t,
    const ::xrn::ecs::entity::Container& entities,
    const ::xrn::ecs::component::Container& components
) const
{
    // static_assert(
        // !::xrn::ecs::system::System<
            // func,
            // BanishedComponentTypes...
        // >::getSignature().containsAny(::xrn::ecs::system::System<
            // func,
            // BanishedComponentTypes...
        // >::getBanishedSignature()),
        // "System signature contains a banished component"
    // );

    if constexpr (!::xrn::ecs::detail::meta::Function<decltype(func)>::Arguments::areConst) {
        ::std::cerr
            << "System called as const but doesn't contain const argments"
            << ::std::endl;
    } else {
        auto isMatching{ [](const ::xrn::ecs::Entity& entity) {
            return entity.getSignature().contains(::xrn::ecs::system::System<func, Types...>::getSignature());
        } };

        for (auto& entity : entities | ::std::views::filter(isMatching)) {
            // get every args into a tupple
            using TupleType = ::xrn::ecs::detail::meta::Function<decltype(func)>::Arguments::Type;
            auto args{
                ::xrn::ecs::system::detail::TupleHelper<func, TupleType>::fill(t, components, entity)
            };

            // exec the func
            ::std::apply(func, args);
        }
    }
}

template <
    auto func,
    typename... Types
> constexpr void ::xrn::ecs::system::System<func, Types...>::operator()(
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
    typename... Types
> consteval auto ::xrn::ecs::system::System<func, Types...>::getSignature()
    -> ::xrn::ecs::Signature
{
    return ::xrn::ecs::detail::meta::Function<decltype(func)>::Arguments::signature;
}
