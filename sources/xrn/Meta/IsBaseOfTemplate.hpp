#pragma once

namespace xrn::meta {

///////////////////////////////////////////////////////////////////////////
/// \brief Checks
/// \ingroup meta
///
/// \include IsBaseOfTemplate.hpp <xrn/Meta/IsBaseOfTemplate.hpp>
///
/// This class is a part of the ::xrn::Meta Library designed to facilitate
/// usage of template metaprgramming
///
/// ::xrn::meta::IsBaseOfTemplate structure's purpuse is to execute check
/// whether the class given as secound template parameter is derived from
/// the type given as first template parameter
/// ::xrn::meta::IsBaseOfTemplate::value is true if the second types given
/// as template parameters IS indeed derived from the first one, false
/// otherwise
///
/// \tparam Types Types to execute actions on
///
///////////////////////////////////////////////////////////////////////////
template <
    template <typename...> class Base,
    typename DerivedType
> struct IsBaseOfTemplate {

private:

    ///////////////////////////////////////////////////////////////////////////
    // \brief A function which can only be called by something convertible to
    // a Base<Ts...>*
    //
    // \return A ::std::variant here as a way of "returning" a parameter pack
    //
    ///////////////////////////////////////////////////////////////////////////
    template<
        typename... Ts
    > static constexpr auto isCallable(Base<Ts...>*)
        -> ::std::variant<Ts...>;

    ///////////////////////////////////////////////////////////////////////////
    // \brief Detector, will return type of calling isCallable, or it won't
    // compile if that can't be done
    //
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename T
    > using IsCallable = decltype(
        ::xrn::meta::IsBaseOfTemplate<Base, DerivedType>::isCallable(::std::declval<T*>())
    );

    ///////////////////////////////////////////////////////////////////////////
    // \brief If it is possible to call isCallable with the Derived type what
    // would it return, if not type is void
    //
    ///////////////////////////////////////////////////////////////////////////
    using Derived = ::std::remove_cvref_t<DerivedType>;
    using Type = ::std::experimental::detected_or_t<void, IsCallable, Derived>;

public:

    ///////////////////////////////////////////////////////////////////////////
    // \brief Is it possible to call isCallable which the Derived type
    //
    ///////////////////////////////////////////////////////////////////////////
    static inline constexpr const auto value{ ::std::experimental::is_detected<IsCallable, Derived>::value };

};

///////////////////////////////////////////////////////////////////////////
/// \brief Same as ::xrn::meta::IsBaseOfTemplate<Base, DerivedType>::value
///
///////////////////////////////////////////////////////////////////////////
template <
    template <typename...> class Base,
    typename DerivedType
> inline constexpr const auto IsBaseOfTemplate_v = ::xrn::meta::IsBaseOfTemplate<Base, DerivedType>::value;

///////////////////////////////////////////////////////////////////////////
/// \brief Same as ::xrn::meta::IsBaseOfTemplate<Base, DerivedType>::value
///
///////////////////////////////////////////////////////////////////////////
template <
    template <typename...> class Base,
    typename DerivedType
> inline constexpr const auto isBaseOfTemplate = ::xrn::meta::IsBaseOfTemplate<Base, DerivedType>::value;

} // namespace xrn::meta
