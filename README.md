# xrnEcs
## Table of contents
* [Introduction](#introduction)
* [Goal of this project](#goal-of-this-project)
* [Technologies used](#technologies-used)
* [Launch](#launch)
* [Example of use](#example-of-use)

## Introduction
'xrn' projects are small standalone learning projects that, put together, will (maybe) make a Game Engine.
This subproject is an ECS (Entity Component System) header-only library designed to be a fast and lightweight
library forcing as many things as possible at compile time.
The downside of forcing compile time operations is that using it can sometimes be a bit more complicated
than it would have been without those operations. However, the gain in speed and lightweight is worth the
trouble for the base of a Game Engine where all small optimizations are welcome.

## Goal of this project

## Technologies used
* c++2b
* [boost](https://github.com/boostorg/boost) 1.78.0 / [boost::tests](https://github.com/boostorg/test) (only for unitary tests)
* [Nanobench](https://github.com/martinus/nanobench) 4.3.6 (only for benchmarks)
* [bitset2](https://github.com/ClaasBontus/bitset2)

## Launch
For now (till a solution for the `xrn/Ecs/Component/Declaration.hpp` file have been found), after cloning
the repository, copy the source header files (inside the directory `sources/xrn/`) to the include directory
of your choice:
```sh
git clone git@github.com:DiantArts/xrnEcs.git && cp xrnEcs/sources/xrn/ path/to/your/directory
```
Then, all is left to do is to add the directory where `xrn` directory have been copied to the list of include.
Else, it is possible to directly clone the directory in the repositorp and set 'xrnEcs/sources' to the list of includes.

## Example of use
Content of `xrn/Ecs/Component/Declaration.hpp`:
```cpp
namespace xrn::ecs::component {

ABILITY(AbilityA);
ABILITY(AbilityB);

COMPONENT(ComponentA) {
public:
    int value{ 1 };
};

COMPONENT(ComponentB) {
public:
    ComponentB(int val) : value{ val }{}
    int value;
};

} // namespace xr::ecs::component
```
Content of the main:
```cpp
#include <xrn/Ecs.hpp>

void printComponentValues(
    ::xrn::Time,
    const ::xrn::ecs::Entity&,
    const ::xrn::ecs::component::ComponentA& a,
    const ::xrn::ecs::component::ComponentB& b
){
    ::std::cout << "ComponentA: " << a.value << " ComponentB: " << b.value << ::std::endl;
}

int main()
{
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
    // with a function instead of a lambda
    constSystems.emplace<printComponentValues>();

    // run all the systems with a clock
    ::xrn::Clock clock;
    for (auto i{ 0uz }; i < 10; ++i) {
        systems.run(clock.getElapsed(), entities);
        constSystems.run(clock.restart(), entities);
    }
    return EXIT_SUCCESS;
}
```
Output of this program:
```
ComponentA: 12 ComponentB: 8
ComponentA: 26 ComponentB: 11
ComponentA: 43 ComponentB: 14
ComponentA: 63 ComponentB: 17
ComponentA: 86 ComponentB: 20
ComponentA: 112 ComponentB: 23
ComponentA: 141 ComponentB: 26
ComponentA: 173 ComponentB: 29
ComponentA: 208 ComponentB: 32
ComponentA: 246 ComponentB: 35
```
