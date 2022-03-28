#pragma once

#include <xrn/Ecs/Signature.hpp>



namespace xrn::ecs::detail::meta {


template <
    typename... ArgTypes
> [[ nodiscard ]] static inline consteval auto generateSignature()
{
    ::xrn::ecs::Signature signature;
    ::xrn::meta::ForEach<ArgTypes...>::template run<
        []<typename Type>(::xrn::ecs::Signature& signature){
            if constexpr (::xrn::ecs::detail::constraint::isEcsRegistered<Type>) {
                signature.add<Type>();
            }
        }
    >(signature);
    return signature;
}



template <
    typename func
> struct Function
    : public Function<decltype(&func::operator())>
{};



template <
    typename RetType,
    typename... ArgTypes
> struct Function<RetType(ArgTypes...)> {

    struct Return {
        using Type = RetType;
    };

    struct Arguments {
        using Type = ::std::tuple<ArgTypes...>;
        static constexpr const auto areConst{ ((
            ::std::is_const<::std::remove_reference_t<ArgTypes>>::value ||
            !::std::is_reference<ArgTypes>::value
        ) && ...) };
        static inline constexpr auto signature{ ::xrn::ecs::detail::meta::generateSignature<ArgTypes...>() };
    };

};



template <
    typename RetType,
    typename... ArgTypes
> struct Function<RetType(*)(ArgTypes...)>
    : public ::xrn::ecs::detail::meta::Function<RetType(ArgTypes...)>
{};



template <
    typename RetType,
    typename... ArgTypes
> struct Function<::std::function<RetType(ArgTypes...)>>
    : public ::xrn::ecs::detail::meta::Function<RetType(ArgTypes...)>
{};



template <
    typename ClassType,
    typename RetType,
    typename... ArgTypes
>struct Function<RetType(ClassType::*)(ArgTypes...) const> {

    struct Return {
        using Type = RetType;
    };

    struct Arguments {
        using Type = ::std::tuple<ArgTypes...>;
        static constexpr const auto areConst{ ((
            ::std::is_const<::std::remove_reference_t<ArgTypes>>::value ||
            !::std::is_reference<ArgTypes>::value
        ) && ...) };
        static inline constexpr auto signature{ ::xrn::ecs::detail::meta::generateSignature<ArgTypes...>() };
    };
};



} // namespace xrn::ecs::detail::meta
