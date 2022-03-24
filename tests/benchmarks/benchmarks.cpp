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
#include <xrn/Ecs.hpp>


void addsAllints(
    ::xrn::ecs::component::test::Benchmark100ints& t
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
                ankerl::nanobench::doNotOptimizeAway(::xrn::ecs::entity::Entity{});
            }
        );
        bench.run(
            "entity: create",
            [&components]{
                using Component = ::xrn::ecs::component::test::Benchmark100ints;
                auto entity{ ::xrn::ecs::entity::Entity::generate<Component>(components) };
                entity.removeComponent<Component>(components);
            }
        );
    }

    {
        ankerl::nanobench::Bench bench;
        bench.epochs(50000).performanceCounters(true);

        ::xrn::ecs::component::Container components;
        ::xrn::ecs::entity::Container entities{ components };
        ::xrn::ecs::system::System<addsAllints> systemAdd;
        ::xrn::Clock c;
        entities.emplace<::xrn::ecs::component::test::Benchmark100ints>();
        bench.run(
            "system: adds",
            [&]{
                systemAdd(c.restart(), entities, components);
            }
        );
    }
    return 0;
}
