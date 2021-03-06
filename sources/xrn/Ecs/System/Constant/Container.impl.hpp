#pragma once



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Run
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::xrn::ecs::system::constant::Container::run(
    ::xrn::Time t,
    const ::xrn::ecs::entity::Container& entities
) const
{
    for (auto& system : m_systems) {
        system->run(t, entities);
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Others
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
auto ::xrn::ecs::system::constant::Container::emplace(
    auto function
) -> ::xrn::ecs::constant::ASystem&
{
    if constexpr (!::xrn::ecs::detail::meta::Function<decltype(function)>::Arguments::areConst) {
        ::std::cerr
            << "[ERROR]: Trying to emplace a const system but argments are not const"
            << ::std::endl;
    } else {
        m_systems.push_back(::std::make_unique<::xrn::ecs::ConstSystem<decltype(function)>>(function));
    }
    return *m_systems.back();
}
