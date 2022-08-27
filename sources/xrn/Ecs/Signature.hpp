#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Cbitset/Cbitset.hpp>
#include <xrn/Meta/Constraint.hpp>
#include <xrn/Meta/ForEach.hpp>
#include <xrn/Ecs/Detail/Constraint.hpp>



namespace xrn::ecs {

///////////////////////////////////////////////////////////////////////////
/// \brief Simplifies time measures
/// \ingroup ecs
///
/// \include Signature.hpp <xrn/Ecs/Signature.hpp>
///
/// ::xrn::Signature's purpuse is to tracks the components contained by a
/// class (mainly an ::xrn::ecs::entity::Entity). It contains a bit for every
/// component declared in the xrn/Ecs/Component/Declaration.hpp. This bit is always
/// either true or false.
/// ::xrn::Signature can be generated and used at compile time through
/// constexpr methods.
///
/// Usage example:
/// \code
/// constexpr auto constexprSignature{ ::xrn::ecs::Signature<
///     ::xrn::ecs::component::test::ComponentA,
///     ::xrn::ecs::component::test::ComponentB
/// >::generate<
///     ::xrn::ecs::component::test::ComponentA,
///     ::xrn::ecs::component::test::ComponentB
/// >() };
/// auto runtimeSignature{
///     ::xrn::ecs::Signature<
///         ::xrn::ecs::component::test::ComponentA,
///         ::xrn::ecs::component::test::ComponentB
///     > ::generate<
///         ::xrn::ecs::component::test::ComponentA
///     >()
/// };
///
/// constexprSignature != runtimeSignature; // true
/// constexprSignature.containsNone(runtimeSignature); // false
/// constexprSignature.containsAll(runtimeSignature); // true
/// runtimeSignature.containsAll(constexprSignature); // false
/// \endcode
///
/// \see ::xrn::ecs::entity::Entity
///
///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> class Signature {

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
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...>... Types
    > [[ nodiscard ]] static consteval auto generate() noexcept
        -> ::xrn::ecs::Signature<ComponentTypes...>;



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
    // Set/Add
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Adds components and abilities to the signature
    ///
    /// \tparam Types Components and abilities to add to the signature
    ///
    /// Same as set()
    ///
    /// \see set()
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...>... Types
    > constexpr void add();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Adds components to the signature
    ///
    /// \param componentIds Component Ids to add to the signature
    ///
    /// Same as set()
    ///
    /// \see set(), ::xrn::util::BasicForwardId
    ///
    ///////////////////////////////////////////////////////////////////////////
    constexpr void add(
        ::xrn::ecs::detail::constraint::isId auto... componentIds
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Adds components and abilities to the signature
    ///
    /// \tparam Types Components and abilities to add to the signature
    ///
    /// Same as add()
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...>... Types
    > constexpr void set();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Adds components to the signature
    ///
    /// \param componentIds Component Ids to add to the signature
    ///
    /// Same as add()
    ///
    /// \see add(), ::xrn::util::BasicForwardId
    ///
    ///////////////////////////////////////////////////////////////////////////
    constexpr void set(
        ::xrn::ecs::detail::constraint::isId auto... componentIds
    );



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // reset/Remove
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes components and abilities from the signature
    ///
    /// \tparam Types Components and abilities to remove from the signature
    ///
    /// Same as reset()
    ///
    /// \see reset()
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...>... Types
    > constexpr void remove();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes components from the signature
    ///
    /// \param componentIds Component Ids to remove from the signature
    ///
    /// Same as reset()
    ///
    /// \see reset(), ::xrn::util::BasicForwardId
    ///
    ///////////////////////////////////////////////////////////////////////////
    constexpr void remove(
        ::xrn::ecs::detail::constraint::isId auto... componentIds
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes all components from the signature
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline void reset();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes components and abilities from the signature
    ///
    /// \tparam Types Components and abilities to remove from the signature
    ///
    /// Same as remove()
    ///
    /// \see remove()
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...>... Types
    > constexpr void reset();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes components from the signature
    ///
    /// \param componentIds Component Ids to remove from the signature
    ///
    /// Same as remove()
    ///
    /// \see remove(), ::xrn::util::BasicForwardId
    ///
    ///////////////////////////////////////////////////////////////////////////
    constexpr void reset(
        ::xrn::ecs::detail::constraint::isId auto... componentIds
    );



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Getters
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether the component or abilitiy is contained
    ///
    /// \tparam Types Component or ability to check
    ///
    /// \return True if present, false otherwise
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...> Type
    > [[ nodiscard ]] constexpr auto get() const
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
    /// \see ::xrn::util::BasicForwardId
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto get(
        ::xrn::Id componentId
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
    /// \see get(), ::xrn::util::BasicForwardId
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
        const ::xrn::ecs::Signature<ComponentTypes...>& signature
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether the components and abilities are present in the
    ///        signature
    ///
    /// Same as containsAll().
    ///
    /// \tparam Types Components and abilities to check
    ///
    /// \return True if all the components and abilities are present, false
    ///         otherwise
    ///
    /// \see containsAll()
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...>... Types
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
    /// \see containsAll(), ::xrn::util::BasicForwardId
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto contains(
        ::xrn::ecs::detail::constraint::isId auto... componentIds
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
        const ::xrn::ecs::Signature<ComponentTypes...>& signature
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether the components and abilities are present in the
    ///        signature
    ///
    /// Same as contains().
    ///
    /// \tparam Types Components and abilities to check
    ///
    /// \return True if all the components are present, false otherwise
    ///
    /// \see contains()
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...>... Types
    > [[ nodiscard ]] constexpr auto containsAll() const
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
    /// \see contains(), ::xrn::util::BasicForwardId
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto containsAll(
        ::xrn::ecs::detail::constraint::isId auto... componentIds
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
        const ::xrn::ecs::Signature<ComponentTypes...>& signature
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether it contains any of the component and abilities of
    ///        the signature given as parameter
    ///
    /// \tparam Types Components and abilities to check
    ///
    /// \return True if at least one components is present, false otherwise
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...>... Types
    > [[ nodiscard ]] constexpr auto containsAny() const
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
    /// \see ::xrn::util::BasicForwardId
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto containsAny(
        ::xrn::ecs::detail::constraint::isId auto... componentIds
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
        const ::xrn::ecs::Signature<ComponentTypes...>& signature
    ) const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether none of the component and abilities are present
    ///        in the signature
    ///
    /// \tparam ComponentTypes Components to check
    ///
    /// \return True if no component is present, false otherwise
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::meta::constraint::contains<ComponentTypes...>... Types
    > [[ nodiscard ]] constexpr auto containsNone() const
        -> bool;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Checks whether none of the component is present in the signature
    ///
    /// \param componentIds Ids of the components to check
    ///
    /// \return True if no component is present, false otherwise
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto containsNone(
        ::xrn::ecs::detail::constraint::isId auto... componentIds
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
        const ::xrn::ecs::Signature<ComponentTypes...>& signature
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
        const ::xrn::ecs::Signature<ComponentTypes...>& signature
    ) const
        -> bool;



private:

    ::cbitset::Cbitset<sizeof...(ComponentTypes)> m_bitset{};

};

} // namespace xrn::ecs



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// ::std::ostream
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/// \brief Write the content of the signature to an ::std::ostream
///
///////////////////////////////////////////////////////////////////////////
template <
    typename... ComponentTypes
> inline auto operator<<(
    ::std::ostream& os,
    const ::xrn::ecs::Signature<ComponentTypes...>& signature
) -> ::std::ostream&;



///////////////////////////////////////////////////////////////////////////
// Header-implimentation
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs/Signature.impl.hpp>
