///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs.hpp>



///////////////////////////////////////////////////////////////////////////
auto main()
    -> int
try {
    constexpr ::xrn::ecs::Signature signature;
    // signature.add<D>();

    // ::xrn::ecs::component::Container components;
    // ::xrn::ecs::entity::Container entities{ components };
    // auto e1Id{ entities.emplace<D>().getId() };
    // auto e2Id{ entities.emplace<T>().getId() };
    // auto e3Id{ entities.emplace<D, T>().getId() };

    // ::xrn::ecs::system::System<function1> system1;
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
