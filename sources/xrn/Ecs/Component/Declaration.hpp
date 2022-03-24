#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Declares components
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// COMPONENT macro only works in the "::xrn::ecs::component" namespace. To
// declare a macro in another namespace, use COMPONENT_IN_NAMESPACE with
// the first argument being the current namespace.
// To use an other file (or multiple files) to declare components, please go
// inside the "/xrn/Ecs/Component/Detail/Declaration.hpp" file, and look at the
// "User-defined Components" sections. It is where the component declaration
// files are included and used.
// Components are forwarded declared here, but can be defined else where.
///////////////////////////////////////////////////////////////////////////
namespace xrn::ecs::component {

///////////////////////////////////////////////////////////////////////////
// Drawable component.
//
///////////////////////////////////////////////////////////////////////////
COMPONENT(Drawable) {
public:
    Drawable(){
        ::std::cout << "Creating D: "
            << ++this->nbOfComponent << ::std::endl;
    };
    ~Drawable(){
        ::std::cout << "Deleting D: "
            << --this->nbOfComponent << ::std::endl;
    };
    int value{ 1 };
    static inline auto nbOfComponent{ 0uz };
};


///////////////////////////////////////////////////////////////////////////
// Transformable component.
//
///////////////////////////////////////////////////////////////////////////
COMPONENT(Transformable) {
public:
    Transformable(){
        ::std::cout << "Creating T: "
            << ++this->nbOfComponent << ::std::endl;
    };
    ~Transformable(){
        ::std::cout << "Deleting T: "
            << --this->nbOfComponent << ::std::endl;
    };
    int value{ 2 }, valu2{ 0 };
    static inline auto nbOfComponent{ 0uz };
};



///////////////////////////////////////////////////////////////////////////
// Controllable component.
//
///////////////////////////////////////////////////////////////////////////
COMPONENT(Controllable) {
public:
    Controllable(){
        ::std::cout << "Creating C: "
            << ++this->nbOfComponent << ::std::endl;
    };
    ~Controllable(){
        ::std::cout << "Deleting C: "
            << --this->nbOfComponent << ::std::endl;
    };
    int value{ 3 }, valu2{ 0 }, valu3{ 0 };
    static inline auto nbOfComponent{ 0uz };
};



///////////////////////////////////////////////////////////////////////////
// Killable component.
//
///////////////////////////////////////////////////////////////////////////
COMPONENT(Killable) {
public:
    Killable(int a, int b, int c, int d) : value{ a }, valu2{ b }, valu3{ c }, valu4{ d } {
        ::std::cout << "Creating K: "
            << ++this->nbOfComponent << ::std::endl;
    }
    ~Killable() {
        ::std::cout << "Deleting K: "
            << --this->nbOfComponent << ::std::endl;
    }
    int value{ 3 }, valu2{ 0 }, valu3{ 0 }, valu4{ 0 };
    static inline auto nbOfComponent{ 0uz };
};

} // namespace xr::ecs::component
