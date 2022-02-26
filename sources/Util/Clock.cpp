#include <pch.hpp>
#include <Util/Clock.hpp>


// ------------------------------------------------------------------ *structors

::xrn::util::Clock::Clock()
    : m_lastCallTime{ ::std::chrono::high_resolution_clock::now() }
{}



// ------------------------------------------------------------------ Get

auto ::xrn::util::Clock::getElapsed()
    -> Clock::Type
{
    return Clock::Type{ static_cast<Clock::Type::Type>(::std::chrono::duration<Clock::Type::Type>(
        ::std::chrono::high_resolution_clock::now() - m_lastCallTime
    ).count() * 1000.0f) };
}

auto ::xrn::util::Clock::getElapsedRestart()
    -> Clock::Type
{
    auto saveLastCallTime{ ::std::chrono::high_resolution_clock::now() };
    m_lastCallTime = ::std::chrono::high_resolution_clock::now();
    return Clock::Type{ static_cast<Clock::Type::Type>(::std::chrono::duration<Clock::Type::Type>(
        m_lastCallTime - saveLastCallTime
    ).count() * 1000.0f) };
}

void ::xrn::util::Clock::restart()
{
    m_lastCallTime = ::std::chrono::high_resolution_clock::now();
}
