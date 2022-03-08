#pragma once

#include <Util/Clock.hpp>
#include <Ecs/System/System.hpp>
#include <Ecs/Component.hpp>
#include <Ecs/Entity.hpp>



namespace xrn::ecs::system {



class Container {

public:

    // ------------------------------------------------------------------ Run

    void run(
        ::xrn::Time t,
        ::xrn::ecs::entity::Container& entities,
        ::xrn::ecs::component::Container& components
    );

    void run(
        ::xrn::Time t,
        const ::xrn::ecs::entity::Container& entities,
        const ::xrn::ecs::component::Container& components
    ) const;



    // ------------------------------------------------------------------ Vectors

    template <
        auto func,
        ::xrn::ecs::detail::constraint::isComponent... BanishedComponentTypes
    > void emplace();



private:

    ::std::vector<::std::unique_ptr<::xrn::ecs::system::ASystem>> m_systems{};

};



} // namespace xrn::ecs::system

#include <Ecs/System/Container.impl.hpp>
