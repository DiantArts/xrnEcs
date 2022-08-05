///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Ecs.hpp>
#include <Ecs/Detail/Constraint.hpp>
#include <MegaArray.hpp>
#include <MegaArray.impl.hpp>
#include <MemoryManager.impl.hpp>

///////////////////////////////////////////////////////////////////////////
// Components
///////////////////////////////////////////////////////////////////////////
auto nbOfComponent{ 0uz };
namespace xrn::ecs::component {
    class Drawable
        : public ::xrn::ecs::AComponent<::xrn::ecs::component::Drawable>
    {
    public:
        Drawable(){
            ++nbOfComponent;
            ::std::cout << "Creating: " << nbOfComponent << ::std::endl;
        };
        ~Drawable(){
            --nbOfComponent;
            ::std::cout << "Deleting: " << nbOfComponent << ::std::endl;
        };
    };
    class Transformable
        : public ::xrn::ecs::AComponent<::xrn::ecs::component::Transformable>
    {
    public:
        Transformable(){
            ++nbOfComponent;
            ::std::cout << "Creating: " << nbOfComponent << ::std::endl;
        };
        ~Transformable(){
            --nbOfComponent;
            ::std::cout << "Deleting: " << nbOfComponent << ::std::endl;
        };
        int value{ 1 };
    };
    class Controllable
        : public ::xrn::ecs::AComponent<::xrn::ecs::component::Controllable>
    {
    public:
        Controllable(){
            ++nbOfComponent;
            ::std::cout << "Creating: " << nbOfComponent << ::std::endl;
        };
        ~Controllable(){
            --nbOfComponent;
            ::std::cout << "Deleting: " << nbOfComponent << ::std::endl;
        };
        int value{ 2 }, valu2{ 0 }; };
    class Killable
        : public ::xrn::ecs::AComponent<::xrn::ecs::component::Killable>
    {
    public:
        Killable(int a, int b, int c) : value{ a }, valu2{ b }, valu3{ c } {
            ++nbOfComponent;
            ::std::cout << "Creating: " << nbOfComponent << ::std::endl;
        }
        ~Killable() {
            --nbOfComponent;
            ::std::cout << "Deleting: " << nbOfComponent << ::std::endl;
        }
        int value{ 3 }, valu2{ 0 }, valu3{ 0 };
    };
} // namespace xrn::ecs::component

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
auto main()
    -> int
try {
    using D = ::xrn::ecs::component::Drawable;
    using T = ::xrn::ecs::component::Transformable;
    using C = ::xrn::ecs::component::Controllable;
    using K = ::xrn::ecs::component::Killable;

    ::xrn::ecs::Entity e;
    ::xrn::ecs::component::MegaArray array{ 254 };

    array.emplace<T>(e);
    array.emplace<C>(e);
    array.remove<T>(e);
    array.emplace<T>(e);
    return EXIT_SUCCESS;
} catch (const ::std::exception& e) {
   ::std::cerr << "ERROR: " << e.what() <<::std::endl;
    return EXIT_FAILURE;
} catch (...) {
   ::std::cerr << "ERROR: unknown" <<::std::endl;
    return EXIT_FAILURE;
}
