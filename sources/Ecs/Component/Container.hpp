#pragma once

#include <Util/Id.hpp>
#include <Meta/UniqueTypes.hpp>
#include <Ecs/Detail/Constraint.hpp>
#include <Ecs/Component/AComponent.hpp>



namespace xrn::ecs::component {



class Container {

public:

    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > using SubContainerType = ::std::vector<std::remove_cvref_t<ComponentType>>;

    // map[ComponentId].first == vector<EntityId>
    // map[ComponentId].second  == vector<ComponentType>
    using SubPairContainerType = ::std::pair<::std::vector<::xrn::Id>, void*>;

    using Type = ::std::unordered_map<
        ::xrn::Id, Container::SubPairContainerType, ::xrn::Id::Hasher
    >;



public:

    // ~Container();

    // ------------------------------------------------------------------ Id

    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] constexpr auto getId() const
        -> ::xrn::Id;

    [[ nodiscard ]] static consteval auto getMaxId()
        -> ::xrn::Id;



    // ------------------------------------------------------------------ Emplace/Remove

    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > auto emplace(
        ::xrn::Id entityId,
        auto&&... args
    ) -> ComponentType&;

    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void emplaceMany(
        ::xrn::Id entityId
    );

    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > void push(
        ::xrn::Id entityId,
        ComponentType&& component
    );

    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void pushMany(
        ::xrn::Id entityId,
        ComponentTypes&&... components
    );

    template <
        ::xrn::ecs::detail::constraint::isComponent... ComponentTypes
    > void removeMany(
        ::xrn::Id entityId
    );

    void removeMany(
        ::xrn::Id entityId,
        ::xrn::ecs::detail::constraint::isId auto... componentIds
    );

    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > void remove(
        ::xrn::Id entityId
    );

    void remove(
        ::xrn::Id entityId,
        ::xrn::Id componentId
    );

    inline void clear();




    // ------------------------------------------------------------------ Get

    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto get(
        ::xrn::Id entityId
    ) const
        -> const ComponentType&;

    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto get(
        ::xrn::Id entityId
    )
        -> ComponentType&;

    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto getIndex(
        ::xrn::Id entityId
    ) const
        -> ::std::size_t;

    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto exists(
        ::xrn::Id entityId
    ) const
        -> bool;



    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto getVector() const
        -> const ::std::vector<ComponentType>&;

    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > void removeVector();

    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > void removeVector(
        ::xrn::Id entityId
    );

    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto vectorExists() const
        -> bool;



private:

    // ------------------------------------------------------------------ SubContainers
    // Those functions are unsafe and should be use with caution

    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto getUnsafePairSubContainer()
        -> SubPairContainerType&;

    template <
        ::xrn::ecs::detail::constraint::isComponent ComponentType
    > [[ nodiscard ]] auto getUnsafePairSubContainer() const
        -> const SubPairContainerType&;

    [[ nodiscard ]] auto getUnsafePairSubContainer(
        ::xrn::Id id
    ) -> SubPairContainerType&;



private:

    Container::Type m_container{};

};



} // namespace xrn::ecs::component::
