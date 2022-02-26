#pragma once

///////////////////////////////////////////////////////////////////////////
// Header-implimentation
///////////////////////////////////////////////////////////////////////////
#include <Util/Time.hpp>



namespace xrn::util {

///////////////////////////////////////////////////////////////////////////
/// \brief 
/// \ingroup ecs
///
/// \include Clock.hpp <Util/Clock.hpp>
///
/// ::xrn::Clock's purpuse is to represent and uniform time manipulations
///
/// Usage example:
/// \code
/// \endcode
///
/// \see ::xrn::Time
///
///////////////////////////////////////////////////////////////////////////
class Clock {

public:

    using Type = ::xrn::Time;



public:

    // ------------------------------------------------------------------ *structors

    Clock();



    // ------------------------------------------------------------------ Get

    [[ nodiscard ]] auto getElapsed()
        -> Clock::Type;

    [[ nodiscard ]] auto getElapsedRestart()
        -> Clock::Type;

    void restart();



private:

    ::std::chrono::time_point<std::chrono::high_resolution_clock> m_lastCallTime;

};



} // namespace xrn::ecs

namespace xrn { using Clock = ::xrn::util::Clock; }
