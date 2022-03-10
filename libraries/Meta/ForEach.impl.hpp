#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// methods
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> template <
    auto function
> constexpr void ::xrn::meta::ForEach<Types...>::run(
    auto&&... args
)
{
    (function.template operator()<Types>(::std::forward<decltype(args)>(args)...), ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> template <
    auto function
> constexpr auto ::xrn::meta::ForEach<Types...>::compareAnd(
    auto&&... args
) -> bool
{
    return (function.template operator()<Types>(::std::forward<decltype(args)>(args)...) && ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> template <
    auto function
> constexpr auto ::xrn::meta::ForEach<Types...>::compareOr(
    auto&&... args
) -> bool
{
    return (function.template operator()<Types>(::std::forward<decltype(args)>(args)...) || ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> template <
    typename Type
> constexpr auto ::xrn::meta::ForEach<Types...>::hasType()
    -> bool
{
    return (::std::is_same<Type, Types>::value || ...);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Specialization for Tuple
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> template <
    auto function
> constexpr void ::xrn::meta::ForEach<::xrn::meta::detail::Tuple<Types...>>::run(
    auto&&... args
)
{
    (function.template operator()<Types>(::std::forward<decltype(args)>(args)...), ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> template <
    auto function
> constexpr auto ::xrn::meta::ForEach<::xrn::meta::detail::Tuple<Types...>>::compareAnd(
    auto&&... args
) -> bool
{
    return (function.template operator()<Types>(::std::forward<decltype(args)>(args)...) && ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> template <
    auto function
> constexpr auto ::xrn::meta::ForEach<::xrn::meta::detail::Tuple<Types...>>::compareOr(
    auto&&... args
) -> bool
{
    return (function.template operator()<Types>(::std::forward<decltype(args)>(args)...) || ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> template <
    typename Type
> constexpr auto ::xrn::meta::ForEach<::xrn::meta::detail::Tuple<Types...>>::hasType()
    -> bool
{
    return (::std::is_same<Type, Types>::value || ...);
}
