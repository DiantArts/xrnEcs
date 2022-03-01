#pragma once

namespace xrn::util {

///////////////////////////////////////////////////////////////////////////
/// \brief Representation of the time in the xrn Project
/// \ingroup util
///
/// \include Id.hpp <Util/Id.hpp>
///
/// ::xrn::util::BasicFormardId's purpuse is to identify objects accross all
/// xrn Projects. This class can only increment, never decrement.
/// Ids are usually given with using an external counter to allow unique Ids.
/// ::xrn::Id and ::xrn::util::Id are aliases of
/// ::xrn::util::BasicFormardId<::std::size_t>.
///
/// Usage example:
/// \code
/// \endcode
///
///////////////////////////////////////////////////////////////////////////
template <
    typename T
> class BasicForwardId {

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

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Structure allowing Id hashage
    ///
    ///////////////////////////////////////////////////////////////////////////
    struct Hasher;



public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Constructs an Id from a value
    ///
    /// Constructs a ::xrn::util::Time containing a point in time.
    ///
    /// \param amount Time in milliseconds
    ///
    ///////////////////////////////////////////////////////////////////////////
    constexpr BasicForwardId(
        auto value
    ) noexcept;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Rule of 5
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Default destructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    constexpr ~BasicForwardId() noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Default copy constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    constexpr BasicForwardId(
        const ::xrn::util::BasicForwardId<T>& other
    ) noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Default copy assignment operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    constexpr auto operator=(
        const ::xrn::util::BasicForwardId<T>& other
    ) noexcept
        -> ::xrn::util::BasicForwardId<T>&;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Default move constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    constexpr BasicForwardId(
        ::xrn::util::BasicForwardId<T>&& other
    ) noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Default move assignment operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    constexpr auto operator=(
        ::xrn::util::BasicForwardId<T>&& other
    ) noexcept
        -> ::xrn::util::BasicForwardId<T>&;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Getters
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Returns the value of the Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto get() const
        -> BasicForwardId<T>::Type;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Returns the value of the Id as string
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto getAsString() const
        -> ::std::string;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Alias method of get()
    ///
    /// \see get()
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] inline constexpr operator BasicForwardId<T>::Type() const;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Alias method of getAsString()
    ///
    /// \see getAsString()
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] inline operator ::std::string() const;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Operations
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Pre-increment operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    constexpr auto operator++()
        -> ::xrn::util::BasicForwardId<T>&;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Post-increment operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    constexpr auto operator++(
        int
    ) -> ::xrn::util::BasicForwardId<T>;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Increment the Id
    ///
    /// Same as pre-increment operator but does not return anything
    ///
    ///////////////////////////////////////////////////////////////////////////
    constexpr void increment();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Compares with another Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto operator<=>(
        const ::xrn::util::BasicForwardId<T>& other
    ) const
        -> ::std::strong_ordering;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Compares with anything that can be compared with the internal
    /// type
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto operator<=>(
        const auto& other
    ) const
        -> ::std::strong_ordering;



private:

    ::xrn::util::BasicForwardId<T>::Type m_value;

};

} // namespace xrn::util



///////////////////////////////////////////////////////////////////////////
// Template specialization
///////////////////////////////////////////////////////////////////////////
namespace xrn::util { using Id = ::xrn::util::BasicForwardId<::std::size_t>; }
namespace xrn { using Id = ::xrn::util::Id; }



///////////////////////////////////////////////////////////////////////////
// Header-implimentation
///////////////////////////////////////////////////////////////////////////
#include <Util/Id.impl.hpp>
