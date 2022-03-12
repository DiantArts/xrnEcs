#pragma once

template <
    auto func,
    ::xrn::ecs::detail::constraint::isComponent... BanishedComponentTypes
> void ::xrn::ecs::system::Container::emplace()
{
    m_systems.push_back(::std::make_unique<::xrn::ecs::System<
        func,
        BanishedComponentTypes...
    >>());
}
