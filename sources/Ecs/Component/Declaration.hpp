#pragma once

#include <Ecs/Component/Detail/Declaration.hpp>

START_COMPONENT_DECLARATIONS();



#ifdef TEST // used for unit testing
DECLARE_COMPONENT_IN_NAMESPACE(xrn::ecs::component::test, Movable);
DECLARE_COMPONENT_IN_NAMESPACE(xrn::ecs::component::test, Transformable);
DECLARE_COMPONENT_IN_NAMESPACE(xrn::ecs::component::test, Transformable2d);
#endif // TEST

DECLARE_COMPONENT_IN_NAMESPACE(xrn::ecs::component, Controllable);
DECLARE_COMPONENT_IN_NAMESPACE(xrn::ecs::component, Transformable);
DECLARE_COMPONENT_IN_NAMESPACE(xrn::ecs::component, Drawable);



STOP_COMPONENT_DECLARATIONS();

#include <Ecs/Component/Detail/UndefDeclarations.hpp>
