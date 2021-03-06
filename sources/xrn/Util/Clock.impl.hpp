#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> ::xrn::util::BasicClock<T>::BasicClock() noexcept
    : m_timePoint{ ::std::chrono::high_resolution_clock::now() }
{}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Basic
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> void ::xrn::util::BasicClock<T>::reset()
{
    m_timePoint = ::std::chrono::high_resolution_clock::now();
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> auto ::xrn::util::BasicClock<T>::getElapsed()
    -> BasicClock<T>::Type
{
    return BasicClock<T>::Type{ static_cast<BasicClock<T>::Type::Type>(
        ::std::chrono::duration<typename BasicClock<T>::Type::Type>(
            ::std::chrono::high_resolution_clock::now() - m_timePoint
        ).count() * 1000.0
    ) };
}

///////////////////////////////////////////////////////////////////////////
template <
    typename T
> auto ::xrn::util::BasicClock<T>::restart()
    -> BasicClock<T>::Type
{
    auto ret{ this->getElapsed() };
    this->reset();
    return ret;
}
