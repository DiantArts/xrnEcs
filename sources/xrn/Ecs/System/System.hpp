#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs/Signature.hpp>
#include <xrn/Ecs/Entity.hpp>
#include <xrn/Ecs/Component.hpp>
#include <xrn/Ecs/System/ASystem.hpp>
#include <xrn/Ecs/System/Detail/SystemFiller.hpp>



namespace xrn::ecs::system {

///////////////////////////////////////////////////////////////////////////
/// \brief Representation of a system
/// \ingroup ecs-system
///
/// \include System.hpp <xrn/Ecs/System/System.hpp>
///
/// ::xrn::ecs::system::System inherits from ::xrn::ecs::system::ASystem
/// and represents how a general system. It is the kind of system the user
/// is supposed to manipulate. Those systems are pushed as
/// ::xrn::ecs::system::ASystem inside a ::xrn::ecs::system::Container.
/// This class is aliased with ::xrn::ecs::System.
///
/// \tparam function Function to create a system from
/// \tparam Types    Types (usually Abilities) that the entity must possess
///                  to use the System
///
/// Usage example:
/// \code
/// using namespace ::xrn::ecs::component::test;
/// ::xrn::ecs::component::Container components;
/// ::xrn::ecs::entity::Container entities{ components };
///
/// auto e1Id{ entities.emplace<ComponentA>().getId() };
/// auto e2Id{ entities.emplace<ComponentB>().getId() };
/// auto e3Id{ entities.emplace<ComponentA, ComponentB>().getId() };
///
/// ::xrn::ecs::System system{ detail::function1 };
/// ::xrn::Clock clock;
/// system.run(clock.restart(), entities);
///
/// components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value // 1;
/// components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value // 0;
/// components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value // 1;
/// components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value // 0;
/// \endcode
///
/// \see ::xrn::ecs::system::ASystem, ::xrn::ecs::system::Container
///
///////////////////////////////////////////////////////////////////////////
template <
    typename FunctionType
> class System
    : public ::xrn::ecs::system::ASystem
{

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
    ///////////////////////////////////////////////////////////////////////////
    constexpr System(
        FunctionType function
    );



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Run
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Runs the system
    ///
    /// \param deltaTime Represents the time passed by the user. It is usually
    ///                  used to know the elapsed since the last runs of
    ///                  systems
    /// \param entities  Container of entities that the system will act upon
    ///
    /// \see ::xrn::util::BasicTime, ::xrn::ecs::entity::Container
    ///
    ///////////////////////////////////////////////////////////////////////////
    constexpr void run(
        ::xrn::Time deltaTime,
        ::xrn::ecs::entity::Container& entities
    ) override;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Runs the system
    ///
    /// \param deltaTime Represents the time passed by the user. It is usually
    ///                  used to know the elapsed since the last runs of
    ///                  systems
    /// \param entities  Container of entities that the system will act upon
    ///
    /// \see ::xrn::util::BasicTime, ::xrn::ecs::entity::Container
    ///
    ///////////////////////////////////////////////////////////////////////////
    constexpr void operator()(
        ::xrn::Time deltaTime,
        ::xrn::ecs::entity::Container& entities
    );



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Add to signature
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Adds components and abilities to the signature
    ///
    /// \tparam Types Components and abilities to add to the signature
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isEcsRegistered... Types
    > constexpr void addToSignature();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Adds components to the signature
    ///
    /// \tparam ComponentTypes Components to add to the signature
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > constexpr void addComponentsToSignature();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Adds abilities to the signature
    ///
    /// \tparam AbilityTypes Abilities to add to the signature
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isAbility... AbilityTypes
    > constexpr void addAbilitiesToSignature();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Adds components to the signature
    ///
    /// \param componentIds Component Ids to add to the signature
    ///
    ///////////////////////////////////////////////////////////////////////////
    constexpr void addToSignature(
        ::xrn::ecs::detail::constraint::isId auto... componentIds
    );



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Remove from signature
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes components and abilities from the signature
    ///
    /// \tparam Types Components and abilities to remove from the signature
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isEcsRegistered... Types
    > constexpr void removeFromSignature();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes components from the signature
    ///
    /// \tparam ComponentTypes Components to remove from the signature
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > constexpr void removeComponentsFromSignature();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes abilities from the signature
    ///
    /// \tparam AbilityTypes Abilities to remove from the signature
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isAbility... AbilityTypes
    > constexpr void removeAbilitiesFromSignature();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes components from the signature
    ///
    /// \param componentIds Component Ids to remove from the signature
    ///
    ///////////////////////////////////////////////////////////////////////////
    constexpr void removeFromSignature(
        ::xrn::ecs::detail::constraint::isId auto... componentIds
    );



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Signature
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the signature of the system
    ///
    /// \see ::xrn::ecs::Signature
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto getSignature()
        -> ::xrn::ecs::Signature&;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the signature of the system
    ///
    /// \see ::xrn::ecs::Signature
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto getSignature() const
        -> const ::xrn::ecs::Signature&;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Banish
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Banishes components and abilities
    ///
    /// \tparam Types Components and abilities to banish
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isEcsRegistered... Types
    > constexpr void banish();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Banishes components
    ///
    /// \tparam ComponentTypes Components to banish
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > constexpr void banishComponents();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Banishes abilities
    ///
    /// \tparam AbilityTypes Abilities to banish
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isAbility... AbilityTypes
    > constexpr void banishAbilities();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Banishes components
    ///
    /// \param componentIds Component Ids to banish
    ///
    ///////////////////////////////////////////////////////////////////////////
    constexpr void banish(
        ::xrn::ecs::detail::constraint::isId auto... componentIds
    );



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Remove from signature
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes components and abilities from the signature
    ///
    /// \tparam Types Components and abilities to remove from the signature
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isEcsRegistered... Types
    > constexpr void removeFromBanishedSignature();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes components from the signature
    ///
    /// \tparam ComponentTypes Components to remove from the signature
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > constexpr void removeComponentsFromBanishedSignature();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes abilities from the signature
    ///
    /// \tparam AbilityTypes Abilities to remove from the signature
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        ::xrn::ecs::detail::constraint::isAbility... AbilityTypes
    > constexpr void removeAbilitiesFromBanishedSignature();

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Removes components from the signature
    ///
    /// \param componentIds Component Ids to remove from the signature
    ///
    ///////////////////////////////////////////////////////////////////////////
    constexpr void removeFromBanishedSignature(
        ::xrn::ecs::detail::constraint::isId auto... componentIds
    );



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Signature
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the signature of the system
    ///
    /// \see ::xrn::ecs::Signature
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto getBanishedSignature()
        -> ::xrn::ecs::Signature&;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the signature of the system
    ///
    /// \see ::xrn::ecs::Signature
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] constexpr auto getBanishedSignature() const
        -> const ::xrn::ecs::Signature&;



private:

    ::xrn::ecs::Signature m_signature{
        ::xrn::ecs::detail::meta::Function<FunctionType>::Arguments::signature
    };
    ::xrn::ecs::Signature m_banishedSignature{};

    FunctionType m_function;

};

} // namespace xrn::ecs::system



///////////////////////////////////////////////////////////////////////////
// Alias name
///////////////////////////////////////////////////////////////////////////
namespace xrn::ecs {
    template <
        typename FunctionType
    > using System = ::xrn::ecs::system::System<FunctionType>;
}



///////////////////////////////////////////////////////////////////////////
// Header-implimentation
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs/System/System.impl.hpp>
