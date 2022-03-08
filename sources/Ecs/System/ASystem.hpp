#pragma once

#include <Util/Time.hpp>

namespace xrn::ecs::entity{ class Container; }
namespace xrn::ecs::component{ class Container; }



namespace xrn::ecs::system {



class ASystem {

public:

    // ------------------------------------------------------------------ Constructors

    virtual ~ASystem() noexcept = 0; // TODO: RULE OF 5!



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
