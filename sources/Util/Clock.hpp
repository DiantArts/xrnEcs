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
/// ::xrn::util::Clock provide an high resolution clock allowing precise
/// elapsed time measures.
///
///
/// Usage example:
/// \code
/// \endcode
///
/// \see ::xrn::Time
///
///////////////////////////////////////////////////////////////////////////
template <
    typename T
> class BasicClock {

public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // static elements
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Type internally contained by the class
    ///
    ///////////////////////////////////////////////////////////////////////////
    using Type = T;



public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // *structors
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    /// Constructs a clock and starts it automatically. The return types will
    /// be of the type given as template parameter. By default, the internal
    /// type is ::xrn::Time.
    ///
    /// \see ::xrn::Time
    ///
    ///////////////////////////////////////////////////////////////////////////
    explicit BasicClock() noexcept;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Basic
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Restarts the clock
    ///
    /// Puts the time counter back to zero.
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline void reset();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Get the time elapsed since the last reset
    ///
    /// Returns the time elapsed sine the last reset of the clock. The clock is
    /// reseted when constructed or when restart() or reset() is called.
    ///
    /// \param amount Time in milliseconds
    ///
    /// \see reset(), restart()
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto getElapsed()
        -> BasicClock<T>::Type;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Fusion between getElapsed() and reset()
    ///
    /// Puts the time counter back to zero returns the elapsed time since the
    /// last clock reset.
    ///
    /// \see getElapsed(), reset()
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto restart()
        -> BasicClock<T>::Type;



private:

    ///////////////////////////////////////////////////////////////////////////
    // Time of the last clock reset (constructor, restart() or reset())
    ///////////////////////////////////////////////////////////////////////////
    ::std::chrono::time_point<std::chrono::high_resolution_clock> m_timePoint;

};

} // namespace xrn::ecs



///////////////////////////////////////////////////////////////////////////
// Template specialization
///////////////////////////////////////////////////////////////////////////

namespace xrn::util { using Clock = ::xrn::util::BasicClock<::xrn::Time>; }
namespace xrn { using Clock = ::xrn::util::Clock; }



///////////////////////////////////////////////////////////////////////////
// Header-implimentation
///////////////////////////////////////////////////////////////////////////
#include <Util/Clock.impl.hpp>
