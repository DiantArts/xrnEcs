namespace xrn::meta::detail {

///////////////////////////////////////////////////////////////////////////
template <
    typename... ArgTypes
> struct Tuple {
    using Type = ::xrn::meta::detail::Tuple<ArgTypes...>;
};

///////////////////////////////////////////////////////////////////////////
template <
    typename... NestedArgTypes,
    typename... ArgTypes
> struct Tuple<::xrn::meta::detail::Tuple<NestedArgTypes...>, ArgTypes...>
{
    using Type = ::xrn::meta::detail::Tuple<NestedArgTypes..., ArgTypes...>;
};

} // namespace xrn::meta::detail
