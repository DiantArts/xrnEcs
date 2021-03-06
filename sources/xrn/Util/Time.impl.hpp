#pragma once

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> constexpr auto ::xrn::util::BasicTime<T>::createAsSeconds(
    const auto& amount
) noexcept -> ::xrn::util::BasicTime<T>
{
    return ::xrn::util::BasicTime<T>{ static_cast<::xrn::util::BasicTime<T>::Type>(amount) * 1'000 };
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> constexpr auto ::xrn::util::BasicTime<T>::createAsMilliseconds(
    const auto& amount
) noexcept -> ::xrn::util::BasicTime<T>
{
    return ::xrn::util::BasicTime<T>{ static_cast<::xrn::util::BasicTime<T>::Type>(amount) };
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> constexpr auto ::xrn::util::BasicTime<T>::createAsMicroseconds(
    const auto& amount
) noexcept -> ::xrn::util::BasicTime<T>
{
    return ::xrn::util::BasicTime<T>{ static_cast<::xrn::util::BasicTime<T>::Type>(amount) / 1'000 };
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> constexpr auto ::xrn::util::BasicTime<T>::createAsNanoseconds(
    const auto& amount
) noexcept -> ::xrn::util::BasicTime<T>
{
    return ::xrn::util::BasicTime<T>{ static_cast<::xrn::util::BasicTime<T>::Type>(amount) / 1'000'000 };
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> constexpr ::xrn::util::BasicTime<T>::BasicTime(
    auto amount
) noexcept
    : m_time{ static_cast<::xrn::util::BasicTime<T>::Type>(amount) }
{}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Comparison
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> constexpr auto ::xrn::util::BasicTime<T>::operator<=>(
    const ::xrn::util::BasicTime<T>& rhs
) const
    -> ::std::partial_ordering
{
    return m_time <=> rhs.m_time;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> constexpr auto ::xrn::util::BasicTime<T>::operator<=>(
    const auto& rhs
) const
    -> ::std::partial_ordering
{
    return m_time <=> rhs;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Get
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> constexpr ::xrn::util::BasicTime<T>::operator BasicTime<T>::Type() const noexcept
{
    return m_time;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> constexpr auto ::xrn::util::BasicTime<T>::get() const
    -> BasicTime<T>::Type
{
    return m_time;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> constexpr auto ::xrn::util::BasicTime<T>::getAsSeconds() const
    -> BasicTime<T>::Type
{
    return m_time / 1'000;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> constexpr auto ::xrn::util::BasicTime<T>::getAsMilliseconds() const
    -> BasicTime<T>::Type
{
    return m_time;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> constexpr auto ::xrn::util::BasicTime<T>::getAsMicroseconds() const
    -> BasicTime<T>::Type
{
    return m_time * 1'000;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> constexpr auto ::xrn::util::BasicTime<T>::getAsNanoseconds() const
    -> BasicTime<T>::Type
{
    return m_time * 1'000'000;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Set
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> auto ::xrn::util::BasicTime<T>::operator=(
    const auto& amount
) -> ::xrn::util::BasicTime<T>&
{
    m_time = amount;
    return *this;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> void ::xrn::util::BasicTime<T>::set(
    const ::xrn::util::BasicTime<T>& amount
)
{
    m_time = amount.m_time;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> void ::xrn::util::BasicTime<T>::set(
    const auto& amount
)
{
    m_time = amount;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Add
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> auto ::xrn::util::BasicTime<T>::operator+=(
    const ::xrn::util::BasicTime<T>& rhs
) -> ::xrn::util::BasicTime<T>&
{
    m_time += rhs.m_time;
    return *this;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> auto ::xrn::util::BasicTime<T>::operator+=(
    const auto& rhs
) -> ::xrn::util::BasicTime<T>&
{
    m_time += rhs;
    return *this;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> constexpr auto ::xrn::util::BasicTime<T>::operator+(
    const ::xrn::util::BasicTime<T>& rhs
) const
    -> ::xrn::util::BasicTime<T>
{
    ::xrn::util::BasicTime<T> newTime{ *this };
    newTime.add(rhs);
    return newTime;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> constexpr auto ::xrn::util::BasicTime<T>::operator+(
    const auto& rhs
) const
    -> ::xrn::util::BasicTime<T>
{
    ::xrn::util::BasicTime<T> newTime{ *this };
    newTime.add(rhs);
    return newTime;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> void ::xrn::util::BasicTime<T>::add(
    const ::xrn::util::BasicTime<T>& amount
)
{
    m_time += amount.m_time;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> void ::xrn::util::BasicTime<T>::add(
    const auto& amount
)
{
    m_time += amount;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Sub
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> auto ::xrn::util::BasicTime<T>::operator-=(
    const ::xrn::util::BasicTime<T>& rhs
) -> ::xrn::util::BasicTime<T>&
{
    m_time -= rhs.m_time;
    return *this;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> auto ::xrn::util::BasicTime<T>::operator-=(
    const auto& rhs
) -> ::xrn::util::BasicTime<T>&
{
    m_time -= rhs;
    return *this;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> constexpr auto ::xrn::util::BasicTime<T>::operator-(
    const ::xrn::util::BasicTime<T>& rhs
) const
    -> ::xrn::util::BasicTime<T>
{
    ::xrn::util::BasicTime<T> newTime{ *this };
    newTime.sub(rhs);
    return newTime;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> constexpr auto ::xrn::util::BasicTime<T>::operator-(
    const auto& rhs
) const
    -> ::xrn::util::BasicTime<T>
{
    ::xrn::util::BasicTime<T> newTime{ *this };
    newTime.sub(rhs);
    return newTime;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> void ::xrn::util::BasicTime<T>::sub(
    const ::xrn::util::BasicTime<T>& amount
)
{
    m_time -= amount.m_time;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> void ::xrn::util::BasicTime<T>::sub(
    const auto& amount
)
{
    m_time -= amount;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Mul
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> auto ::xrn::util::BasicTime<T>::operator*=(
    const auto& rhs
) -> ::xrn::util::BasicTime<T>&
{
    m_time *= rhs;
    return *this;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> constexpr auto ::xrn::util::BasicTime<T>::operator*(
    const auto& rhs
) const
    -> ::xrn::util::BasicTime<T>
{
    ::xrn::util::BasicTime<T> newTime{ *this };
    newTime.mul(rhs);
    return newTime;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> void ::xrn::util::BasicTime<T>::mul(
    const auto& amount
)
{
    m_time *= amount;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Div
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> auto ::xrn::util::BasicTime<T>::operator/=(
    const auto& rhs
) -> ::xrn::util::BasicTime<T>&
{
    m_time /= rhs;
    return *this;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> constexpr auto ::xrn::util::BasicTime<T>::operator/(
    const auto& rhs
) const
    -> ::xrn::util::BasicTime<T>
{
    ::xrn::util::BasicTime<T> newTime{ *this };
    newTime.div(rhs);
    return newTime;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> void ::xrn::util::BasicTime<T>::div(
    const auto& amount
)
{
    m_time /= amount;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Mod
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> auto ::xrn::util::BasicTime<T>::operator%=(
    const auto& rhs
) -> ::xrn::util::BasicTime<T>&
{
    auto newValue{
        static_cast<::std::uint_fast32_t>(m_time) % static_cast<::std::uint_fast32_t>(rhs)
    };
    m_time = newValue;
    return *this;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> constexpr auto ::xrn::util::BasicTime<T>::operator%(
    const auto& rhs
) const
    -> ::xrn::util::BasicTime<T>
{
    ::xrn::util::BasicTime<T> newTime{ *this };
    newTime.mod(rhs);
    return newTime;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> void ::xrn::util::BasicTime<T>::mod(
    const auto& amount
)
{
    auto newValue{
        static_cast<::std::uint_fast32_t>(m_time) % static_cast<::std::uint_fast32_t>(amount)
    };
    m_time = newValue;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// External types operators
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> [[ nodiscard ]] constexpr auto operator+(
    const auto& lhs,
    const ::xrn::util::BasicTime<T>& rhs
) -> ::xrn::util::BasicTime<T>
{
    return ::xrn::util::BasicTime<T>::createAsMilliseconds(lhs) + rhs;
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> [[ nodiscard ]] constexpr auto operator-(
    const auto& lhs,
    const ::xrn::util::BasicTime<T>& rhs
) -> ::xrn::util::BasicTime<T>
{
    return ::xrn::util::BasicTime<T>::createAsMilliseconds(lhs) - rhs;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Litteral definitions
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] constexpr auto ::xrn::util::literal::operator""_s(
    long double amount
) -> ::xrn::Time
{
    return ::xrn::Time::createAsSeconds(amount);
}

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] constexpr auto ::xrn::util::literal::operator""_s(
    long long unsigned amount
) -> ::xrn::Time
{
    return ::xrn::Time::createAsSeconds(amount);
}

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] constexpr auto ::xrn::util::literal::operator""_ms(
    long double amount
) -> ::xrn::Time
{
    return ::xrn::Time::createAsMilliseconds(amount);
}

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] constexpr auto ::xrn::util::literal::operator""_ms(
    long long unsigned amount
) -> ::xrn::Time
{
    return ::xrn::Time::createAsMilliseconds(amount);
}

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] constexpr auto ::xrn::util::literal::operator""_us(
    long double amount
) -> ::xrn::Time
{
    return ::xrn::Time::createAsMicroseconds(amount);
}

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] constexpr auto ::xrn::util::literal::operator""_us(
    long long unsigned amount
) -> ::xrn::Time
{
    return ::xrn::Time::createAsMicroseconds(amount);
}

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] constexpr auto ::xrn::util::literal::operator""_ns(
    long double amount
) -> ::xrn::Time
{
    return ::xrn::Time::createAsNanoseconds(amount);
}

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] constexpr auto ::xrn::util::literal::operator""_ns(
    long long unsigned amount
) -> ::xrn::Time
{
    return ::xrn::Time::createAsNanoseconds(amount);
}
