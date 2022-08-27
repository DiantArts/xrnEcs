#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs/Signature.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Details
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

namespace {

template <
    ::std::size_t index,
    typename ComponentType,
    typename... ComponentTypes
> struct HelperGetInTemplatePack
    : HelperGetInTemplatePack<index - 1, ComponentTypes...>
{};

template <
    typename ComponentType,
    typename... ComponentTypes
> struct HelperGetInTemplatePack<0, ComponentType, ComponentTypes...>
{
    using Type = ComponentType;
};

} // namespace



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Components
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    auto func,
    ::xrn::Id::Type componentIndex
> constexpr void ::xrn::ecs::detail::ForEach<ComponentTypes...>::findId(
    ::xrn::Id::Type index,
    auto&&... args
)
{
    if constexpr (componentIndex < sizeof...(ComponentTypes)) {
        if (componentIndex == index) {
            return func.template operator()<typename HelperGetInTemplatePack<componentIndex, ComponentTypes...>::Type>(
                ::std::forward<decltype(args)>(args)...
            );
        }
        ForEach::findId<func, componentIndex + 1>(index, ::std::forward<decltype(args)>(args)...);
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    auto func,
    ::xrn::Id::Type componentIndex
> constexpr void ::xrn::ecs::detail::ForEach<ComponentTypes...>::run(
    auto&&... args
)
{
    if constexpr (componentIndex < sizeof...(ComponentTypes)) {
        return func.template operator()<typename HelperGetInTemplatePack<componentIndex, ComponentTypes...>::Type>(
            ::std::forward<decltype(args)>(args)...
        );
        ForEach::run<func, componentIndex + 1>(::std::forward<decltype(args)>(args)...);
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    auto func,
    ::xrn::Id::Type componentIndex
> constexpr void ::xrn::ecs::detail::ForEach<ComponentTypes...>::runIfSignature(
    const ::xrn::ecs::Signature<ComponentTypes...>& signature,
    auto&&... args
)
{
    if constexpr (componentIndex < sizeof...(ComponentTypes)) {
        if (signature.contains(componentIndex)) {
            return func.template operator()<typename HelperGetInTemplatePack<componentIndex, ComponentTypes...>::Type>(
                ::std::forward<decltype(args)>(args)...
            );
        }
        ForEach::runIfSignature<func, componentIndex + 1>(signature, ::std::forward<decltype(args)>(args)...);
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    auto func,
    ::xrn::Id::Type componentIndex
> constexpr void ::xrn::ecs::detail::ForEach<ComponentTypes...>::runWithId(
    auto&&... args
)
{
    if constexpr (componentIndex < sizeof...(ComponentTypes)) {
        return func.template operator()<typename HelperGetInTemplatePack<componentIndex, ComponentTypes...>::Type>(
            componentIndex,
            ::std::forward<decltype(args)>(args)...
        );
        ForEach::runWithId<func, componentIndex + 1>(::std::forward<decltype(args)>(args)...);
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    auto func,
    ::xrn::Id::Type componentIndex
> constexpr void ::xrn::ecs::detail::ForEach<ComponentTypes...>::runWithId(
    const ::xrn::ecs::Signature<ComponentTypes...>& signature,
    auto&&... args
)
{
    if constexpr (componentIndex < sizeof...(ComponentTypes)) {
        if (signature.contains(componentIndex)) {
            return func.template operator()<typename HelperGetInTemplatePack<componentIndex, ComponentTypes...>::Type>(
                componentIndex,
                ::std::forward<decltype(args)>(args)...
            );
        }
        ForEach::runWithId<func, componentIndex + 1>(signature, ::std::forward<decltype(args)>(args)...);
    }
}
