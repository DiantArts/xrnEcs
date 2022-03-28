#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Util/Clock.hpp>
#include <xrn/Ecs/System/System.hpp>
#include <xrn/Ecs/Component.hpp>
#include <xrn/Ecs/Entity.hpp>



namespace xrn::ecs::system {

///////////////////////////////////////////////////////////////////////////
/// \brief Containers of systems
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
/// ::xrn::ecs::system::Container systems;
///
/// auto function1{ [](ComponentA& a) { ++a.value; } }
/// auto function2{ [](ComponentB& b) { ++b.value; } }
/// auto function3{ [](ComponentA& a, ComponentB& b) { ++a.value; ++b.value; } }
///
/// systems.emplace(function1);
/// systems.run(clock.restart(), entities);
/// systems.run(clock.restart(), entities);
/// systems.emplace(function2);
/// systems.run(clock.restart(), entities);
/// systems.emplace(function3);
/// systems.run(clock.restart(), entities);
/// components.get<ComponentA>(e1Id)->value // 4;
/// components.get<ComponentB>(e2Id)->value // 2;
/// components.get<ComponentA>(e3Id)->value // 5;
/// components.get<ComponentB>(e3Id)->value // 3;
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
    /// \see ::xrn::util::BasicTime, ::xrn::ecs::entity::Container
    ///
    ///////////////////////////////////////////////////////////////////////////
    inline void run(
        ::xrn::Time t,
        ::xrn::ecs::entity::Container& entities
    );



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
    /// \see ::xrn::ecs::system::ASystem
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto emplace(
        auto function
    ) -> ::xrn::ecs::ASystem&;



private:

    ::std::vector<::std::unique_ptr<::xrn::ecs::ASystem>> m_systems{};

};

} // namespace xrn::ecs::system



///////////////////////////////////////////////////////////////////////////
// Header-implimentation
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs/System/Container.impl.hpp>
