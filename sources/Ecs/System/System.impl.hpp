#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    auto func,
    typename... Types
> constexpr ::xrn::ecs::system::System<func, Types...>::System() = default;



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Run
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    auto func,
    typename... Types
> constexpr void ::xrn::ecs::system::System<func, Types...>::operator()(
    ::xrn::Time deltaTime,
    ::xrn::ecs::entity::Container& entities
)
{
    auto isMatching{ [](const ::xrn::ecs::Entity& entity) {
        return entity.getSignature().contains(::xrn::ecs::system::System<func, Types...>::getSignature());
    } };

    for (auto& entity : entities | ::std::views::filter(isMatching)) {
        // get every args into a tupple
        using TupleType = ::xrn::ecs::detail::meta::Function<decltype(func)>::Arguments::Type;
        auto args{ ::xrn::ecs::system::detail::SystemFiller<TupleType>::fill(
            deltaTime, entities.getComponentContainer(), entity
        ) };

        // exec the func
        ::std::apply(func, args);
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    auto func,
    typename... Types
> constexpr void ::xrn::ecs::system::System<func, Types...>::operator()(
    ::xrn::Time deltaTime,
    const ::xrn::ecs::entity::Container& entities
) const
{
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
            auto args{ ::xrn::ecs::system::detail::SystemFiller<TupleType>::fill(
                deltaTime, entities.getComponentContainer(), entity
            ) };

            // exec the func
            ::std::apply(func, args);
        }
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Others
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    auto func,
    typename... Types
> consteval auto ::xrn::ecs::system::System<func, Types...>::getSignature()
    -> ::xrn::ecs::Signature
{
    return ::xrn::ecs::detail::meta::Function<decltype(func)>::Arguments::signature;
}
