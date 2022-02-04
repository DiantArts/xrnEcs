#pragma once

#include <Ecs/Id.hpp>
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

    // ------------------------------------------------------------------ *structors

    explicit AComponent();

    virtual ~AComponent() = 0;

};



template <
    typename Type
> concept ConceptType =
    ::xrn::meta::IsBaseOfTemplate<::xrn::ecs::component::AComponent, ::std::remove_cvref_t<Type>>::value;



static constexpr ::xrn::ecs::Id maxId { ::xrn::ecs::component::declaration::detail::numberOfIds };



} // namespace xrn::ecs::component




#pragma GCC diagnostic pop



#include <Ecs/Component/AComponent.impl.hpp>
