///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs.hpp>

int function(int);

///////////////////////////////////////////////////////////////////////////
auto main()
    -> int
{
    auto* a{ new int{ 1 } };
    a[2] = 5;
    return 0;

    // auto functionSignature{ ::xrn::ecs::detail::Function<int, float>::
        // template Information<[&](int){}>::Arguments::generateSignature()
    // };

    // ::std::cout << functionSignature << ::std::endl;
    // return 0;

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
    registry.run([&](int& i){
        ::std::cout << "system int" << ::std::endl;
        ++i;
    });
    ::std::cout << registry.get<int>(e1) << ::std::endl;
    ::std::cout << registry.get<int>(e3) << ::std::endl;
    registry.run([](int& i){
        ::std::cout << "system int" << ::std::endl;
        ++i;
    });
    ::std::cout << registry.get<int>(e1) << ::std::endl;
    ::std::cout << registry.get<int>(e3) << ::std::endl;
    registry.run([](::xrn::Time, int& i){
        ::std::cout << "system int" << ::std::endl;
        ++i;
    });
    ::std::cout << registry.get<int>(e1) << ::std::endl;
    ::std::cout << registry.get<int>(e3) << ::std::endl;
    registry.run<float>([](::xrn::Time, ::xrn::ecs::Entity entity, int& i){
        ::std::cout << "system int with float banned" << ::std::endl;
        ++i;
    });
    ::std::cout << registry.get<int>(e1) << ::std::endl;
    ::std::cout << registry.get<int>(e3) << ::std::endl;
    registry.run([](::xrn::Time, ::xrn::ecs::Entity, int& i, float f){
        ::std::cout << "system int and float" << ::std::endl;
        ++i;
        ++f;
    });
    ::std::cout << registry.get<int>(e1) << ::std::endl;
    ::std::cout << registry.get<int>(e3) << ::std::endl;

    return EXIT_SUCCESS;
}
