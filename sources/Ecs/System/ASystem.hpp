#pragma once

#include <Ecs/Component/Container.hpp>
#include <Ecs/Entity/Container.hpp>
#include <Util/Time.hpp>



namespace xrn::ecs::system {



class ASystem {

public:

    // ------------------------------------------------------------------ Constructors

    virtual ~ASystem() noexcept = 0; // RULE OF 5!



    // ------------------------------------------------------------------ Run

    virtual void operator()(
        ::xrn::Time t,
        ::xrn::ecs::Entity::Container& entities,
        ::xrn::ecs::component::Container& components
    ) = 0;

    virtual void operator()(
        ::xrn::Time t,
        const ::xrn::ecs::Entity::Container& entities,
        const ::xrn::ecs::component::Container& components
    ) const = 0;



private:

};



} // namespace xrn::ecs::system
