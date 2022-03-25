///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs.hpp>


void printComponentValues(
    ::xrn::Time,
    const ::xrn::ecs::Entity&,
    const ::xrn::ecs::component::ComponentA& a,
    const ::xrn::ecs::component::ComponentB& b
){
    ::std::cout << "ComponentA: " << a.value << " ComponentB: " << b.value << ::std::endl;
}



///////////////////////////////////////////////////////////////////////////
auto main()
    -> int
try {
    using namespace ::xrn::ecs::component;

    // Creating the ECS containers needed
    // Containing all the components of the program
    ::xrn::ecs::component::Container components;
    // Containing all the entities of the program, links the component container to it
    ::xrn::ecs::entity::Container entities{ components };
    // Systems of the program. Systems can be applied on different component/entity containers
    ::xrn::ecs::system::Container systems;
    // Const systems are normal systems that are used to affect other things than component (like drawing to the screen)
    ::xrn::ecs::system::ConstContainer constSystems;

    // Creating entities
    // Create an entity with a single component and keep its ID to use it later
    auto entityId1{ entities.emplace<ComponentA>().getId() };
    // Create an entity with a multiple components and keep its ID aswell
    auto entityId2{ entities.emplace(ComponentA{}, ComponentB{ 5 }).getId() };

    // emplacing all the system that will be executed each time systems.run() is called
    // Single mutable component
    systems.emplace<[](ComponentA& a){
        ++a.value;
    }>();

    // with the entity containing the component
    systems.emplace<[](::xrn::ecs::Entity&, ComponentA& a){
        ++a.value;
    }>();

    // With multiple components
    systems.emplace<[](::xrn::ecs::Entity&, ComponentA& a, ComponentB& b){
        ++a.value; ++b.value;
    }>();

    // With const Entity
    systems.emplace<[](const ::xrn::ecs::Entity&, ComponentA& a, ComponentB& b){
        ++a.value; ++b.value;
    }>();

    // With const Components
    systems.emplace<[](::xrn::ecs::Entity&, ComponentA& a, const ComponentB& b){
        a.value += b.value;
    }>();

    // With Time
    systems.emplace<[](::xrn::Time, const ::xrn::ecs::Entity&, ComponentB& b){
        ++b.value;
    }>();

    // emplacing all the const systems (everything has to be const or copied)
    constSystems.emplace<printComponentValues>();

    // run all the systems with a clock
    ::xrn::Clock clock;
    for (auto i{ 0uz }; i < 10; ++i) {
        systems.run(clock.getElapsed(), entities);
        constSystems.run(clock.restart(), entities);
    }
    return EXIT_SUCCESS;

    return EXIT_SUCCESS;
} catch (const ::std::exception& e) {
   ::std::cerr << "ERROR: " << e.what() <<::std::endl;
    return EXIT_FAILURE;
} catch (...) {
   ::std::cerr << "ERROR: unknown" <<::std::endl;
    return EXIT_FAILURE;
}
