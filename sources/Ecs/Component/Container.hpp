#pragma once

#include <Ecs/Id.hpp>
#include <Ecs/AComponent.hpp>
#include <Meta/UniqueTypes.hpp>



namespace xrn::ecs::component {



class Container {

public:

    template <
        ::xrn::ecs::component::ConceptType ComponentType
    > using SubContainerType = ::std::vector<std::remove_cvref_t<ComponentType>>;

    // map[ComponentId].first == vector<EntityId>
    // map[ComponentId].second  == vector<ComponentType>
    using SubPairContainerType = ::std::pair<::std::vector<::xrn::ecs::Id>, void*>;

    using Type = ::std::unordered_map<
        ::xrn::ecs::Id, Container::SubPairContainerType, ::xrn::ecs::Id::Hasher
    >;



public:

    // ------------------------------------------------------------------ *structors

    explicit Container();

    ~Container();



    // ------------------------------------------------------------------ Id

    template <
        ::xrn::ecs::component::ConceptType ComponentType
    > [[ nodiscard ]] constexpr auto getId() const
        -> ::xrn::ecs::Id;

    [[ nodiscard ]] static constexpr auto getMaxId()
        -> ::xrn::ecs::Id;



    // ------------------------------------------------------------------ Emplace/Remove

    template <
        ::xrn::ecs::component::ConceptType ComponentType
    > auto emplace(
        ::xrn::ecs::Id entityId,
        auto&&... args
    )
        -> ComponentType&;

    template <
        ::xrn::ecs::component::ConceptType... ComponentTypes
    > void emplaceMany(
        ::xrn::ecs::Id entityId
    );

    template <
        ::xrn::ecs::component::ConceptType ComponentType
    > void push(
        ::xrn::ecs::Id entityId,
        ComponentType&& component
    );

    template <
        ::xrn::ecs::component::ConceptType... ComponentTypes
    > void pushMany(
        ::xrn::ecs::Id entityId,
        ComponentTypes&&... components
    );

    template <
        ::xrn::ecs::component::ConceptType ComponentType
    > void remove(
        ::xrn::ecs::Id entityId
    );

    template <
        ::xrn::ecs::component::ConceptType... ComponentTypes
    > void removeMany(
        ::xrn::ecs::Id entityId
    );



    // ------------------------------------------------------------------ Get

    template <
        ::xrn::ecs::component::ConceptType ComponentType
    > [[ nodiscard ]] auto get(
        ::xrn::ecs::Id entityId
    ) const
        -> const ComponentType&;

    template <
        ::xrn::ecs::component::ConceptType ComponentType
    > [[ nodiscard ]] auto get(
        ::xrn::ecs::Id entityId
    )
        -> ComponentType&;

    template <
        ::xrn::ecs::component::ConceptType ComponentType
    > [[ nodiscard ]] auto getIndex(
        ::xrn::ecs::Id entityId
    ) const
        -> ::std::size_t;

    template <
        ::xrn::ecs::component::ConceptType ComponentType
    > [[ nodiscard ]] auto exists(
        ::xrn::ecs::Id entityId
    ) const
        -> bool;



    template <
        ::xrn::ecs::component::ConceptType ComponentType
    > [[ nodiscard ]] auto getVector() const
        -> const ::std::vector<ComponentType>&;

    template <
        ::xrn::ecs::component::ConceptType ComponentType
    > [[ nodiscard ]] auto vectorExists() const
        -> bool;



    // ------------------------------------------------------------------ SubContainers
    // Those functions are unsafe and should be use with caution

    template <
        ::xrn::ecs::component::ConceptType ComponentType
    > [[ nodiscard ]] auto getUnsafePairSubContainer()
        -> SubPairContainerType&;

    template <
        ::xrn::ecs::component::ConceptType ComponentType
    > [[ nodiscard ]] auto getUnsafePairSubContainer() const
        -> const SubPairContainerType&;



private:

    Container::Type m_container{};

};



} // namespace xrn::ecs::component::

#include <Ecs/Component/Container.impl.hpp>
