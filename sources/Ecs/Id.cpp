#include <pch.hpp>
#include <Ecs/Id.hpp>


// ------------------------------------------------------------------ Get

::xrn::ecs::Id::operator ::std::string() const
{
    return ::std::to_string(m_value);
}



// ------------------------------------------------------------------ Set

auto ::xrn::ecs::Id::operator=(
    Id::Type value
) -> ::xrn::ecs::Id&
{
    m_value = value;
    return *this;
}



// ------------------------------------------------------------------ Incrementation

auto ::xrn::ecs::Id::operator++()
    -> xrn::ecs::Id&
{
    ++m_value;
    return *this;
}

auto ::xrn::ecs::Id::operator++(
    int
) -> xrn::ecs::Id
{
    auto value{ m_value };
    ++m_value;
    return *this;
}

void ::xrn::ecs::Id::increment()
{
    ++m_value;
}



// ------------------------------------------------------------------ Others

auto ::xrn::ecs::Id::operator<=>(const ::xrn::ecs::Id& other)
    -> ::std::weak_ordering
{
    return m_value <=> other.m_value;
}
