///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Ecs/Entity.hpp>
#include <Ecs/Detail/Constraint.hpp>
#include <Ecs/Component/Detail/Type.hpp>
#include <Ecs/Component/ForEach.hpp>



// namespace xrn::ecs::component {
    // class Drawable
        // : public ::xrn::ecs::AComponent<::xrn::ecs::component::Drawable>
    // {};
    // class Transformable
        // : public ::xrn::ecs::AComponent<::xrn::ecs::component::Transformable>
    // {};
    // class Controllable
        // : public ::xrn::ecs::AComponent<::xrn::ecs::component::Controllable>
    // {};
    // class Killable
        // : public ::xrn::ecs::AComponent<::xrn::ecs::component::Killable>
    // {};
// } // namespace xrn::ecs::component



template <
    auto func,
    ::std::size_t index = 0
> void constexpr forEachComponent(
    const ::xrn::Id id
)
{
    if constexpr (index < xrn::ecs::component::maxId) {
        func.template operator()<typename xrn::ecs::component::IdInfo<index>::Type>();
        forEachComponent<func, index + 1>(id);
    }
}


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
auto main()
    -> int
try {
    ::std::cout << ::xrn::ecs::isComponent<::xrn::ecs::component::Drawable> << ::std::endl;
    // auto signature{ ::xrn::ecs::Signature::generate<
        // ::xrn::ecs::component::Drawable, ::xrn::ecs::component::Controllable
    // >() };
    // ::xrn::ecs::component::ForEach::template run<[]<
            // ::xrn::ecs::detail::constraint::isComponent T
        // >(int i){
        // ::std::cout << "hello: " << i << " + " << T::getId() << ::std::endl;
    // }>(signature, 5);

    // ::xrn::Id value{ 1 };
    // forEachComponent<[]<typename T>(){
        // ::std::cout << "hello: " << T::getId() << ::std::endl;
    // }>(value);
    return EXIT_SUCCESS;
} catch (const ::std::exception& e) {
   ::std::cerr << "ERROR: " << e.what() <<::std::endl;
    return EXIT_FAILURE;
} catch (...) {
   ::std::cerr << "ERROR: unknown" <<::std::endl;
    return EXIT_FAILURE;
}
