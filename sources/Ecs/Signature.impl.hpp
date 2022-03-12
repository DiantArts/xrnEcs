#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Meta/ForEach.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// static elements
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> consteval auto ::xrn::ecs::Signature::generate() noexcept
    -> ::xrn::ecs::Signature
{
    ::xrn::ecs::Signature signature;

    ::xrn::meta::ForEach<Types...>::template run<
        []<typename Type>(
            ::xrn::ecs::Signature& signature
        ){
            if constexpr (::xrn::ecs::detail::constraint::isComponent<Type>) {
                using ComponentType =::std::remove_reference_t<Type>;
                signature.set<ComponentType>();
            }
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
constexpr ::xrn::ecs::Signature::Signature() noexcept = default;



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Setters
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> constexpr void ::xrn::ecs::Signature::add()
{
    ::xrn::meta::ForEach<ComponentTypes...>::template run<
        []<::xrn::ecs::detail::constraint::isComponent RawComponentType>(
            ::cbitset::Cbitset<::xrn::ecs::component::maxId>& signature
        ){
            using ComponentType =::std::remove_reference_t<RawComponentType>;
            signature.set(ComponentType::getId());
        }
    >(m_bitset);
}

///////////////////////////////////////////////////////////////////////////
constexpr void ::xrn::ecs::Signature::add(
    ::xrn::ecs::detail::constraint::isId auto... componentIds
)
{
    for (auto componentId : { componentIds... }) {
        m_bitset.set(componentId);
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> constexpr void ::xrn::ecs::Signature::set()
{
    this->add<ComponentTypes...>();
}

///////////////////////////////////////////////////////////////////////////
constexpr void ::xrn::ecs::Signature::set(
    ::xrn::ecs::detail::constraint::isId auto... componentIds
)
{
    this->add(componentIds...);
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> constexpr void ::xrn::ecs::Signature::remove()
{
    ::xrn::meta::ForEach<ComponentTypes...>::template run<
        []<::xrn::ecs::detail::constraint::isComponent RawComponentType>(
            ::cbitset::Cbitset<::xrn::ecs::component::maxId>& signature
        ){
            using ComponentType =::std::remove_reference_t<RawComponentType>;
            signature.reset(ComponentType::getId());
        }
    >(m_bitset);
}

///////////////////////////////////////////////////////////////////////////
constexpr void ::xrn::ecs::Signature::remove(
    ::xrn::ecs::detail::constraint::isId auto... componentIds
)
{
    for (auto componentId : { componentIds... }) {
        m_bitset.reset(componentId);
    }
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> constexpr void ::xrn::ecs::Signature::reset()
{
    this->remove<ComponentTypes...>();
}

///////////////////////////////////////////////////////////////////////////
constexpr void ::xrn::ecs::Signature::reset(
    ::xrn::ecs::detail::constraint::isId auto... componentIds
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
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> constexpr auto ::xrn::ecs::Signature::get() const
    -> bool
{
    return m_bitset[ComponentType::getId()];
}

///////////////////////////////////////////////////////////////////////////
constexpr auto ::xrn::ecs::Signature::get(
    ::xrn::ecs::detail::constraint::isComponent auto& component
) const
    -> bool
{
    return m_bitset[component.getId()];
}

///////////////////////////////////////////////////////////////////////////
constexpr auto ::xrn::ecs::Signature::get(
    ::xrn::Id componentId
) const
    -> bool
{
    return m_bitset[componentId];
}

///////////////////////////////////////////////////////////////////////////
constexpr auto ::xrn::ecs::Signature::operator[](
    ::xrn::ecs::detail::constraint::isComponent auto& component
) const
    -> bool
{
    return m_bitset[component.getId()];
}

///////////////////////////////////////////////////////////////////////////
constexpr auto ::xrn::ecs::Signature::operator[](
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
constexpr auto ::xrn::ecs::Signature::contains(
    const ::xrn::ecs::Signature& signature
) const
    -> bool
{
    return this->containsAll(signature);
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> constexpr auto ::xrn::ecs::Signature::contains() const
    -> bool
{
    return this->containsAll<ComponentTypes...>();
}

///////////////////////////////////////////////////////////////////////////
constexpr auto ::xrn::ecs::Signature::contains(
    const ::xrn::ecs::detail::constraint::isComponent auto&... components
) const
    -> bool
{
    return this->containsAll(components...);
}

///////////////////////////////////////////////////////////////////////////
constexpr auto ::xrn::ecs::Signature::contains(
    ::xrn::ecs::detail::constraint::isId auto... componentIds
) const
    -> bool
{
    return this->containsAll(componentIds...);
}

///////////////////////////////////////////////////////////////////////////
constexpr auto ::xrn::ecs::Signature::containsAll(
    const ::xrn::ecs::Signature& signature
) const
    -> bool
{
    return (m_bitset & signature.m_bitset) == signature.m_bitset;
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> constexpr auto ::xrn::ecs::Signature::containsAll() const
    -> bool
{
    return (m_bitset[ComponentTypes::getId()] && ...);
}

///////////////////////////////////////////////////////////////////////////
constexpr auto ::xrn::ecs::Signature::containsAll(
    const ::xrn::ecs::detail::constraint::isComponent auto&... components
) const
    -> bool
{
    return (m_bitset[components.getId()] && ...);
}

///////////////////////////////////////////////////////////////////////////
constexpr auto ::xrn::ecs::Signature::containsAll(
    ::xrn::ecs::detail::constraint::isId auto... componentIds
) const
    -> bool
{
    return (m_bitset[componentIds] && ...);
}

///////////////////////////////////////////////////////////////////////////
constexpr auto ::xrn::ecs::Signature::containsAny(
    const ::xrn::ecs::Signature& signature
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
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> constexpr auto ::xrn::ecs::Signature::containsAny() const
    -> bool
{
    return (m_bitset[ComponentTypes::getId()] || ...);
}

///////////////////////////////////////////////////////////////////////////
constexpr auto ::xrn::ecs::Signature::containsAny(
    const ::xrn::ecs::detail::constraint::isComponent auto&... components
) const
    -> bool
{
    return (m_bitset[components.getId()] || ...);
}

///////////////////////////////////////////////////////////////////////////
constexpr auto ::xrn::ecs::Signature::containsAny(
    ::xrn::ecs::detail::constraint::isId auto... componentIds
) const
    -> bool
{
    return (m_bitset[componentIds] || ...);
}

///////////////////////////////////////////////////////////////////////////
constexpr auto ::xrn::ecs::Signature::containsNone(
    const ::xrn::ecs::Signature& signature
) const
    -> bool
{
    return !this->containsAny(signature);
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> constexpr auto ::xrn::ecs::Signature::containsNone() const
    -> bool
{
    return !this->containsAny<ComponentTypes...>();
}

///////////////////////////////////////////////////////////////////////////
constexpr auto ::xrn::ecs::Signature::containsNone(
    const ::xrn::ecs::detail::constraint::isComponent auto&... components
) const
    -> bool
{
    return !this->containsAny(components...);
}

///////////////////////////////////////////////////////////////////////////
constexpr auto ::xrn::ecs::Signature::containsNone(
    ::xrn::ecs::detail::constraint::isId auto... componentIds
) const
    -> bool
{
    return !this->containsAny(componentIds...);
}

///////////////////////////////////////////////////////////////////////////
constexpr auto ::xrn::ecs::Signature::operator==(
    const ::xrn::ecs::Signature& signature
) const
    -> bool
{
    return m_bitset == signature.m_bitset;
}

///////////////////////////////////////////////////////////////////////////
constexpr auto ::xrn::ecs::Signature::operator!=(
    const ::xrn::ecs::Signature& signature
) const
    -> bool
{
    return m_bitset != signature.m_bitset;
}
