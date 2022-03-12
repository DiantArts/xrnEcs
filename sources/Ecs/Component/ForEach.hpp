#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Util/Id.hpp>
#include <Ecs/Signature.hpp>



namespace xrn::ecs::component {

class ForEach {

public:

    template <
        auto func,
        ::xrn::Id::Type componentIndex = 0
    > static constexpr void run(
        auto&&... args
    )
    {
        if constexpr (componentIndex < xrn::ecs::component::maxId) {
            func.template operator()<typename ::xrn::ecs::component::IdInfo<componentIndex>::Type>(
                ::std::forward<decltype(args)>(args)...
            );
           ::xrn::ecs::component::ForEach::run<func, componentIndex + 1>(
                ::std::forward<decltype(args)>(args)...
            );
        }
    }

    template <
        auto func,
        ::xrn::Id::Type componentIndex = 0
    > static constexpr void run(
        const ::xrn::ecs::Signature& signature,
        auto&&... args
    )
    {
        if constexpr (componentIndex < xrn::ecs::component::maxId) {
            if (signature.contains(componentIndex)) {
                func.template operator()<typename ::xrn::ecs::component::IdInfo<componentIndex>::Type>(
                    ::std::forward<decltype(args)>(args)...
                );
            }
            ::xrn::ecs::component::ForEach::run<func, componentIndex + 1>(
                signature,
                ::std::forward<decltype(args)>(args)...
            );
        }
    }

    template <
        auto func,
        ::xrn::Id::Type componentIndex = 0
    > static constexpr void runWithId(
        auto&&... args
    )
    {
        if constexpr (componentIndex < xrn::ecs::component::maxId) {
            func.template operator()<typename ::xrn::ecs::component::IdInfo<componentIndex>::Type>(
                componentIndex,
                ::std::forward<decltype(args)>(args)...
            );
            ::xrn::ecs::component::ForEach::runWithId<func, componentIndex + 1>(
                ::std::forward<decltype(args)>(args)...
            );
        }
    }

    template <
        auto func,
        ::xrn::Id::Type componentIndex = 0
    > static constexpr void runWithId(
        const ::xrn::ecs::Signature& signature,
        auto&&... args
    )
    {
        if constexpr (componentIndex < xrn::ecs::component::maxId) {
            if (signature.contains(componentIndex)) {
                func.template operator()<typename ::xrn::ecs::component::IdInfo<componentIndex>::Type>(
                    componentIndex,
                    ::std::forward<decltype(args)>(args)...
                );
            }
            ::xrn::ecs::component::ForEach::runWithId<func, componentIndex + 1>(
                signature,
                ::std::forward<decltype(args)>(args)...
            );
        }
    }

};

} // namespace xrn::ecs::component
