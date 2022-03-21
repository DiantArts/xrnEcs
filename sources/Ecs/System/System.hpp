#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Ecs/Signature.hpp>
#include <Ecs/System/Detail/Meta/Function.hpp>
#include <Ecs/System/ASystem.hpp>

namespace xrn::ecs::component { class Container; }
namespace xrn::ecs::entity { class Container; }


namespace xrn::ecs::system {

///////////////////////////////////////////////////////////////////////////
/// \brief Simplifies time measures
/// \ingroup ecs-system
///
/// \include System.hpp <Ecs/System/System.hpp>
///
/// Represents the system of the xrn's ECS. This class allows actions
/// (represented by callable - functions or classes with operator())
/// on components.
///
/// Usage example:
/// \code
/// \endcode
///
/// \see ::xrn::ecs::component::declaration::detail::AComponent
///
///////////////////////////////////////////////////////////////////////////
template <
    auto function,
    typename... Types
> class System
    : public ::xrn::ecs::system::ASystem
{

public:

    // ------------------------------------------------------------------ Constructors

    constexpr System();



    // ------------------------------------------------------------------ Run

    constexpr void operator()(
        ::xrn::Time t,
        ::xrn::ecs::entity::Container& entities,
        ::xrn::ecs::component::Container& components
    ) override;

    constexpr void operator()(
        ::xrn::Time t,
        ::xrn::ecs::component::Container& components,
        ::xrn::ecs::entity::Container& entities
    );

    constexpr void operator()(
        ::xrn::Time t,
        const ::xrn::ecs::entity::Container& entities,
        const ::xrn::ecs::component::Container& components
    ) const override;

    constexpr void operator()(
        ::xrn::Time t,
        const ::xrn::ecs::component::Container& components,
        const ::xrn::ecs::entity::Container& entities
    ) const;



    // ------------------------------------------------------------------ Signature

    [[ nodiscard ]] static consteval auto getSignature()
        -> ::xrn::ecs::Signature;



private:

    // static inline constexpr auto m_signature{
        // ::xrn::ecs::detail::meta::Function<decltype(function)>::Arguments::signature.template add<Types...>()
    // };

};

} // namespace xrn::ecs::system



///////////////////////////////////////////////////////////////////////////
// Alias name
///////////////////////////////////////////////////////////////////////////
namespace xrn::ecs {
    template <
        auto function,
        typename... Types
    > using System = ::xrn::ecs::system::System<function, Types...>;
}
