#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Ecs/Component/AComponent.hpp>
#include <Ecs/Detail/Constraint.hpp>



namespace xrn::ecs {

///////////////////////////////////////////////////////////////////////////
/// \brief Simplifies time measures
/// \ingroup ecs
///
/// \include Signature.hpp <Ecs/Signature.hpp>
///
/// ::xrn::Signature's purpuse is to tracks the components contained by a
/// class (mainly an ::xrn::ecs::Entity). It contains a bit for every
/// component declared in the Ecs/Component/Declaration.hpp. This bit is always
/// either true or false.
/// ::xrn::Signature can be generated and used at compile time through
/// constexpr methods.
///
/// Usage example:
/// \code
/// \endcode
///
/// \see ::xrn::ecs::component::AComponent, ::xrn::ecs::Entity
///
///////////////////////////////////////////////////////////////////////////
class Signature {

public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // static elements
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Constructs a ::xrn::ecs::Signature
    ///
    /// The ::xrn::ecs::Signature will be constructed from the Types given as
    /// template parameter. Even tho only component types will be used, the
    /// function accepts all types.
    ///
    /// \warning This function can only be used at compile time.
    ///
    /// \tparam Types All types are accepted, but only component types will be
    ///         used to construct the signature
    ///
    /// \return ::xrn::ecs::Signature just created
    ///
    /// \see ::xrn::ecs::component::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename... Types
    > [[ nodiscard ]] static consteval auto generate() noexcept
        -> ::xrn::ecs::Signature;

public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    /// Constructs an empty ::xrn::ecs::Signature.
    ///
    ///////////////////////////////////////////////////////////////////////////
    explicit constexpr Signature() noexcept;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Setters
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Adds components to the signature
    ///
    /// \tparam ComponentTypes Components to add to the signature
    ///
    /// Same as set()
    ///
    /// \see set(), ::xrn::ecs::component::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > constexpr void add();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Adds components to the signature
    ///
    /// \tparam ComponentTypes Components to add to the signature
    ///
    /// Same as add()
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > constexpr void set();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes components from the signature
    ///
    /// \tparam ComponentTypes Components to remove from the signature
    ///
    /// Same as reset()
    ///
    /// \see reset(), ::xrn::ecs::component::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > constexpr void remove();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes components from the signature
    ///
    /// \tparam ComponentTypes Components to remove from the signature
    ///
    /// Same as remove()
    ///
    /// \see remove(), ::xrn::ecs::component::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > constexpr void reset();



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Getters
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether the component is contained
    ///
    /// Checks whether the component given as parameter is contained.
    ///
    /// \tparam ComponentTypes Component to check
    ///
    /// \return True if the component is present, false otherwise
    ///
    /// \see containsAll(), ::xrn::ecs::component::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] constexpr auto get() const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether the component is contained
    ///
    /// Checks whether the component given as parameter is contained.
    ///
    /// \tparam component Component to check
    ///
    /// \return True if the component is present, false otherwise
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto get(
        ::xrn::ecs::detail::constraint::isComponent auto& component
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether the component is contained
    ///
    /// Checks whether the component given as parameter is contained.
    ///
    /// \tparam componentId Components to check
    ///
    /// \return True if the component is present, false otherwise
    ///
    /// \see containsAll(), ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto get(
        ::xrn::Id componentId
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether the component is contained
    ///
    /// Checks whether the component given as parameter is contained.
    /// Same as get().
    ///
    /// \param component Component to check
    ///
    /// \return True if the component is present, false otherwise
    ///
    /// \see get(), ::xrn::ecs::component::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto operator[](
        ::xrn::ecs::detail::constraint::isComponent auto& components
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether the component is contained
    ///
    /// Checks whether the component given as id as parameter is contained.
    /// Same as get().
    ///
    /// \param componentId Component to check
    ///
    /// \return True if the component is present, false otherwise
    ///
    /// \see get(), ::xrn::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto operator[](
        ::xrn::Id componentId
    ) const
        -> bool;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Comparison
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether the signature is contained
    ///
    /// Same as containsAll().
    ///
    /// \param Signature Signature to check
    ///
    /// \return True if all the components are present, false otherwise
    ///
    /// \see containsAll()
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto contains(
        const ::xrn::ecs::Signature& signature
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether the components are present in the signature
    ///
    /// Same as containsAll().
    ///
    /// \tparam ComponentTypes Components to check
    ///
    /// \return True if all the components are present, false otherwise
    ///
    /// \see containsAll(), ::xrn::ecs::component::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > [[ nodiscard ]] constexpr auto contains() const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether the components are present in the signature
    ///
    /// Same as containsAll().
    ///
    /// \param components Components to check
    ///
    /// \return True if all the components are present, false otherwise
    ///
    /// \see containsAll(), ::xrn::ecs::component::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto contains(
        const ::xrn::ecs::detail::constraint::isComponent auto&... components
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether the components are present in the signature
    ///
    /// Same as containsAll().
    ///
    /// \param components Components to check
    ///
    /// \return True if all the components are present, false otherwise
    ///
    /// \see containsAll(), ::xrn::util::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto contains(
        const ::xrn::ecs::detail::constraint::isId auto&... componentIds
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether the signature is contained
    ///
    /// Same as contains().
    ///
    /// \param Signature Signature to check
    ///
    /// \return True if all the components are present, false otherwise
    ///
    /// \see contains()
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto containsAll(
        const ::xrn::ecs::Signature& signature
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether the components are present in the signature
    ///
    /// Same as contains().
    ///
    /// \tparam ComponentsTypes Components to check
    ///
    /// \return True if all the components are present, false otherwise
    ///
    /// \see contains(), ::xrn::ecs::component::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > [[ nodiscard ]] constexpr auto containsAll() const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether the components are present in the signature
    ///
    /// Same as contains().
    ///
    /// \param components Components to check
    ///
    /// \return True if all the components are present, false otherwise
    ///
    /// \see contains(), ::xrn::ecs::component::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto containsAll(
        const ::xrn::ecs::detail::constraint::isComponent auto&... components
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether the components are present in the signature
    ///
    /// Same as contains().
    ///
    /// \param componentIds Ids of the components to check
    ///
    /// \return True if all the components are present, false otherwise
    ///
    /// \see contains(), ::xrn::util::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto containsAll(
        const ::xrn::ecs::detail::constraint::isId auto&... componentIds
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether it contains any of the component of the signature
    ///        given as parameter
    ///
    /// \param Signature Signature to check
    ///
    /// \return True if all the components are present, false otherwise
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto containsAny(
        const ::xrn::ecs::Signature& signature
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether at least a component is present in the signature
    ///
    /// Checks whether at least one component from the ComponentTypes given as
    /// template parameter is present in the signature.
    ///
    /// \param components Components to check
    ///
    /// \return True if at least one components is present, false otherwise
    ///
    /// \see testAny(), ::xrn::ecs::component::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > [[ nodiscard ]] constexpr auto containsAny() const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether at least a component is present in the signature
    ///
    /// Checks whether at least one component from the components given as
    /// parameter is present in the signature.
    ///
    /// \param components Components to check
    ///
    /// \return True if at least one components is present, false otherwise
    ///
    /// \see testAny(), ::xrn::ecs::component::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto containsAny(
        const ::xrn::ecs::detail::constraint::isComponent auto&... components
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether at least a component is present in the signature
    ///
    /// Checks whether at least one component from the components given as
    /// parameter is present in the signature.
    ///
    /// \param componentIds Ids of the components to check
    ///
    /// \return True if at least one components is present, false otherwise
    ///
    /// \see testAny(), ::xrn::util::Id
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto containsAny(
        const ::xrn::ecs::detail::constraint::isId auto&... componentIds
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether none of the component is present in the signature
    ///
    /// \param Signature Signature to check
    ///
    /// \return True if all the components are present, false otherwise
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto containsNone(
        const ::xrn::ecs::Signature& signature
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether none of the component is present in the signature
    ///
    /// Checks whether one of the ComponentTypes given as template parameter
    /// is present in the signature.
    ///
    /// \param components Components to check
    ///
    /// \return True if no component is present, false otherwise
    ///
    /// \see testNone(), ::xrn::ecs::component::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > [[ nodiscard ]] constexpr auto containsNone() const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether none of the component is present in the signature
    ///
    /// Checks whether one of the components given as parameter is present in
    /// the signature.
    ///
    /// \param components Components to check
    ///
    /// \return True if no component is present, false otherwise
    ///
    /// \see testNone(), ::xrn::ecs::component::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto containsNone(
        const ::xrn::ecs::detail::constraint::isComponent auto&... components
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether none of the component is present in the signature
    ///
    /// Checks whether one of the component Ids given as parameter is present
    /// in the signature.
    ///
    /// \param componentIds Ids of the components to check
    ///
    /// \return True if no component is present, false otherwise
    ///
    /// \see testNone(), ::xrn::ecs::component::AComponent
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto containsNone(
        const ::xrn::ecs::detail::constraint::isId auto&... componentIds
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether the signature are identical
    ///
    /// \param Signature Signature to check
    ///
    /// \return True if the signatures are identical, false otherwise
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto operator==(
        const ::xrn::ecs::Signature& signature
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether the signature are not identical
    ///
    /// \param Signature Signature to check
    ///
    /// \return True if the signatures are different, false otherwise
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto operator!=(
        const ::xrn::ecs::Signature& signature
    ) const
        -> bool;



private:

    ::cbitset::Cbitset<::xrn::ecs::component::maxId> m_bitset{};

};

} // namespace xrn::ecs



///////////////////////////////////////////////////////////////////////////
/// \brief Write the content of the signature to an ::std::ostream
///
///////////////////////////////////////////////////////////////////////////
auto operator<<(
    ::std::ostream& os,
    const ::xrn::ecs::Signature& signature
) -> ::std::ostream&;



///////////////////////////////////////////////////////////////////////////
// Header-implimentation
///////////////////////////////////////////////////////////////////////////
#include <Ecs/Signature.impl.hpp>
