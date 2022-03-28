#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Util/Clock.hpp>
#include <xrn/Ecs/Component.hpp>
#include <xrn/Ecs/Entity.hpp>
#include <xrn/Ecs/System/Constant/System.hpp>
#include <xrn/Ecs/System/Detail/Meta/Function.hpp>



namespace xrn::ecs::system::constant {

///////////////////////////////////////////////////////////////////////////
/// \brief Containers of const systems
/// \ingroup ecs-system
///
/// \include System.hpp <xrn/Ecs/System/System.hpp>
///
/// ::xrn::ecs::system::Container contains all the
/// ::xrn::ecs::system::System and allows to perform action on all systems
/// contained in a single method like ::xrn::ecs::system::Container::run().
///
/// Usage example:
/// \code
/// using namespace ::xrn::ecs::component::test;
///
/// ::xrn::Clock clock;
/// ::xrn::ecs::component::Container components;
/// ::xrn::ecs::entity::Container entities{ components };
/// auto e1Id{ entities.emplace<ComponentA>().getId() };
/// auto e2Id{ entities.emplace<ComponentB>().getId() };
/// auto e3Id{ entities.emplace<ComponentA, ComponentB>().getId() };
/// ::xrn::ecs::constant::system::Container systems;
///
/// auto function1{ [](ComponentA& a) { /* ... */ } }
/// auto function2{ [](ComponentB& b) { /* ... */ } }
/// auto function3{ [](ComponentA& a, ComponentB& b) { /* ... */ } }
///
/// systems.emplace(function1);
/// systems.emplace(function2);
/// systems.emplace(function3);
/// systems.run(clock.restart(), entities);
/// \endcode
///
/// \see ::xrn::ecs::system::System
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
    /// \see ::xrn::util::BasicForwardTime, ::xrn::ecs::entity::Container
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline void run(
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
    /// \brief Emplaces a const systems
    ///
    /// Creates a system and push it to the container of systems.
    ///
    /// \warning Calling this method with non-const arguments may leads to
    ///          undefined behaviors
    ///
    /// \tparam function Function to pass to the system
    /// \tparam Types    Types to pass to the system
    ///
    /// \see ::xrn::ecs::system::constant::ASystem
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto emplace(
        auto function
    ) -> ::xrn::ecs::constant::ASystem&;



private:

    ::std::vector<::std::unique_ptr<::xrn::ecs::constant::ASystem>> m_systems{};

};

} // namespace xrn::ecs::system



///////////////////////////////////////////////////////////////////////////
// Alias name
///////////////////////////////////////////////////////////////////////////
namespace xrn::ecs::system::constant { using Container = ::xrn::ecs::system::constant::Container; }
namespace xrn::ecs::constant::system { using Container = ::xrn::ecs::system::constant::Container; }
namespace xrn::ecs::system { using ConstContainer = ::xrn::ecs::system::constant::Container; }



///////////////////////////////////////////////////////////////////////////
// Header-implimentation
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs/System/Constant/Container.impl.hpp>
