#pragma once

#include <Ecs/Component/Detail/Declaration.hpp>



START_COMPONENT_DECLARATIONS();



#ifdef TEST
DECLARE_COMPONENT_IN_NAMESPACE(xrn::ecs::component::test, Movable);
DECLARE_COMPONENT_IN_NAMESPACE(xrn::ecs::component::test, Transformable);
DECLARE_COMPONENT_IN_NAMESPACE(xrn::ecs::component::test, Transformable2d);
#endif // TEST

DECLARE_COMPONENT_IN_NAMESPACE(xrn::ecs::component, Controllable); //TODO: adapt DO NOT USE for now
DECLARE_COMPONENT_IN_NAMESPACE(xrn::ecs::component, Transformable); //TODO: adapt
DECLARE_COMPONENT_IN_NAMESPACE(xrn::ecs::component, Drawable); //TODO: implement



STOP_COMPONENT_DECLARATIONS();
