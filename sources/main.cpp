///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Ecs/Entity.hpp>



namespace xrn::ecs::component {
    class Drawable
        : public ::xrn::ecs::AComponent<::xrn::ecs::component::Drawable>
    {};
    class Transformable
        : public ::xrn::ecs::AComponent<::xrn::ecs::component::Transformable>
    {};
} // namespace xrn::ecs::component



auto main()
    -> int
try {
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::Entity entity{};
    ::std::cout << ::std::boolalpha << "base entity: " << &entity << ::std::endl;
    ::xrn::ecs::Entity::Reference ref{ components, entity };
    ::std::cout << ::std::boolalpha << "ref get entity: " << &ref.get() << ::std::endl;
    const ::xrn::ecs::Entity& entityRef3{ ref };
    ::std::cout << ::std::boolalpha << "const ref entity: " << &entityRef3 << ::std::endl;

    ::std::cout << ::std::boolalpha << "ref comparison: " << (&entity == &entityRef3) << ::std::endl;
    ::std::cout << ::std::boolalpha << "get comparison: " << (&entity == &ref.get()) << ::std::endl;
    return EXIT_SUCCESS;
} catch (const ::std::exception& e) {
   ::std::cerr << "ERROR: " << e.what() <<::std::endl;
    return EXIT_FAILURE;
} catch (...) {
   ::std::cerr << "ERROR: unknown" <<::std::endl;
    return EXIT_FAILURE;
}
