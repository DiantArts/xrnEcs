#include <pch.hpp>
#include <Util/Id.hpp>


// ------------------------------------------------------------------ Get

::xrn::util::Id::operator ::std::string() const
{
    return ::std::to_string(m_value);
}



// ------------------------------------------------------------------ Set

auto ::xrn::util::Id::operator=(
    Id::Type value
) -> ::xrn::util::Id&
{
    m_value = value;
    return *this;
}



// ------------------------------------------------------------------ Incrementation

auto ::xrn::util::Id::operator++()
    -> xrn::util::Id&
{
    ++m_value;
    return *this;
}

auto ::xrn::util::Id::operator++(
    int
) -> xrn::util::Id
{
    auto value{ m_value };
    ++m_value;
    return *this;
}

void ::xrn::util::Id::increment()
{
    ++m_value;
}



// ------------------------------------------------------------------ Others

auto ::xrn::util::Id::operator<=>(const ::xrn::util::Id& other)
    -> ::std::weak_ordering
{
    return m_value <=> other.m_value;
}
