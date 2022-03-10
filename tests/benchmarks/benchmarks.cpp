///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Benchmark library
///////////////////////////////////////////////////////////////////////////
#include <nanobench.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Ecs.hpp>



///////////////////////////////////////////////////////////////////////////
// Test components
///////////////////////////////////////////////////////////////////////////
namespace xrn::ecs::component::test {
    class Movable
        : public ::xrn::ecs::AComponent<::xrn::ecs::component::test::Movable>
    {};

    class Transformable
        : public ::xrn::ecs::AComponent<::xrn::ecs::component::test::Transformable>
    {
    public:
        int value[100];
    };
} // namespace xrn::ecs::component::test


void addsAllints(
    ::xrn::ecs::component::test::Transformable& t
)
{
    int a{ 0 };
    for (auto i{ 0uz }; i < 100; i++) {
        a += i;
        t.value[i] = a;
    }
}


auto main()
    -> int
{
    {
        ankerl::nanobench::Bench bench;
        bench.epochs(50000).performanceCounters(true);

        ::xrn::ecs::component::Container components;
        bench.run(
            "10k empty entities",
            []{
                ankerl::nanobench::doNotOptimizeAway(::xrn::ecs::Entity{});
            }
        );
        bench.run(
            "entity: create",
            [&components]{
                using Component = ::xrn::ecs::component::test::Transformable;
                auto entity{ ::xrn::ecs::Entity::generate<Component>(components) };
                entity.removeComponent<Component>(components);
            }
        );
    }

    {
        ankerl::nanobench::Bench bench;
        bench.epochs(50000).performanceCounters(true);

        ::xrn::ecs::component::Container components;
        ::xrn::ecs::entity::Container entities{ components };
        ::xrn::ecs::System<addsAllints> systemAdd;
        ::xrn::Clock c;
        entities.emplace<::xrn::ecs::component::test::Transformable>();
        bench.run(
            "system: adds",
            [&]{
                systemAdd(c.restart(), entities, components);
            }
        );
    }
    return 0;
}
