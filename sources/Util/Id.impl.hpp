#include <boost/functional/hash.hpp>




// ------------------------------------------------------------------ *structors

// default value is 0
constexpr ::xrn::util::Id::Id() noexcept = default;

constexpr ::xrn::util::Id::Id(
    ::std::integral auto baseValue
) noexcept
    : m_value{ static_cast<Id::Type>(baseValue) }
{}

constexpr ::xrn::util::Id::~Id() noexcept = default;



// ------------------------------------------------------------------ copy idiom

constexpr ::xrn::util::Id::Id(
    const ::xrn::util::Id& other
) noexcept = default;

constexpr auto ::xrn::util::Id::operator=(
    const ::xrn::util::Id& other
) noexcept
    -> ::xrn::util::Id& = default;



// ------------------------------------------------------------------ copy idiom

constexpr ::xrn::util::Id::Id(
    ::xrn::util::Id&& other
) noexcept = default;

constexpr auto ::xrn::util::Id::operator=(
    ::xrn::util::Id&& other
) noexcept
    -> ::xrn::util::Id& = default;



// ------------------------------------------------------------------ Get

constexpr auto ::xrn::util::Id::get() const
    -> ::xrn::util::Id::Type
{
    return m_value;
}

constexpr ::xrn::util::Id::operator ::xrn::util::Id::Type() const
{
    return m_value;
}



// ------------------------------------------------------------------ Hasher

struct xrn::util::Id::Hasher {

    auto operator () (
        const ::xrn::util::Id& id
    ) const
        -> ::std::size_t
    {
        ::std::size_t seed = 0;
        ::boost::hash_combine(seed, id.get());
        return seed;
    }

};
