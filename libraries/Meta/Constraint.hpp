#pragma once

namespace xrn::meta::constraint {

///////////////////////////////////////////////////////////////////////////
/// \brief Checks whether the Type given as template parameter is an
///        ::xrn::ecs::entity::Entity
///
/// The comparison ignores cv-qualifiers, references (compares the type
/// referenced) and pointers (compares the type pointed)
///
/// \tparam Type to check
///
/// \return True if the Type given as template parameter is an
///         ::xrn::ecs::entity::Entity. False otherwise
///
/// \see ::xrn::ecs::entity::Entity
///
///////////////////////////////////////////////////////////////////////////
template <
    typename Type1,
    typename Type2
> concept sameAs = ::std::same_as<
        ::std::remove_cvref_t<::std::remove_pointer_t<Type1>>,
        ::std::remove_cvref_t<::std::remove_pointer_t<Type2>>
    >;

///////////////////////////////////////////////////////////////////////////
/// \brief Checks whether the Type given as template parameter is const
///
/// The comparison ignores cv-qualifiers and references (compares the type
/// referenced).
///
/// \tparam Type to check
///
/// \return True if the Type given as template parameter is an
///         ::xrn::ecs::entity::Entity. False otherwise
///
/// \see ::xrn::ecs::entity::Entity
///
///////////////////////////////////////////////////////////////////////////
template <
    typename Type
> concept isConst = ::std::is_const_v<::std::remove_reference_t<::std::remove_pointer_t<Type>>>;

///////////////////////////////////////////////////////////////////////////
/// \brief Is the value given to a function or method mutates the original
/// variable
///
/// Same as ::xrn::meta::constraint::isConst, but retirns.
///
/// \tparam Type to check
///
/// \return True if the Type given as template parameter is an
///         ::xrn::ecs::entity::Entity. False otherwise
///
/// \see ::xrn::ecs::entity::Entity
///
///////////////////////////////////////////////////////////////////////////
template <
    typename Type
> concept isMutable = (::std::is_pointer_v<Type> && !::std::is_const_v<::std::remove_pointer_t<Type>>)
    || (::std::is_reference_v<Type> && !::std::is_const_v<::std::remove_reference_t<Type>>);

} // namespace xrn::meta::constraint
