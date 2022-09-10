///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs.hpp>
#include <xrn/Util.hpp>

///////////////////////////////////////////////////////////////////////////
auto main()
    -> int
{
    ::xrn::ecs::Registry<int, float> registry;
    auto e1{ registry.createEntity() };
    auto e2{ registry.createEntity() };
    auto e3{ registry.createEntity() };
    registry.add<int>(e1, 5);
    registry.add<float>(e2, 5);
    registry.add<int>(e3, 5);
    registry.add<float>(e3, 5);

    ::std::cout << registry.get<int>(e1) << ::std::endl;
    ::std::cout << registry.get<int>(e3) << ::std::endl;
    registry.run([](::xrn::Time deltaTime, ::xrn::ecs::Entity entity, int& i){
        ::std::cout << "system int" << ::std::endl;
        ++i;
    });
    ::std::cout << registry.get<int>(e1) << ::std::endl;
    ::std::cout << registry.get<int>(e3) << ::std::endl;
    registry.run([](::xrn::Time deltaTime, ::xrn::ecs::Entity entity, int& i, float f){
        ::std::cout << "system int and float" << ::std::endl;
        ++i;
        ++f;
    });
    ::std::cout << registry.get<int>(e1) << ::std::endl;
    ::std::cout << registry.get<int>(e3) << ::std::endl;

    return EXIT_SUCCESS;
}
