#pragma once

///////////////////////////////////////////////////////////////////////////
// Implementation header
///////////////////////////////////////////////////////////////////////////
#include <xrn/Meta/Tuple.impl.hpp>



namespace xrn::meta {

///////////////////////////////////////////////////////////////////////////
/// \brief Execute actions for each type
/// \ingroup meta
///
/// \include Tuple.hpp <xrn/Meta/Tuple.hpp>
///
/// This class is a part of the ::xrn::meta Library designed to facilitate
/// usage of template metaprgramming.
///
/// ::xrn::meta::Tuple structure's purpuse is to concat types to group them
/// under a single type that the ::xrn::meta library is aware of.
/// It is possible to concat two ::xrn::meta::Tuple, if one of the
/// ::xrn::meta::Tuple is the first template argument of the second.
/// Otherwise, the ::xrn::meta::Tuple acts as a Type like others.
///
/// \tparam Types Types to execute actions on
///
///////////////////////////////////////////////////////////////////////////
template <typename... ArgTypes> using Tuple = ::xrn::meta::detail::Tuple<ArgTypes...>::Type;

} // namespace xrn::meta
