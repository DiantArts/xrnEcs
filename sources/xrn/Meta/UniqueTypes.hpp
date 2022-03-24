#pragma once

namespace xrn::meta {

///////////////////////////////////////////////////////////////////////////
/// \brief Checks if a all the types present in the list are unique
/// \ingroup meta
///
/// \include UniqueTpes.hpp <xrn/Meta/UniqueTypes.hpp>
///
/// This class is a part of the ::xrn::Meta Library designed to facilitate
/// usage of template metaprgramming
///
/// ::xrn::meta::UniqueTypes structure's purpuse is to check if all the types
/// present inside the variadic list of type given as template parameters are
/// unique
/// ::xrn::meta::UniqueTypes::value is true if all the types given as template
/// parameters are unique, false otherwise
///
/// \tparam Types Types to execute actions on
///
///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> struct UniqueTypes;

///////////////////////////////////////////////////////////////////////////
/// \brief Same as ::xrn::meta::UniqueTypes<Type...>::value
///
///////////////////////////////////////////////////////////////////////////
template <
    typename... Types
> inline constexpr const bool uniqueTypes_v = ::xrn::meta::UniqueTypes<Types...>::value;

} // namespace xrn::meta



///////////////////////////////////////////////////////////////////////////
// Header-implimentation
///////////////////////////////////////////////////////////////////////////
#include <xrn/Meta/UniqueTypes.impl.hpp>
