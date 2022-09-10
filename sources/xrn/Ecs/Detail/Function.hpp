#pragma once

#include <xrn/Ecs/Signature.hpp>



namespace xrn::ecs::detail::meta {




template <
    typename... ComponentTypes
> struct ComponentHelper {
    template <
        typename func
    > struct FunctionInfo
        : public ::xrn::ecs::detail::meta::ComponentHelper<ComponentTypes...>::FunctionInfo<decltype(&func::operator())>
    {};
};



template <
    typename... ComponentTypes
> template <
    typename RetType,
    typename... ArgTypes
> struct ComponentHelper<ComponentTypes...>::FunctionInfo<RetType(ArgTypes...)> {

    struct Return {
        using Type = RetType;
    };

    struct Arguments {
        using Type = ::std::tuple<ArgTypes...>;
        static constexpr const auto areConst{ ((
            ::std::is_const<::std::remove_reference_t<ArgTypes>>::value ||
            !::std::is_reference<ArgTypes>::value
        ) && ...) };

        [[ nodiscard ]] static inline consteval auto generateSignature()
        {
            ::xrn::ecs::Signature<ComponentTypes...> signature;
            ::xrn::meta::ForEach<ArgTypes...>::template run<
                []<typename CurrentType>(::xrn::ecs::Signature<ComponentTypes...>& signature){
                    if constexpr (::xrn::meta::constraint::contains<CurrentType, ComponentTypes...>) {
                        signature.template add<CurrentType>();
                    }
                }
            >(signature);
            return signature;
        }
    };

};



template <
    typename... ComponentTypes
> template <
    typename RetType,
    typename... ArgTypes
> struct ComponentHelper<ComponentTypes...>::FunctionInfo<RetType(*)(ArgTypes...)>
    : public ::xrn::ecs::detail::meta::ComponentHelper<ComponentTypes...>::FunctionInfo<RetType(ArgTypes...)>
{};



template <
    typename... ComponentTypes
> template <
    typename RetType,
    typename... ArgTypes
> struct ComponentHelper<ComponentTypes...>::FunctionInfo<::std::function<RetType(ArgTypes...)>>
    : public ::xrn::ecs::detail::meta::ComponentHelper<ComponentTypes...>::FunctionInfo<RetType(ArgTypes...)>
{};



template <
    typename... ComponentTypes
> template <
    typename ClassType,
    typename RetType,
    typename... ArgTypes
>struct ComponentHelper<ComponentTypes...>::FunctionInfo<RetType(ClassType::*)(ArgTypes...) const>
    : public ::xrn::ecs::detail::meta::ComponentHelper<ComponentTypes...>::FunctionInfo<RetType(ArgTypes...)>
{};



} // namespace xrn::ecs::detail::meta