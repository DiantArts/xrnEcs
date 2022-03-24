#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs/Entity.hpp>
#include <xrn/Ecs/Component.hpp>
#include <xrn/Ecs/System.hpp>



///////////////////////////////////////////////////////////////////////////
/// \defgroup ecs ECS module
///
/// The ::xrn::ecs library is designed to facilitate the usage of Ecs
/// architectures.
///
///////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////
/// \mainpage
///
/// \section welcome Welcome
/// Welcome to the xrn Ecs documentation. Here you will find a detailed
/// view of all the classes and functions.<br/>
///
/// \section example Short example
/// Before showing the code, it is important to note that components used
/// in the example, as well as all the components and abilities must be
/// declared inside the xrn/Ecs/Component/Declaration.hpp file, with the macros
/// COMPONENT(), COMPONENT_IN_NAMESPACE(), ABILITY() and
/// ABILITY_IN_NAMESPACE().
///
/// Here is a short example:
///
/// \code
/// #include <xrn/Ecs.hpp>
///
/// int main()
/// {
///     using namespace ::xrn::ecs::component::test;
///
///     // Creating the ECS containers needed
///     // Containing all the components of the program
///     ::xrn::ecs::component::Container components;
///     // Containing all the entities of the program, links the component container to it
///     ::xrn::ecs::entity::Container entities{ components };
///     // Systems of the program. Systems can be applied on different component/entity containers
///     ::xrn::ecs::system::Container systems;
///     // Const systems are normal systems that are used to affect other things than component. like drawing to the screen
///     ::xrn::ecs::system::ConstContainer constSystems;
///
///     // Creating entities
///     // Create an entity with a single component and keep its ID to use it later
///     auto entityId1{ entities.emplace<ComponentA>().getId() };
///     // Create an entity with a multiple components and keep its ID aswell
///     auto entityId2{ entities.emplace(ComponentA{}, ComponentB{ 5 }).getId() };
///
///     // emplacing all the system that will be executed each time systems.run() is called
///     systems.emplace<[](ComponentA& a){}>(); // Single mutable component
///     systems.emplace<[](::xrn::ecs::Entity& entity, ComponentA& a){ ... }>(); // with the entity containing the component
///     systems.emplace<[](::xrn::ecs::Entity& entity, ComponentA& a, ComponentB& b){ ... }>(); // With multiple components
///     systems.emplace<[](const ::xrn::ecs::Entity& entity, ComponentA& a, ComponentB& b){ ... }>(); // With const Entity
///     systems.emplace<[](::xrn::ecs::Entity& entity, ComponentA& a, const ComponentB& b){ ... }>(); // With const Components
///     systems.emplace<[](::xrn::ecs::Entity& entity, const ComponentA& a, const ComponentB& b){ ... }>(); // With const Components
///     systems.emplace<[](::xrn::Time, const ::xrn::ecs::Entity& entity, ComponentB& b){ ... }>(); // With Time
///
///     // emplacing all the const systems
///     constSystems.emplace<[](::xrn::Time, const ::xrn::ecs::Entity& entity, const ComponentB& b){ ... }>(); // everything has to be const (or copy)
///
///     // run all the systems with a clock
///     ::xrn::Clock clock;
///     for (auto i{ 0uz }; i < 10; ++i) {
///         systems.run(clock.getElapsed(), entities);
///         constSystems.run(clock.restart(), entities);
///     }
/// }
/// \endcode
///
///////////////////////////////////////////////////////////////////////////
