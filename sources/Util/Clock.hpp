#pragma once

///////////////////////////////////////////////////////////////////////////
// Header-implimentation
///////////////////////////////////////////////////////////////////////////
#include <Util/Time.hpp>



namespace xrn::util {

///////////////////////////////////////////////////////////////////////////
/// \brief Simplifies time measures
/// \ingroup util
///
/// \include Clock.hpp <Util/Clock.hpp>
///
/// It provide an high resolution clock thanks to the c++ standards
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
