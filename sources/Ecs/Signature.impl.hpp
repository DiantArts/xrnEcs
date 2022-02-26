#include <Meta/ForEach.hpp>
#include <Ecs/Detail/Signature.hpp>



// ------------------------------------------------------------------ *structors

constexpr ::xrn::ecs::Signature::Signature(
    const ::cbitset::Cbitset<::xrn::ecs::component::maxId>& bitset
) noexcept
    : m_bitset{ bitset }
{}

constexpr ::xrn::ecs::Signature::~Signature() noexcept = default;



// ------------------------------------------------------------------ copy idiom

constexpr ::xrn::ecs::Signature::Signature(
    const ::xrn::ecs::Signature& other
) noexcept = default;

constexpr auto ::xrn::ecs::Signature::operator=(
    const ::xrn::ecs::Signature& other
) noexcept
    -> ::xrn::ecs::Signature& = default;



// ------------------------------------------------------------------ copy idiom

constexpr ::xrn::ecs::Signature::Signature(
    ::xrn::ecs::Signature&& other
) noexcept = default;

constexpr auto ::xrn::ecs::Signature::operator=(
    ::xrn::ecs::Signature&& other
) noexcept
    -> ::xrn::ecs::Signature& = default;



// ------------------------------------------------------------------ Genetate

template <
    typename... Types
> [[ nodiscard ]] constexpr auto ::xrn::ecs::Signature::generate() noexcept
    -> ::xrn::ecs::Signature
{
    return ::xrn::ecs::detail::signature::Generator<Types...>::value;
}



// ------------------------------------------------------------------ BitManipulation

template <
    ::xrn::ecs::component::ConceptType... ComponentTypes
> void ::xrn::ecs::Signature::set()
{
    ::xrn::meta::ForEach<ComponentTypes...>::template run<
        []<
            ::xrn::ecs::component::ConceptType RawComponentType
        >(
            ::cbitset::Cbitset<::xrn::ecs::component::maxId>& signature
        ){
            using ComponentType =::std::remove_reference_t<RawComponentType>;
            signature.set(ComponentType::getId());
        }
    >(m_bitset);
}

template <
    ::xrn::ecs::component::ConceptType... ComponentTypes
> void ::xrn::ecs::Signature::reset()
{
    ::xrn::meta::ForEach<ComponentTypes...>::template run<
        []<
            ::xrn::ecs::component::ConceptType RawComponentType
        >(
            ::cbitset::Cbitset<::xrn::ecs::component::maxId>& signature
        ){
            using ComponentType =::std::remove_reference_t<RawComponentType>;
            signature.reset(ComponentType::getId());
        }
    >(m_bitset);
}



// ------------------------------------------------------------------ Get

template <
    ::xrn::ecs::component::ConceptType ComponentType
> auto ::xrn::ecs::Signature::get()
    -> bool
{
    return m_bitset[ComponentType::getId()];
}




// ------------------------------------------------------------------ Contains

[[ nodiscard ]] constexpr auto ::xrn::ecs::Signature::contains(
    const ::xrn::ecs::Signature& that
) const
    -> bool
{
    return (m_bitset & that.m_bitset) == that.m_bitset;
}

template <
    ::xrn::ecs::component::ConceptType... ComponentTypes
> [[ nodiscard ]] constexpr auto ::xrn::ecs::Signature::contains() const
    -> bool
{
    return ::xrn::meta::ForEach<ComponentTypes...>::template compareAnd<
        []<
            ::xrn::ecs::component::ConceptType RawComponentType
        >(
            const ::cbitset::Cbitset<::xrn::ecs::component::maxId>& bitset
        ){
            using ComponentType =::std::remove_reference_t<RawComponentType>;
            return bitset[ComponentType::getId()];
        }
    >(m_bitset);
}

[[ nodiscard ]] constexpr auto ::xrn::ecs::Signature::contains(
    const ::xrn::ecs::component::ConceptType auto&... component
) const
    -> bool
{
    return (m_bitset[component.getId()] && ...);
}



// ------------------------------------------------------------------ ContainsOne

[[ nodiscard ]] constexpr auto ::xrn::ecs::Signature::containsAtLeastOne(
    const ::xrn::ecs::Signature& that
) const
    -> bool
{
    for (::std::size_t i{ 0 }; i < m_bitset.size(); i++) {
        if (m_bitset[i] && m_bitset[i] == that.m_bitset[i]) {
            return true;
        }
    }
    return false;
}

template <
    ::xrn::ecs::component::ConceptType... ComponentTypes
> [[ nodiscard ]] constexpr auto ::xrn::ecs::Signature::containsAtLeastOne() const
    -> bool
{
    return ::xrn::meta::ForEach<ComponentTypes...>::template exist<
        []<
            ::xrn::ecs::component::ConceptType RawComponentType
        >(
            const ::cbitset::Cbitset<::xrn::ecs::component::maxId>& bitset
        ){
            using ComponentType =::std::remove_reference_t<RawComponentType>;
            return bitset[ComponentType::getId()];
        }
    >(m_bitset);
}

[[ nodiscard ]] constexpr auto ::xrn::ecs::Signature::containsAtLeastOne(
    const ::xrn::ecs::component::ConceptType auto&... component
) const
    -> bool
{
    return (m_bitset[component.getId()] || ...);
}



// ------------------------------------------------------------------ Comparisons

[[ nodiscard ]] constexpr auto ::xrn::ecs::Signature::operator==(
    const ::xrn::ecs::Signature& that
) const
    -> bool
{
    return m_bitset == that.m_bitset;
}

[[ nodiscard ]] constexpr auto ::xrn::ecs::Signature::operator!=(
    const ::xrn::ecs::Signature& that
) const
    -> bool
{
    return m_bitset != that.m_bitset;
}
