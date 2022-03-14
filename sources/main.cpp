///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Ecs.hpp>
#include <Ecs/Component/Detail/Declaration.hpp>
#include <Ecs/Component/Detail/MemoryManager.hpp>
#include <Ecs/Component/Container.hpp>
#include <Ecs/Component/Detail/MemoryManager.impl.hpp>
#include <Ecs/Component/Container.impl.hpp>


static void function1(
    ::xrn::ecs::Entity& e,
    ::xrn::ecs::component::Drawable& m
) {
    ++m.value;
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
auto main()
    -> int
try {
    using D = ::xrn::ecs::component::Drawable;
    using T = ::xrn::ecs::component::Transformable;
    using C = ::xrn::ecs::component::Controllable;
    using K = ::xrn::ecs::component::Killable;

    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    auto e1Id{ entities.emplace<D>().getId() };
    auto e2Id{ entities.emplace<T>().getId() };
    auto e3Id{ entities.emplace<D, T>().getId() };

    ::xrn::ecs::System<function1> system1;
    // ::std::cout << (components.get<D>(e1Id)->value) << ::std::endl;
    // ::std::cout << (components.get<T>(e2Id)->value) << ::std::endl;
    // ::std::cout << (components.get<D>(e3Id)->value) << ", " << (components.get<T>(e3Id)->value) << ::std::endl;
    return EXIT_SUCCESS;
} catch (const ::std::exception& e) {
   ::std::cerr << "ERROR: " << e.what() <<::std::endl;
    return EXIT_FAILURE;
} catch (...) {
   ::std::cerr << "ERROR: unknown" <<::std::endl;
    return EXIT_FAILURE;
}
