#pragma once

#include <Ecs/Component/Container.hpp>
#include <Ecs/Entity/Container.hpp>
#include <Util/Time.hpp>



namespace xrn::ecs::system {



class ASystem {

public:

    // ------------------------------------------------------------------ *structors

    virtual ~ASystem() noexcept = 0; // RULE OF 5!



    // ------------------------------------------------------------------ Run

    virtual void operator()(
        ::xrn::Time t,
        ::xrn::ecs::entity::Container& entities,
        ::xrn::ecs::component::Container& components
    ) = 0;

    virtual void operator()(
        ::xrn::Time t,
        const ::xrn::ecs::entity::Container& entities,
        const ::xrn::ecs::component::Container& components
    ) const = 0;



private:

};



} // namespace xrn::ecs::system
