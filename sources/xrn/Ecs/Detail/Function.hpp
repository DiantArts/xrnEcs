#pragma once

#include <xrn/Ecs/Signature.hpp>



namespace xrn::ecs::detail {



///////////////////////////////////////////////////////////////////////////
/// \internal
/// \brief Helps with retrieving information from functions
/// \ingroup ecs
///
/// \include Function.hpp <xrn/Ecs/Detail/Function.hpp>
///
/// Helps with meta programming
///
/// Usage example:
/// \code
/// auto functionSignature{ ::xrn::ecs::detail::Function<ComponentTypes...>::
///     template Information<decltype(function)>::Arguments::generateSignature()
/// };
/// \endcode
///
///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> struct Function {

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Contains information about the function
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename func
    > struct InformationImpl
        : public ::xrn::ecs::detail::Function<ComponentTypes...>::InformationImpl<decltype(&func::operator())>
    {};

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the function and decltype it
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        auto func
    > struct Information
        : public ::xrn::ecs::detail::Function<ComponentTypes...>::InformationImpl<decltype(func)>
    {};

};



///////////////////////////////////////////////////////////////////////////
/// \brief Information from basic functions
///
/// All other overload inherit from this one.
///
///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    typename RetType,
    typename... ArgTypes
> struct Function<ComponentTypes...>::InformationImpl<RetType(ArgTypes...)> {

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Contains the return type
    ///
    ///////////////////////////////////////////////////////////////////////////
    struct Return {
        using Type = RetType;
    };

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Contains the argument types
    ///
    ///////////////////////////////////////////////////////////////////////////
    struct Arguments {

        ///////////////////////////////////////////////////////////////////////////
        /// \brief Tuple of all the types
        ///
        ///////////////////////////////////////////////////////////////////////////
        using Type = ::std::tuple<ArgTypes...>;

        ///////////////////////////////////////////////////////////////////////////
        /// \brief Are all the arguments modifying the original value passed as
        ///        argument (mutable ref or ptr).
        ///
        ///////////////////////////////////////////////////////////////////////////
        static constexpr const auto areConst{ ((
            ::std::is_const<::std::remove_reference_t<ArgTypes>>::value ||
            !::std::is_reference<ArgTypes>::value
        ) && ...) };

        ///////////////////////////////////////////////////////////////////////////
        /// \brief Generate a ::xrn::ecs::Signature of the arguments
        ///
        ///////////////////////////////////////////////////////////////////////////
        [[ nodiscard ]] static inline consteval auto generateSignature()
            -> ::xrn::ecs::Signature<ComponentTypes...>
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



///////////////////////////////////////////////////////////////////////////
/// \brief Information from function pointers
///
///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    typename RetType,
    typename... ArgTypes
> struct Function<ComponentTypes...>::InformationImpl<RetType(*)(ArgTypes...)>
    : public ::xrn::ecs::detail::Function<ComponentTypes...>::InformationImpl<RetType(ArgTypes...)>
{};



///////////////////////////////////////////////////////////////////////////
/// \brief Information from ::std::function
///
///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    typename RetType,
    typename... ArgTypes
> struct Function<ComponentTypes...>::InformationImpl<::std::function<RetType(ArgTypes...)>>
    : public ::xrn::ecs::detail::Function<ComponentTypes...>::InformationImpl<RetType(ArgTypes...)>
{};



///////////////////////////////////////////////////////////////////////////
/// \brief Information from class operator()
///
///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    typename ClassType,
    typename RetType,
    typename... ArgTypes
>struct Function<ComponentTypes...>::InformationImpl<RetType(ClassType::*)(ArgTypes...) const>
    : public ::xrn::ecs::detail::Function<ComponentTypes...>::InformationImpl<RetType(ArgTypes...)>
{};



} // namespace xrn::ecs::detail
