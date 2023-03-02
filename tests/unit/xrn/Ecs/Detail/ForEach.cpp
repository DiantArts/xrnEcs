#include <pch.hpp>
#include <gtest/gtest.h>
#include <xrn/Ecs/Detail/ForEach.hpp>

TEST(ForEach, findId)
{
    int i{ 0 };

    ::xrn::ecs::detail::ForEach<int, float, char>::template findId<
        []<typename T>(int& i){ if constexpr (::std::is_same_v<int, T>) { ++i; } }
    >(0, i);
    EXPECT_TRUE(i == 1);

    ::xrn::ecs::detail::ForEach<int, float, char>::template findId<
        []<typename T>(int& i){ if constexpr (::std::is_same_v<float, T>) { ++i; } }
    >(1, i);
    EXPECT_TRUE(i == 2);

    ::xrn::ecs::detail::ForEach<int, float, char>::template findId<
        []<typename T>(int& i){ if constexpr (::std::is_same_v<char, T>) { ++i; } }
    >(2, i);
    EXPECT_TRUE(i == 3);

    ::xrn::ecs::detail::ForEach<int, float, char>::template findId<
        []<typename T>(int& i){ if constexpr (::std::is_same_v<char, T>) { ++i; } }
    >(1, i);
    EXPECT_TRUE(i == 3);
}
