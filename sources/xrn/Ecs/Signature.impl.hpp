#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// static elements
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...>... Types
> consteval auto ::xrn::ecs::Signature<ComponentTypes...>::generate() noexcept
    -> ::xrn::ecs::Signature<ComponentTypes...>
{
    ::xrn::ecs::Signature<ComponentTypes...> signature;

    ::xrn::meta::ForEach<Types...>::template run<
        []<::xrn::meta::constraint::contains<ComponentTypes...> Type>(
            ::xrn::ecs::Signature<ComponentTypes...>& signatureRef
        ){
            signatureRef.set<Type>();
        }
    >(signature);
    return signature;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> constexpr ::xrn::ecs::Signature<ComponentTypes...>::Signature() noexcept = default;



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Set/add
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...>... Types
> constexpr void ::xrn::ecs::Signature<ComponentTypes...>::add()
{
    static_assert(sizeof...(Types), "Adding to a signature with 0 template arguments");

    ::xrn::meta::ForEach<Types...>::template run<
        []<::xrn::meta::constraint::contains<ComponentTypes...> RawType>(
            ::cbitset::Cbitset<sizeof...(ComponentTypes)>& signature
        ){
            using Type = ::std::remove_cvref_t<::std::remove_pointer_t<RawType>>;
            signature.set(::xrn::meta::ForEach<ComponentTypes...>::template getPosition<Type>());
        }
    >(m_bitset);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> constexpr void ::xrn::ecs::Signature<ComponentTypes...>::add(
    ::xrn::util::constraint::isId auto... componentIds
)
{
    for (auto componentId : { componentIds... }) {
        m_bitset.set(componentId);
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...>... Types
> constexpr void ::xrn::ecs::Signature<ComponentTypes...>::set()
{
    static_assert(sizeof...(Types), "Adding to a signature with 0 template arguments");
    this->add<Types...>();
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> constexpr void ::xrn::ecs::Signature<ComponentTypes...>::set(
    ::xrn::util::constraint::isId auto... componentIds
)
{
    this->add(componentIds...);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Reset/Remove
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...>... Types
> constexpr void ::xrn::ecs::Signature<ComponentTypes...>::remove()
{
    static_assert(sizeof...(Types), "Adding to a signature with 0 template arguments");
    ::xrn::meta::ForEach<Types...>::template run<
        []<::xrn::meta::constraint::contains<ComponentTypes...> RawType>(
            ::cbitset::Cbitset<sizeof...(ComponentTypes)>& signature
        ){
            using Type = ::std::remove_cvref_t<::std::remove_pointer_t<RawType>>;
            signature.reset(::xrn::meta::ForEach<ComponentTypes...>::template getPosition<Type>());
        }
    >(m_bitset);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> constexpr void ::xrn::ecs::Signature<ComponentTypes...>::remove(
    ::xrn::util::constraint::isId auto... componentIds
)
{
    for (auto componentId : { componentIds... }) {
        m_bitset.reset(componentId);
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> void ::xrn::ecs::Signature<ComponentTypes...>::reset()
{
    m_bitset.reset();
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...>... Types
> constexpr void ::xrn::ecs::Signature<ComponentTypes...>::reset()
{
    static_assert(sizeof...(Types), "Reseting to a signature with 0 template arguments");
    this->remove<Types...>();
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> constexpr void ::xrn::ecs::Signature<ComponentTypes...>::reset(
    ::xrn::util::constraint::isId auto... componentIds
)
{
    this->remove(componentIds...);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Getters
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...> Type
> constexpr auto ::xrn::ecs::Signature<ComponentTypes...>::get() const
    -> bool
{
    return m_bitset[::xrn::meta::ForEach<ComponentTypes...>::template getPosition<Type>()];
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> constexpr auto ::xrn::ecs::Signature<ComponentTypes...>::get(
    ::xrn::Id componentId
) const
    -> bool
{
    return m_bitset[componentId];
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> constexpr auto ::xrn::ecs::Signature<ComponentTypes...>::operator[](
    ::xrn::Id componentId
) const
    -> bool
{
    return m_bitset[componentId];
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Comparison
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> constexpr auto ::xrn::ecs::Signature<ComponentTypes...>::contains(
    const ::xrn::ecs::Signature<ComponentTypes...>& signature
) const
    -> bool
{
    return this->containsAll(signature);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...>... Types
> constexpr auto ::xrn::ecs::Signature<ComponentTypes...>::contains() const
    -> bool
{
    return this->containsAll<Types...>();
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> constexpr auto ::xrn::ecs::Signature<ComponentTypes...>::contains(
    ::xrn::util::constraint::isId auto... componentIds
) const
    -> bool
{
    return this->containsAll(componentIds...);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> constexpr auto ::xrn::ecs::Signature<ComponentTypes...>::containsAll(
    const ::xrn::ecs::Signature<ComponentTypes...>& signature
) const
    -> bool
{
    return (m_bitset & signature.m_bitset) == signature.m_bitset;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...>... Types
> constexpr auto ::xrn::ecs::Signature<ComponentTypes...>::containsAll() const
    -> bool
{
    return (m_bitset[::xrn::meta::ForEach<ComponentTypes...>::template getPosition<Types>()] && ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> constexpr auto ::xrn::ecs::Signature<ComponentTypes...>::containsAll(
    ::xrn::util::constraint::isId auto... componentIds
) const
    -> bool
{
    return (m_bitset[componentIds] && ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> constexpr auto ::xrn::ecs::Signature<ComponentTypes...>::containsAny(
    const ::xrn::ecs::Signature<ComponentTypes...>& signature
) const
    -> bool
{
    for (auto i{ 0uz }; i < m_bitset.size(); ++i) {
        if (m_bitset[i] && m_bitset[i] == signature.m_bitset[i]) {
            return true;
        }
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...>... Types
> constexpr auto ::xrn::ecs::Signature<ComponentTypes...>::containsAny() const
    -> bool
{
    return (m_bitset[::xrn::meta::ForEach<ComponentTypes...>::template getPosition<Types>()] || ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> constexpr auto ::xrn::ecs::Signature<ComponentTypes...>::containsAny(
    ::xrn::util::constraint::isId auto... componentIds
) const
    -> bool
{
    return (m_bitset[componentIds] || ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> constexpr auto ::xrn::ecs::Signature<ComponentTypes...>::containsNone(
    const ::xrn::ecs::Signature<ComponentTypes...>& signature
) const
    -> bool
{
    return !this->containsAny(signature);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> template <
    ::xrn::meta::constraint::contains<ComponentTypes...>... Types
> constexpr auto ::xrn::ecs::Signature<ComponentTypes...>::containsNone() const
    -> bool
{
    return !this->containsAny<Types...>();
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> constexpr auto ::xrn::ecs::Signature<ComponentTypes...>::containsNone(
    ::xrn::util::constraint::isId auto... componentIds
) const
    -> bool
{
    return !this->containsAny(componentIds...);
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> constexpr auto ::xrn::ecs::Signature<ComponentTypes...>::operator==(
    const ::xrn::ecs::Signature<ComponentTypes...>& signature
) const
    -> bool
{
    return m_bitset == signature.m_bitset;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> constexpr auto ::xrn::ecs::Signature<ComponentTypes...>::operator!=(
    const ::xrn::ecs::Signature<ComponentTypes...>& signature
) const
    -> bool
{
    return m_bitset != signature.m_bitset;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// ::std::ostream
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> auto operator<<(
    ::std::ostream& os,
    const ::xrn::ecs::Signature<ComponentTypes...>& signature
) -> ::std::ostream&
{
    for (auto i{ 0uz }; i < sizeof...(ComponentTypes); ++i) {
        os << signature[i];
    }
    return os;
}
