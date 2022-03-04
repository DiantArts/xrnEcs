#pragma once

#include <Meta/ForEach.hpp>
#include <Ecs/Detail/Constraint.hpp>

namespace xrn::ecs::entity { class Entity; }



namespace xrn::ecs::detail::signature {



template <
    typename... ComponentTypes
> struct Generator;



template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> struct Generator <
    ComponentTypes...
> {
    static constexpr auto get()
        -> ::xrn::ecs::Signature
    {
        ::cbitset::Cbitset<::xrn::ecs::component::maxId> signature;

        for (::std::size_t i{ 0 }; i < ::xrn::ecs::component::maxId; i++) {
            ::xrn::meta::ForEach<ComponentTypes...>::template run<
                []<
                    ::xrn::ecs::detail::constraint::isComponent RawComponentType
                >(
                    ::cbitset::Cbitset<::xrn::ecs::component::maxId>& signature,
                    int i
                ){
                    using ComponentType =::std::remove_reference_t<RawComponentType>;
                    if (ComponentType::getId() == i) {
                        signature.set(i);
                    }
                }
            >(signature, i);
        }

        return Signature{ signature };
    }

    static constexpr auto value{ Generator<ComponentTypes...>::get() };
};



template <
    ::xrn::ecs::detail::constraint::isEntity EntityType,
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> struct Generator <
    EntityType,
    ComponentTypes...
> {
    static constexpr auto get()
        -> ::xrn::ecs::Signature
    {
        return ::xrn::ecs::detail::signature::Generator<ComponentTypes...>::get();
    }

    static constexpr auto value{ Generator<ComponentTypes...>::get() };
};



template <
    ::xrn::ecs::detail::constraint::isTime TimeType,
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> struct Generator <
    TimeType,
    ComponentTypes...
> {
    static constexpr auto get()
        -> ::xrn::ecs::Signature
    {
        return ::xrn::ecs::detail::signature::Generator<ComponentTypes...>::get();
    }

    static constexpr auto value{
        ::xrn::ecs::detail::signature::Generator<ComponentTypes...>::get()
    };
};

template <
    ::xrn::ecs::detail::constraint::isTime TimeType,
    ::xrn::ecs::detail::constraint::isEntity EntityType,
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> struct Generator <
    TimeType,
    EntityType,
    ComponentTypes...
> {
    static constexpr auto get()
        -> ::xrn::ecs::Signature
    {
        return ::xrn::ecs::detail::signature::Generator<ComponentTypes...>::get();
    }

    static constexpr auto value{
        ::xrn::ecs::detail::signature::Generator<ComponentTypes...>::get()
    };
};

template <
    ::xrn::ecs::detail::constraint::isEntity EntityType,
    ::xrn::ecs::detail::constraint::isTime TimeType,
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> struct Generator <
    EntityType,
    TimeType,
    ComponentTypes...
> {
    static constexpr auto get()
        -> ::xrn::ecs::Signature
    {
        return ::xrn::ecs::detail::signature::Generator<ComponentTypes...>::get();
    }

    static constexpr auto value{
        ::xrn::ecs::detail::signature::Generator<ComponentTypes...>::get()
    };
};



} // namespace xrn::ecs::system
