#include <pch.hpp>
#include <Util/Clock.hpp>



auto main(
    int argc,
    char **argv
) -> int
{
    try {
        using ::xrn::util::literal::operator""_ns;

        auto t1{ ::xrn::Time::createAsSeconds(0.1) };
        auto t2{ t1.getAsMilliseconds() }; // 100ms
        ::xrn::Time t3{ 30u };
        auto t4{ t3.getAsMicroseconds() }; // 30000ms
        auto t5{ ::xrn::Time::createAsNanoseconds(-800000) }; // -0.8
        auto t6{ t5.getAsSeconds() }; // -0.0008ms
        auto t7{ t1 + ::xrn::Time::createAsSeconds(t6) }; // 99.2ms
        auto t8{ t1 + -800000_ns }; // 99.2ms
        auto t9{ t1 + t5 }; // 99.2ms
        auto t10{ t1 + 55 }; // 155ms
        auto t11{ 55 + t1 }; // 155ms

        ::std::cout << "t1  == " << t1 << ::std::endl;
        ::std::cout << "t2  == " << t2 << ::std::endl;
        ::std::cout << "t3  == " << t3 << ::std::endl;
        ::std::cout << "t4  == " << t4 << ::std::endl;
        ::std::cout << "t5  == " << t5 << ::std::endl;
        ::std::cout << "t6  == " << t6 << ::std::endl;
        ::std::cout << "t7  == " << t7 << ::std::endl;
        ::std::cout << "t8  == " << t8 << ::std::endl;
        ::std::cout << "t9  == " << t9 << ::std::endl;
        ::std::cout << "t10 == " << t10 << ::std::endl;
        ::std::cout << "t11 == " << t11 << ::std::endl;
        // ::std::cout << t11 << ::std::endl;
        return EXIT_SUCCESS;
    } catch (const ::std::exception& e) {
       ::std::cerr << "ERROR: " << e.what() <<::std::endl;
        return EXIT_FAILURE;
    } catch (...) {
       ::std::cerr << "ERROR: unknown" <<::std::endl;
        return EXIT_FAILURE;
    }
}
