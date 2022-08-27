#pragma once

#include <xrn/Meta/Constraint.hpp>

namespace xrn::meta {

///////////////////////////////////////////////////////////////////////////
/// \brief Execute actions for each types
/// \ingroup meta
///
/// \include ForEach.hpp <xrn/Meta/ForEach.hpp>
///
/// This class is a part of the ::xrn::meta Library designed to facilitate
/// usage of template metaprgramming.
///
/// ::xrn::meta::ForEach structure's purpuse is to execute different
/// actions on a variadic list of type given as template parameters argment
/// to the class
///
/// The user can then decide to execute funtions or comparisons for each of
/// them
///
/// \tparam Types Types to execute actions on
///
///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> struct ForEach
{
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // methods
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Runs a function for each types
    ///
    /// This function runs the function given as template parameter of the
    /// methods for each template parameter of the struct
    ///
    /// The user can also provide arguments that will be passed to the function
    /// given as template parameter of the method
    ///
    /// \tparam function Function to execute for each types
    ///
    /// \param args Arguments to pass to the user provided function
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        auto function
    > static constexpr void run(
        auto&&... args
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Runs a function only for the matching types
    ///
    /// Same as run() but only for the matching types
    ///
    /// \tparam function Function to execute for each types
    /// \tparam GivenTypes Types to compare to Types, If it contains, runs the
    ///         function
    ///
    /// \param args Arguments to pass to the user provided function
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        auto function,
        ::xrn::meta::constraint::contains<Types...>... GivenTypes
    > static constexpr void runForTypes(
        auto&&... args
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Runs a function for each types
    ///
    /// Same function as ::xrn::meta::ForEach::run except that it returns true
    /// if every call of the function have been true for every type provided
    ///
    /// \return True if every call returns true
    ///
    /// \tparam function Function to execute for each types
    ///
    /// \param args Arguments to pass to the user provided function
    ///
    /// \see ::xrn::meta::ForEach::run
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        auto function
    > [[ nodiscard ]] static constexpr auto compareAnd(
        auto&&... args
    ) -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Runs a function for each types
    ///
    /// Same function as ::xrn::meta::ForEach::run except that it returns true
    /// as soon as a call of the user provided function returns true. Function
    /// given as template parameter of the method
    ///
    /// \return True if at least one call returns true
    ///
    /// \tparam function Function to execute for each types
    ///
    /// \param args Arguments to pass to the user provided function
    ///
    /// \see ::xrn::meta::ForEach::run
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        auto function
    > [[ nodiscard ]] static constexpr auto compareOr(
        auto&&... args
    ) -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Search a Type given as template parameter
    ///
    /// Search a specific type in all the types given as parameter of template
    /// of the class
    ///
    /// \return True if the Type is present at least once
    ///
    /// \tparam Type Type to search
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename Type
    > [[ nodiscard ]] static constexpr auto hasType()
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Find the position in the template parameter pack of the class
    ///
    /// The program is ill-formed if the ComparedType is not present within the
    /// list of types given as template parameter pack of the class
    ///
    /// \return Index within the template paramater pack
    ///
    /// \tparam ComparedType Type to search
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename ComparedType
    > [[ nodiscard ]] static constexpr auto getPosition()
        -> ::std::size_t;
};

} // namespace xrn::meta



///////////////////////////////////////////////////////////////////////////
// Header-implimentation
///////////////////////////////////////////////////////////////////////////
#include <xrn/Meta/ForEach.impl.hpp>
