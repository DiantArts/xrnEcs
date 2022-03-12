///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Ecs/Component/Container.hpp>


void ::xrn::ecs::component::Container::remove(
    const ::xrn::Id entityId,
    const ::xrn::Id componentId
)
{
    auto& pairComponentContainer{ this->getUnsafePairSubContainer(componentId) };
    auto it{ ::std::ranges::find(pairComponentContainer.first, entityId) };
    if (it == pairComponentContainer.first.end()) {
        throw ::std::runtime_error(
            "Entity '"s + static_cast<::std::string>(entityId) + "' doesn't contain a component with a '"s +
                static_cast<::std::string>(componentId) + "' Id"
        );
    }
    pairComponentContainer.first.erase(it);
}

auto ::xrn::ecs::component::Container::getUnsafePairSubContainer(
    const ::xrn::Id id
) -> SubPairContainerType&
{
    return m_container.at(id);
}
