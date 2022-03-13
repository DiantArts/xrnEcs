#pragma once

namespace xrn::meta {



///////////////////////////////////////////////////////////////////////////
template <
    typename Type1,
    typename Type2,
    typename... Rest
> struct UniqueTypes<Type1, Type2, Rest...> {
    static constexpr const bool value{
        !::std::is_same<Type1, Type2>::value &&
        ::xrn::meta::UniqueTypes<Type1, Rest...>::value &&
        ::xrn::meta::UniqueTypes<Type2, Rest...>::value
    };
};

///////////////////////////////////////////////////////////////////////////
template <
    typename Type
> struct UniqueTypes<Type> {
    static constexpr const bool value{ true };
};



} // namespace xrn::meta
