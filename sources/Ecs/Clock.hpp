#pragma once

#include <Ecs/Time.hpp>



namespace xrn::ecs {



class Clock {

public:

    using Type = ::xrn::ecs::Time;



public:

    // ------------------------------------------------------------------ *structors

    Clock();

    ~Clock();



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
