///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <xrn/Ecs.hpp>


void printComponentValues(
    ::xrn::Time,
    const ::xrn::ecs::Entity&,
    const ::xrn::ecs::component::ComponentA& a,
    const ::xrn::ecs::component::ComponentB& b
){
    ::std::cout << "ComponentA: " << a.value << " ComponentB: " << b.value << ::std::endl;
}



///////////////////////////////////////////////////////////////////////////

class ASubSystem {
public:
    virtual ~ASubSystem() = 0;
    virtual void run() = 0;
};
ASubSystem::~ASubSystem() = default;

template <
    typename FuncPtr
> class SubSystem : public ASubSystem {
public:
    SubSystem(FuncPtr func) : m_func{ func } {}

    void run() override { m_func(); }

private:
    FuncPtr m_func;
};


class System2 {
public:
    System2(auto func) : m_func{ ::std::make_unique<SubSystem<decltype(func)>>(func) } {}

    void run(){ m_func->run(); };

private:
    ::std::unique_ptr<ASubSystem> m_func;
};


///////////////////////////////////////////////////////////////////////////
auto main()
    -> int
try {
    using namespace ::xrn::ecs::component;

    int value2{ 7 };
    System2 system{ [value2](){ ::std::cout << value2 << ::std::endl; } };
    system.run();

    return EXIT_SUCCESS;
} catch (const ::std::exception& e) {
   ::std::cerr << "ERROR: " << e.what() <<::std::endl;
    return EXIT_FAILURE;
} catch (...) {
   ::std::cerr << "ERROR: unknown" <<::std::endl;
    return EXIT_FAILURE;
}
