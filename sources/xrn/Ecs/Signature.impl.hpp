#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Meta/ForEach.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// static elements
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isEcsRegistered... Types
> consteval auto ::xrn::ecs::Signature::generate() noexcept
    -> ::xrn::ecs::Signature
{
    ::xrn::ecs::Signature signature;

    ::xrn::meta::ForEach<Types...>::template run<
        []<::xrn::ecs::detail::constraint::isEcsRegistered Type>(
            ::xrn::ecs::Signature& signature
        ){
            signature.set<Type>();
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
// Set/add
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isEcsRegistered... Types
> constexpr void ::xrn::ecs::Signature::add()
{
    static_assert(sizeof...(Types), "Adding to a signature with 0 template arguments");

    ::xrn::meta::ForEach<Types...>::template run<
        []<::xrn::ecs::detail::constraint::isEcsRegistered RawType>(
            ::cbitset::Cbitset<::xrn::ecs::component::maxId>& signature
        ){
            using Type = ::std::remove_cvref_t<::std::remove_pointer_t<RawType>>;
            signature.set(Type::getId());
        }
    >(m_bitset);
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> constexpr void ::xrn::ecs::Signature::addComponents()
{
    static_assert(sizeof...(ComponentTypes), "Adding to a signature with 0 template arguments");
    ::xrn::meta::ForEach<ComponentTypes...>::template run<
        []<::xrn::ecs::detail::constraint::isComponent RawComponentType>(
            ::cbitset::Cbitset<::xrn::ecs::component::maxId>& signature
        ){
            using ComponentType = ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>;
            signature.set(ComponentType::getId());
        }
    >(m_bitset);
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isAbility... AbilityTypes
> constexpr void ::xrn::ecs::Signature::addAbilities()
{
    static_assert(sizeof...(AbilityTypes), "Adding to a signature with 0 template arguments");
    ::xrn::meta::ForEach<AbilityTypes...>::template run<
        []<::xrn::ecs::detail::constraint::isAbility RawComponentType>(
            ::cbitset::Cbitset<::xrn::ecs::component::maxId>& signature
        ){
            using ComponentType = ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>;
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
    ::xrn::ecs::detail::constraint::isEcsRegistered... Types
> constexpr void ::xrn::ecs::Signature::set()
{
    static_assert(sizeof...(Types), "Adding to a signature with 0 template arguments");
    this->add<Types...>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> constexpr void ::xrn::ecs::Signature::setComponents()
{
    static_assert(sizeof...(ComponentTypes), "Adding to a signature with 0 template arguments");
    this->add<ComponentTypes...>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isAbility... AbilityTypes
> constexpr void ::xrn::ecs::Signature::setAbilities()
{
    static_assert(sizeof...(AbilityTypes), "Adding to a signature with 0 template arguments");
    this->add<AbilityTypes...>();
}

///////////////////////////////////////////////////////////////////////////
constexpr void ::xrn::ecs::Signature::set(
    ::xrn::ecs::detail::constraint::isId auto... componentIds
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
    ::xrn::ecs::detail::constraint::isEcsRegistered... Types
> constexpr void ::xrn::ecs::Signature::remove()
{
    static_assert(sizeof...(Types), "Adding to a signature with 0 template arguments");
    ::xrn::meta::ForEach<Types...>::template run<
        []<::xrn::ecs::detail::constraint::isEcsRegistered RawType>(
            ::cbitset::Cbitset<::xrn::ecs::component::maxId>& signature
        ){
            using Type = ::std::remove_cvref_t<::std::remove_pointer_t<RawType>>;
            signature.reset(Type::getId());
        }
    >(m_bitset);
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> constexpr void ::xrn::ecs::Signature::removeComponents()
{
    static_assert(sizeof...(ComponentTypes), "Adding to a signature with 0 template arguments");
    ::xrn::meta::ForEach<ComponentTypes...>::template run<
        []<::xrn::ecs::detail::constraint::isComponent RawComponentType>(
            ::cbitset::Cbitset<::xrn::ecs::component::maxId>& signature
        ){
            using ComponentType = ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>;
            signature.reset(ComponentType::getId());
        }
    >(m_bitset);
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isAbility... AbilityTypes
> constexpr void ::xrn::ecs::Signature::removeAbilities()
{
    static_assert(sizeof...(AbilityTypes), "Adding to a signature with 0 template arguments");
    ::xrn::meta::ForEach<AbilityTypes...>::template run<
        []<::xrn::ecs::detail::constraint::isAbility RawComponentType>(
            ::cbitset::Cbitset<::xrn::ecs::component::maxId>& signature
        ){
            using ComponentType = ::std::remove_cvref_t<::std::remove_pointer_t<RawComponentType>>;
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
void ::xrn::ecs::Signature::reset()
{
    m_bitset.reset();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isEcsRegistered... Types
> constexpr void ::xrn::ecs::Signature::reset()
{
    static_assert(sizeof...(Types), "Reseting to a signature with 0 template arguments");
    this->remove<Types...>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> constexpr void ::xrn::ecs::Signature::resetComponents()
{
    this->remove<ComponentTypes...>();
}


///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isAbility... ComponentTypes
> constexpr void ::xrn::ecs::Signature::resetAbilities()
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
    ::xrn::ecs::detail::constraint::isEcsRegistered Type
> constexpr auto ::xrn::ecs::Signature::get() const
    -> bool
{
    return m_bitset[Type::getId()];
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent ComponentType
> constexpr auto ::xrn::ecs::Signature::getComponent() const
    -> bool
{
    return m_bitset[ComponentType::getId()];
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isAbility AbilityType
> constexpr auto ::xrn::ecs::Signature::getAbility() const
    -> bool
{
    return m_bitset[AbilityType::getId()];
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
    ::xrn::ecs::detail::constraint::isEcsRegistered... Types
> constexpr auto ::xrn::ecs::Signature::contains() const
    -> bool
{
    return this->containsAll<Types...>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> constexpr auto ::xrn::ecs::Signature::containsComponents() const
    -> bool
{
    return this->containsAll<ComponentTypes...>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isAbility... AbilityTypes
> constexpr auto ::xrn::ecs::Signature::containsAbilities() const
    -> bool
{
    return this->containsAll<AbilityTypes...>();
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
    ::xrn::ecs::detail::constraint::isEcsRegistered... Types
> constexpr auto ::xrn::ecs::Signature::containsAll() const
    -> bool
{
    return (m_bitset[Types::getId()] && ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> constexpr auto ::xrn::ecs::Signature::containsAllComponents() const
    -> bool
{
    return (m_bitset[ComponentTypes::getId()] && ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isAbility... AbilityTypes
> constexpr auto ::xrn::ecs::Signature::containsAllAbilities() const
    -> bool
{
    return (m_bitset[AbilityTypes::getId()] && ...);
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
    ::xrn::ecs::detail::constraint::isEcsRegistered... ComponentTypes
> constexpr auto ::xrn::ecs::Signature::containsAny() const
    -> bool
{
    return (m_bitset[ComponentTypes::getId()] || ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> constexpr auto ::xrn::ecs::Signature::containsAnyComponent() const
    -> bool
{
    return (m_bitset[ComponentTypes::getId()] || ...);
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isAbility... AbilityTypes
> constexpr auto ::xrn::ecs::Signature::containsAnyAbility() const
    -> bool
{
    return (m_bitset[AbilityTypes::getId()] || ...);
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
    ::xrn::ecs::detail::constraint::isEcsRegistered... Types
> constexpr auto ::xrn::ecs::Signature::containsNone() const
    -> bool
{
    return !this->containsAny<Types...>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
> constexpr auto ::xrn::ecs::Signature::containsNoneComponent() const
    -> bool
{
    return !this->containsAny<ComponentTypes...>();
}

///////////////////////////////////////////////////////////////////////////
template <
    ::xrn::ecs::detail::constraint::isAbility... AbilityTypes
> constexpr auto ::xrn::ecs::Signature::containsNoneAbility() const
    -> bool
{
    return !this->containsAny<AbilityTypes...>();
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



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// ::std::ostream
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
auto operator<<(
    ::std::ostream& os,
    const ::xrn::ecs::Signature& signature
) -> ::std::ostream&
{
    for (auto i{ 0uz }; i < ::xrn::ecs::component::maxId; ++i) {
        os << signature[i];
    }
    return os;
}
