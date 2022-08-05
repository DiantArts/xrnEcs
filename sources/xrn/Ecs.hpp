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
/// Content of xrn/Ecs/Component/Declaration.hpp:
/// \code
/// namespace xrn::ecs::component {
///
/// ABILITY(AbilityA);
/// ABILITY(AbilityB);
///
/// COMPONENT(ComponentA) {
/// public:
///     int value{ 1 };
/// };
///
/// COMPONENT(ComponentB) {
/// public:
///     ComponentB(int val) : value{ val }{}
///     int value;
/// };
///
/// } // namespace xr::ecs::component
/// \endcode
///
/// Content of the main:
/// \code
/// #include <xrn/Ecs.hpp>
///
/// void printComponentValues(
///     ::xrn::Time,
///     const ::xrn::ecs::Entity&,
///     const ::xrn::ecs::component::ComponentA& a,
///     const ::xrn::ecs::component::ComponentB& b
/// ){
///     ::std::cout << "ComponentA: " << a.value << " ComponentB: " << b.value << ::std::endl;
/// }
///
/// int main()
/// {
///     using namespace ::xrn::ecs::component;
///
///     // Creating the ECS containers needed
///     // Containing all the components of the program
///     ::xrn::ecs::component::Container components;
///     // Containing all the entities of the program, links the component container to it
///     ::xrn::ecs::entity::Container entities{ components };
///     // Systems of the program. Systems can be applied on different component/entity containers
///     ::xrn::ecs::system::Container systems;
///     // Const systems are normal systems that are used to affect other things than component (like drawing to the screen)
///     ::xrn::ecs::system::ConstContainer constSystems;
///
///     // Creating entities
///     // Create an entity with a single component and keep its ID to use it later
///     auto entityId1{ entities.emplace<ComponentA>().getId() };
///     // Create an entity with a multiple components and keep its ID aswell
///     auto entityId2{ entities.emplace(ComponentA{}, ComponentB{ 5 }).getId() };
///
///     // emplacing all the system that will be executed each time systems.run() is called
///     // Single mutable component
///     systems.emplace<[](ComponentA& a){
///         ++a.value;
///     }>();
///
///     // with the entity containing the component
///     systems.emplace<[](::xrn::ecs::Entity&, ComponentA& a){
///         ++a.value;
///     }>();
///
///     // With multiple components
///     systems.emplace<[](::xrn::ecs::Entity&, ComponentA& a, ComponentB& b){
///         ++a.value; ++b.value;
///     }>();
///
///     // With const Entity
///     systems.emplace<[](const ::xrn::ecs::Entity&, ComponentA& a, ComponentB& b){
///         ++a.value; ++b.value;
///     }>();
///
///     // With const Components
///     systems.emplace<[](::xrn::ecs::Entity&, ComponentA& a, const ComponentB& b){
///         a.value += b.value;
///     }>();
///
///     // With Time
///     systems.emplace<[](::xrn::Time, const ::xrn::ecs::Entity&, ComponentB& b){
///         ++b.value;
///     }>();
///
///     // emplacing all the const systems (everything has to be const or copied)
///     // with a function instead of a lambda
///     constSystems.emplace<printComponentValues>();
///
///     // run all the systems with a clock
///     ::xrn::Clock clock;
///     for (auto i{ 0uz }; i < 10; ++i) {
///         systems.run(clock.getElapsed(), entities);
///         constSystems.run(clock.restart(), entities);
///     }
///     return EXIT_SUCCESS;
/// }
/// \endcode
///
/// Output of this program:
/// \code
/// ComponentA: 12 ComponentB: 8
/// ComponentA: 26 ComponentB: 11
/// ComponentA: 43 ComponentB: 14
/// ComponentA: 63 ComponentB: 17
/// ComponentA: 86 ComponentB: 20
/// ComponentA: 112 ComponentB: 23
/// ComponentA: 141 ComponentB: 26
/// ComponentA: 173 ComponentB: 29
/// ComponentA: 208 ComponentB: 32
/// ComponentA: 246 ComponentB: 35
/// \endcode
///
///////////////////////////////////////////////////////////////////////////
