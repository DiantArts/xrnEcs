///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Ecs.hpp>



namespace xrn::ecs::component {
    class Drawable
        : public ::xrn::ecs::AComponent<::xrn::ecs::component::Drawable>
    { public: int value{ 0 }; };
    class Transformable
        : public ::xrn::ecs::AComponent<::xrn::ecs::component::Transformable>
    { public: int value{ 0 }; };
    class Controllable
        : public ::xrn::ecs::AComponent<::xrn::ecs::component::Controllable>
    {};
    class Killable
        : public ::xrn::ecs::AComponent<::xrn::ecs::component::Killable>
    {};
} // namespace xrn::ecs::component


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
auto main()
    -> int
try {
    ::xrn::ecs::component::Container components;
    ::xrn::ecs::entity::Container entities{ components };
    entities.emplace<::xrn::ecs::component::Drawable>().removeComponents<::xrn::ecs::component::Drawable>();
    auto e2Id{ entities.emplace<::xrn::ecs::component::Transformable>().getId() };
    auto e3Id{ entities.emplace<
        ::xrn::ecs::component::Drawable,
        ::xrn::ecs::component::Transformable
    >().getId() };


    return EXIT_SUCCESS;
} catch (const ::std::exception& e) {
   ::std::cerr << "ERROR: " << e.what() <<::std::endl;
    return EXIT_FAILURE;
} catch (...) {
   ::std::cerr << "ERROR: unknown" <<::std::endl;
    return EXIT_FAILURE;
}
