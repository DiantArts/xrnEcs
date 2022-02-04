#include <pch.hpp>
#include <Ecs/Clock.hpp>



int main(int argc, char **argv)
{
    try {
        ::xrn::ecs::Clock clock;
        std::this_thread::sleep_for(2000ms);
        ::std::cout << clock.getElapsed() << ::std::endl;
        return EXIT_SUCCESS;
    } catch (const ::std::exception& e) {
       ::std::cerr << "ERROR: " << e.what() <<::std::endl;
        return EXIT_FAILURE;
    } catch (...) {
       ::std::cerr << "ERROR: unknown" <<::std::endl;
        return EXIT_FAILURE;
    }
}
