#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs/Signature.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Components
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    auto func,
    ::xrn::Id::Type componentIndex
> constexpr void ::xrn::ecs::component::detail::ForEach::find(
    ::xrn::Id::Type id,
    auto&&... args
)
{
    if constexpr (componentIndex < ::xrn::ecs::component::maxId) {
        if constexpr (::xrn::ecs::isComponent<typename ::xrn::ecs::component::IdInfo<componentIndex>::Type>) {
            if (componentIndex == id) {
                return func.template operator()<typename ::xrn::ecs::component::IdInfo<componentIndex>::Type>(
                    ::std::forward<decltype(args)>(args)...
                );
            }
        }
       ::xrn::ecs::component::detail::ForEach::find<func, componentIndex + 1>(
            id, ::std::forward<decltype(args)>(args)...
        );
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    auto func,
    ::xrn::Id::Type componentIndex
> constexpr void ::xrn::ecs::component::detail::ForEach::run(
    auto&&... args
)
{
    if constexpr (componentIndex < ::xrn::ecs::component::maxId) {
        if constexpr (::xrn::ecs::isComponent<typename ::xrn::ecs::component::IdInfo<componentIndex>::Type>) {
            func.template operator()<typename ::xrn::ecs::component::IdInfo<componentIndex>::Type>(
                ::std::forward<decltype(args)>(args)...
            );
        }
       ::xrn::ecs::component::detail::ForEach::run<func, componentIndex + 1>(
            ::std::forward<decltype(args)>(args)...
        );
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    auto func,
    ::xrn::Id::Type componentIndex
> constexpr void ::xrn::ecs::component::detail::ForEach::runIfSignature(
    const ::xrn::ecs::Signature& signature,
    auto&&... args
)
{
    if constexpr (componentIndex < ::xrn::ecs::component::maxId) {
        if constexpr (::xrn::ecs::isComponent<typename ::xrn::ecs::component::IdInfo<componentIndex>::Type>) {
            if (signature.contains(componentIndex)) {
                func.template operator()<typename ::xrn::ecs::component::IdInfo<componentIndex>::Type>(
                    ::std::forward<decltype(args)>(args)...
                );
            }
        }
        ::xrn::ecs::component::detail::ForEach::runIfSignature<func, componentIndex + 1>(
            signature,
            ::std::forward<decltype(args)>(args)...
        );
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    auto func,
    ::xrn::Id::Type componentIndex
> constexpr void ::xrn::ecs::component::detail::ForEach::runWithId(
    auto&&... args
)
{
    if constexpr (componentIndex < ::xrn::ecs::component::maxId) {
        if constexpr (::xrn::ecs::isComponent<typename ::xrn::ecs::component::IdInfo<componentIndex>::Type>) {
            func.template operator()<typename ::xrn::ecs::component::IdInfo<componentIndex>::Type>(
                componentIndex,
                ::std::forward<decltype(args)>(args)...
            );
        }
        ::xrn::ecs::component::detail::ForEach::runWithId<func, componentIndex + 1>(
            ::std::forward<decltype(args)>(args)...
        );
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    auto func,
    ::xrn::Id::Type componentIndex
> constexpr void ::xrn::ecs::component::detail::ForEach::runWithId(
    const ::xrn::ecs::Signature& signature,
    auto&&... args
)
{
    if constexpr (componentIndex < ::xrn::ecs::component::maxId) {
        if constexpr (::xrn::ecs::isComponent<typename ::xrn::ecs::component::IdInfo<componentIndex>::Type>) {
            if (signature.contains(componentIndex)) {
                func.template operator()<typename ::xrn::ecs::component::IdInfo<componentIndex>::Type>(
                    componentIndex,
                    ::std::forward<decltype(args)>(args)...
                );
            }
        }
        ::xrn::ecs::component::detail::ForEach::runWithId<func, componentIndex + 1>(
            signature,
            ::std::forward<decltype(args)>(args)...
        );
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Abilities
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    auto func,
    ::xrn::Id::Type abilityIndex
> constexpr void ::xrn::ecs::ability::detail::ForEach::find(
    ::xrn::Id::Type id,
    auto&&... args
)
{
    if constexpr (abilityIndex < ::xrn::ecs::component::maxId) {
        if constexpr (::xrn::ecs::isAbility<typename ::xrn::ecs::component::IdInfo<abilityIndex>::Type>) {
            if (abilityIndex == id) {
                return func.template operator()<typename ::xrn::ecs::component::IdInfo<abilityIndex>::Type>(
                    ::std::forward<decltype(args)>(args)...
                );
            }
        }
       ::xrn::ecs::ability::detail::ForEach::find<func, abilityIndex + 1>(
            id, ::std::forward<decltype(args)>(args)...
        );
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    auto func,
    ::xrn::Id::Type abilityIndex
> constexpr void ::xrn::ecs::ability::detail::ForEach::run(
    auto&&... args
)
{
    if constexpr (abilityIndex < ::xrn::ecs::component::maxId) {
        if constexpr (::xrn::ecs::isAbility<typename ::xrn::ecs::component::IdInfo<abilityIndex>::Type>) {
            func.template operator()<typename ::xrn::ecs::component::IdInfo<abilityIndex>::Type>(
                ::std::forward<decltype(args)>(args)...
            );
        }
       ::xrn::ecs::ability::detail::ForEach::run<func, abilityIndex + 1>(
            ::std::forward<decltype(args)>(args)...
        );
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    auto func,
    ::xrn::Id::Type abilityIndex
> constexpr void ::xrn::ecs::ability::detail::ForEach::runIfSignature(
    const ::xrn::ecs::Signature& signature,
    auto&&... args
)
{
    if constexpr (abilityIndex < ::xrn::ecs::component::maxId) {
        if constexpr (::xrn::ecs::isAbility<typename ::xrn::ecs::component::IdInfo<abilityIndex>::Type>) {
            if (signature.contains(abilityIndex)) {
                func.template operator()<typename ::xrn::ecs::component::IdInfo<abilityIndex>::Type>(
                    ::std::forward<decltype(args)>(args)...
                );
            }
        }
        ::xrn::ecs::ability::detail::ForEach::runIfSignature<func, abilityIndex + 1>(
            signature,
            ::std::forward<decltype(args)>(args)...
        );
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    auto func,
    ::xrn::Id::Type abilityIndex
> constexpr void ::xrn::ecs::ability::detail::ForEach::runWithId(
    auto&&... args
)
{
    if constexpr (abilityIndex < ::xrn::ecs::component::maxId) {
        if constexpr (::xrn::ecs::isAbility<typename ::xrn::ecs::component::IdInfo<abilityIndex>::Type>) {
            func.template operator()<typename ::xrn::ecs::component::IdInfo<abilityIndex>::Type>(
                abilityIndex,
                ::std::forward<decltype(args)>(args)...
            );
        }
        ::xrn::ecs::ability::detail::ForEach::runWithId<func, abilityIndex + 1>(
            ::std::forward<decltype(args)>(args)...
        );
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    auto func,
    ::xrn::Id::Type abilityIndex
> constexpr void ::xrn::ecs::ability::detail::ForEach::runWithId(
    const ::xrn::ecs::Signature& signature,
    auto&&... args
)
{
    if constexpr (abilityIndex < ::xrn::ecs::component::maxId) {
        if constexpr (::xrn::ecs::isAbility<typename ::xrn::ecs::component::IdInfo<abilityIndex>::Type>) {
            if (signature.contains(abilityIndex)) {
                func.template operator()<typename ::xrn::ecs::component::IdInfo<abilityIndex>::Type>(
                    abilityIndex,
                    ::std::forward<decltype(args)>(args)...
                );
            }
        }
        ::xrn::ecs::ability::detail::ForEach::runWithId<func, abilityIndex + 1>(
            signature,
            ::std::forward<decltype(args)>(args)...
        );
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Components and Abilities
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    auto func,
    ::xrn::Id::Type componentIndex
> constexpr void ::xrn::ecs::detail::ForEach::find(
    ::xrn::Id::Type id,
    auto&&... args
)
{
    if constexpr (componentIndex < ::xrn::ecs::component::maxId) {
        if (componentIndex == id) {
            return func.template operator()<typename ::xrn::ecs::component::IdInfo<componentIndex>::Type>(
                ::std::forward<decltype(args)>(args)...
            );
        }
       ::xrn::ecs::detail::ForEach::find<func, componentIndex + 1>(
            id, ::std::forward<decltype(args)>(args)...
        );
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    auto func,
    ::xrn::Id::Type componentIndex
> constexpr void ::xrn::ecs::detail::ForEach::run(
    auto&&... args
)
{
    if constexpr (componentIndex < ::xrn::ecs::component::maxId) {
        func.template operator()<typename ::xrn::ecs::component::IdInfo<componentIndex>::Type>(
            ::std::forward<decltype(args)>(args)...
        );
       ::xrn::ecs::detail::ForEach::run<func, componentIndex + 1>(
            ::std::forward<decltype(args)>(args)...
        );
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    auto func,
    ::xrn::Id::Type componentIndex
> constexpr void ::xrn::ecs::detail::ForEach::runIfSignature(
    const ::xrn::ecs::Signature& signature,
    auto&&... args
)
{
    if constexpr (componentIndex < ::xrn::ecs::component::maxId) {
        if (signature.contains(componentIndex)) {
            func.template operator()<typename ::xrn::ecs::component::IdInfo<componentIndex>::Type>(
                ::std::forward<decltype(args)>(args)...
            );
        }
        ::xrn::ecs::detail::ForEach::runIfSignature<func, componentIndex + 1>(
            signature,
            ::std::forward<decltype(args)>(args)...
        );
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    auto func,
    ::xrn::Id::Type componentIndex
> constexpr void ::xrn::ecs::detail::ForEach::runWithId(
    auto&&... args
)
{
    if constexpr (componentIndex < ::xrn::ecs::component::maxId) {
        func.template operator()<typename ::xrn::ecs::component::IdInfo<componentIndex>::Type>(
            componentIndex,
            ::std::forward<decltype(args)>(args)...
        );
        ::xrn::ecs::detail::ForEach::runWithId<func, componentIndex + 1>(
            ::std::forward<decltype(args)>(args)...
        );
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    auto func,
    ::xrn::Id::Type componentIndex
> constexpr void ::xrn::ecs::detail::ForEach::runWithId(
    const ::xrn::ecs::Signature& signature,
    auto&&... args
)
{
    if constexpr (componentIndex < ::xrn::ecs::component::maxId) {
        if (signature.contains(componentIndex)) {
            func.template operator()<typename ::xrn::ecs::component::IdInfo<componentIndex>::Type>(
                componentIndex,
                ::std::forward<decltype(args)>(args)...
            );
        }
        ::xrn::ecs::detail::ForEach::runWithId<func, componentIndex + 1>(
            signature,
            ::std::forward<decltype(args)>(args)...
        );
    }
}
