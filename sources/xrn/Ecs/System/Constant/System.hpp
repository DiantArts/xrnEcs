#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs/Signature.hpp>
#include <xrn/Ecs/Entity.hpp>
#include <xrn/Ecs/Component.hpp>
#include <xrn/Ecs/System/Constant/ASystem.hpp>
#include <xrn/Ecs/System/Detail/SystemFiller.hpp>



namespace xrn::ecs::system::constant {

///////////////////////////////////////////////////////////////////////////
/// \brief Representation a system in the xrn ecs Project
/// \ingroup ecs-system
///
/// \include System.hpp <xrn/Ecs/System/System.hpp>
///
/// ::xrn::ecs::system::constant::System inherits from
/// ::xrn::ecs::system::constant::ASystem and represents how a general
/// system. It is the kind of system the user is supposed to manipulate.
/// Those systems are pushed as ::xrn::ecs::system::constant::ASystem inside a
/// ::xrn::ecs::system::Container.
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
/// ::xrn::ecs::System<detail::function1> system;
/// ::xrn::Clock clock;
/// system(clock.restart(), entities);
///
/// components.get<::xrn::ecs::component::test::ComponentA>(e1Id)->value // 1;
/// components.get<::xrn::ecs::component::test::ComponentB>(e2Id)->value // 0;
/// components.get<::xrn::ecs::component::test::ComponentA>(e3Id)->value // 1;
/// components.get<::xrn::ecs::component::test::ComponentB>(e3Id)->value // 0;
/// \endcode
///
/// \see ::xrn::ecs::system::constant::ASystem, ::xrn::ecs::system::Container
///
///////////////////////////////////////////////////////////////////////////
template <
    typename FunctionType
> class System
    : public ::xrn::ecs::system::constant::ASystem
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
    /// \brief Runs the system as const
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
        const ::xrn::ecs::entity::Container& entities
    ) const override;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Runs the system as const
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
        const ::xrn::ecs::entity::Container& entities
    ) const;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Others
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Gets the signature of the system
    ///
    /// \see ::xrn::ecs::Signature
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] static consteval auto getSignature()
        -> ::xrn::ecs::Signature;



private:

    static inline constexpr const auto m_signature{
        ::xrn::ecs::detail::meta::Function<FunctionType>::Arguments::signature
    };

    FunctionType m_function;

};

} // namespace xrn::ecs::system::constant



///////////////////////////////////////////////////////////////////////////
// Alias name
///////////////////////////////////////////////////////////////////////////
namespace xrn::ecs::constant {
    template <
        typename FunctionType
    > using System = ::xrn::ecs::system::constant::System<FunctionType>;
}
namespace xrn::ecs {
    template <
        typename FunctionType
    > using ConstSystem = ::xrn::ecs::constant::System<FunctionType>;
}



///////////////////////////////////////////////////////////////////////////
// Header-implimentation
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs/System/Constant/System.impl.hpp>
