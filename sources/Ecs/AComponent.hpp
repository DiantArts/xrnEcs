#pragma once

#include <Ecs/Component/AComponent.hpp>
namespace xrn::ecs {
    template <
        typename ComponentTypes
    > using AComponent = ::xrn::ecs::component::AComponent<ComponentTypes>;
}



#include <Ecs/Component/Container.hpp>
