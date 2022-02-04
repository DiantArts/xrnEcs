#pragma once

#include <Ecs/System/System.hpp>
namespace xrn::ecs {
    template <
        auto function,
        ::xrn::ecs::component::ConceptType... BanishedComponentTypes
    > using System = ::xrn::ecs::system::System<function, BanishedComponentTypes...>;
}



#include <Ecs/System/Container.hpp>
