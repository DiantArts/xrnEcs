#pragma once

#include <Util/Id.hpp>
#include <Ecs/Component/Declaration.hpp>
#include <Meta/IsBaseOfTemplate.hpp>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"


namespace xrn::ecs::component {




template <
    typename ComponentType
> class AComponent
    : public ::xrn::ecs::component::declaration::detail::WithId<::std::remove_cvref_t<ComponentType>>
{

public:

    virtual ~AComponent() = 0; // TODO: rule of 5

};



static constexpr ::xrn::Id maxId{ ::xrn::ecs::component::declaration::detail::numberOfIds };



} // namespace xrn::ecs::component


#pragma GCC diagnostic pop



#include <Ecs/Component/AComponent.impl.hpp>
