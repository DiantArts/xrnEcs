#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Util/Clock.hpp>
#include <Ecs/System/System.hpp>
#include <Ecs/Component.hpp>
#include <Ecs/Entity.hpp>



namespace xrn::ecs::system {

///////////////////////////////////////////////////////////////////////////
/// \brief Representation a system in the xrn ecs Project
/// \ingroup ecs-system
///
/// \include System.hpp <Ecs/System/System.hpp>
///
/// ::xrn::ecs::system::System inherits from ::xrn::ecs::system::ASystem
/// and represents how a general system. It is the kind of system the user
/// is supposed to manipulate. Those systems are pushed as
/// ::xrn::ecs::system::ASystem inside a ::xrn::ecs::system::Container.
/// This class is aliased with ::xrn::ecs::System.
///
/// Usage example:
/// \code
/// \endcode
///
/// \see ::xrn::ecs::system::ASystem, ::xrn::ecs::system::Container
///
///////////////////////////////////////////////////////////////////////////
class Container {

public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Run
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Runs the systems
    ///
    /// Runs all the system contained by the container. The system matching
    /// will match the component signature and automatically send the arguments
    /// requiered to the system.
    ///
    /// \param deltaTime Represents the time passed by the user. It is usually
    ///                  used to know the elapsed since the last runs of
    ///                  systems
    /// \param entities  Container of entities that the system will act upon
    ///
    /// \see ::xrn::Time, ::xrn::ecs::entity::Container
    ///
    ///////////////////////////////////////////////////////////////////////////
    void run(
        ::xrn::Time t,
        ::xrn::ecs::entity::Container& entities
    );

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Runs the systems as const
    ///
    /// Runs all the system contained by the container. The system matching
    /// will match the component signature and automatically send the arguments
    /// requiered to the system.
    /// The systems will be run as const.
    ///
    /// \warning If the systems are run as const but their components are not,
    ///          it will print so to ::std::cerr and not run anything.
    ///
    /// \param deltaTime Represents the time passed by the user. It is usually
    ///                  used to know the elapsed since the last runs of
    ///                  systems
    /// \param entities  Container of entities that the system will act upon
    ///
    /// \see ::xrn::Time, ::xrn::ecs::entity::Container
    ///
    ///////////////////////////////////////////////////////////////////////////
    void run(
        ::xrn::Time t,
        const ::xrn::ecs::entity::Container& entities
    ) const;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Others
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Emplaces a systems
    ///
    /// Creates a system and push it to the container of systems.
    ///
    /// \tparam function Function to pass to the system
    /// \tparam Types    Types to pass to the system
    ///
    ///////////////////////////////////////////////////////////////////////////
    template <
        auto function,
        typename... Types
    > void emplace();



private:

    ::std::vector<::std::unique_ptr<::xrn::ecs::system::ASystem>> m_systems{};

};

} // namespace xrn::ecs::system



///////////////////////////////////////////////////////////////////////////
// Header-implimentation
///////////////////////////////////////////////////////////////////////////
#include <Ecs/System/Container.impl.hpp>
