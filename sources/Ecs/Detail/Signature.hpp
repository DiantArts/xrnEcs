#pragma once

#include <Meta/ForEach.hpp>

namespace xrn::ecs::entity { class Entity; }



namespace xrn::ecs::detail::signature {



template <
    typename... ComponentTypes
> struct Generator;



template <
    ::xrn::ecs::component::ConceptType... ComponentTypes
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
                    ::xrn::ecs::component::ConceptType RawComponentType
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
    typename Type
> concept EntityConceptType =
    ::std::is_same<
        ::xrn::ecs::entity::Entity,
        ::std::remove_cvref_t<Type>
    >::value;

template <
    ::xrn::ecs::detail::signature::EntityConceptType EntityType,
    ::xrn::ecs::component::ConceptType... ComponentTypes
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
    typename Type
> concept TimeConceptType =
    ::std::is_same<
        ::xrn::Time,
        ::std::remove_cvref_t<Type>
    >::value;

template <
    ::xrn::ecs::detail::signature::TimeConceptType TimeType,
    ::xrn::ecs::component::ConceptType... ComponentTypes
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
    ::xrn::ecs::detail::signature::TimeConceptType TimeType,
    ::xrn::ecs::detail::signature::EntityConceptType EntityType,
    ::xrn::ecs::component::ConceptType... ComponentTypes
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
    ::xrn::ecs::detail::signature::EntityConceptType EntityType,
    ::xrn::ecs::detail::signature::TimeConceptType TimeType,
    ::xrn::ecs::component::ConceptType... ComponentTypes
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
