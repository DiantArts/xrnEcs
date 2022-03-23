#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Util/Id.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Start the component declaration
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/// Declares helpers
///////////////////////////////////////////////////////////////////////////
namespace xrn::ecs::component::declaration::detail {
    template <typename> class IdHandler;
    template <::xrn::Id::Type id> struct IdInfo;
    template <typename T> struct IsComponent : public ::std::false_type {};
    template <typename T> struct IsAbility : public ::std::false_type {};
    static inline constexpr const ::std::size_t baseIdCounter{ __COUNTER__ + 1 };
} // namespace xrn::ecs::component::declaration::detail



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Macro definition
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/// \brief Declares a component
///
/// Registers the type given as macro parameter as part of the components
/// of the program.
/// This macro only works inside the namespace (or subnamespace)
/// "xrn::ecs::component::declaration". Otherwise, use
/// COMPONENT_IN_NAMESPACE.
///
/// \warning Using this macro outside of the files included bellow next to
/// the base file "Ecs/Component/Declaration.hpp" leads to undefined
/// behaviors.
///
/// \see COMPONENT_IN_NAMESPACE()
///
///////////////////////////////////////////////////////////////////////////
#define COMPONENT(className) \
    class className; \
    template <> class xrn::ecs::component::declaration::detail::IdHandler<className> { \
    public: [[ nodiscard ]] static inline consteval ::std::size_t getId() { return m_id; } \
    private: static inline constexpr const auto m_id{ \
            __COUNTER__ - ::xrn::ecs::component::declaration::detail::baseIdCounter \
        }; \
    }; \
    template < \
    > struct xrn::ecs::component::declaration::detail::IdInfo< \
        ::xrn::ecs::component::declaration::detail::IdHandler<className>::getId() \
    > { using Type = className; }; \
    template <> \
    struct xrn::ecs::component::declaration::detail::IsComponent<className> \
        : public ::std::true_type \
    {}; \
    class className \
        : public ::xrn::ecs::component::declaration::detail::IdHandler<::std::remove_cvref_t<className>> \

///////////////////////////////////////////////////////////////////////////
/// \brief Declares a component in a namespace
///
/// Registers the type given as macro parameter as part of the components
/// of the program.
/// The namespace given as parameter must be the current namespace when the
/// macro is called.
///
/// \warning Using this macro outside of the files included bellow next to
/// the base file "Ecs/Component/Declaration.hpp" leads to undefined
/// behaviors.
///
///////////////////////////////////////////////////////////////////////////
#define COMPONENT_IN_NAMESPACE(namespaceName, className) \
    class className; \
    } /* leaving namespace */ \
    template <> class xrn::ecs::component::declaration::detail::IdHandler<namespaceName::className> { \
    public: [[ nodiscard ]] static inline consteval ::std::size_t getId() { return m_id; } \
    private: static inline constexpr const auto m_id{ \
            __COUNTER__ - ::xrn::ecs::component::declaration::detail::baseIdCounter \
        }; \
    }; \
    template < \
    > struct xrn::ecs::component::declaration::detail::IdInfo< \
        ::xrn::ecs::component::declaration::detail::IdHandler<namespaceName::className>::getId() \
    > { using Type = namespaceName::className; }; \
    template <> \
    struct xrn::ecs::component::declaration::detail::IsComponent<namespaceName::className> \
        : public ::std::true_type \
    {}; \
    namespace namespaceName { /* reentering namespace */ \
    class className \
        : public ::xrn::ecs::component::declaration::detail::IdHandler<::std::remove_cvref_t<className>> \

///////////////////////////////////////////////////////////////////////////
/// \brief Declares an ability
///
/// Registers the type given as macro parameter as an ability. Abilities
/// are empty uninstantiable componens only providing a functionality to
/// the linked entity. It will only be used through the signature as it
/// possess an ID.
/// The namespace given as parameter must be the current namespace when the
/// macro is called.
///
/// \warning Using this macro outside of the files included bellow next to
/// the base file "Ecs/Component/Declaration.hpp" leads to undefined
/// behaviors.
///
///////////////////////////////////////////////////////////////////////////
#define ABILITY(className) \
    class className; \
    template <> class xrn::ecs::component::declaration::detail::IdHandler<className> { \
    public: [[ nodiscard ]] static inline consteval ::std::size_t getId() { return m_id; } \
    private: static inline constexpr const auto m_id{ \
            __COUNTER__ - ::xrn::ecs::component::declaration::detail::baseIdCounter \
        }; \
    }; \
    template < \
    > struct xrn::ecs::component::declaration::detail::IdInfo< \
        ::xrn::ecs::component::declaration::detail::IdHandler<className>::getId() \
    > { using Type = className; }; \
    template <> \
    struct xrn::ecs::component::declaration::detail::IsAbility<className> \
        : public ::std::true_type \
    {}; \
    class className final \
        : public ::xrn::ecs::component::declaration::detail::IdHandler<::std::remove_cvref_t<className>> \
    { className(); } \

///////////////////////////////////////////////////////////////////////////
/// \brief Declares an ability in a namespace
///
/// Registers the type given as macro parameter as an ability. Abilities
/// are empty uninstantiable componens only providing a functionality to
/// the linked entity. It will only be used through the signature as it
/// possess an ID.
/// The namespace given as parameter must be the current namespace when the
/// macro is called.
///
/// \warning Using this macro outside of the files included bellow next to
/// the base file "Ecs/Component/Declaration.hpp" leads to undefined
/// behaviors.
///
///////////////////////////////////////////////////////////////////////////
#define ABILITY_IN_NAMESPACE(namespaceName, className) \
    class className; \
    } /* leaving namespace */ \
    template <> class xrn::ecs::component::declaration::detail::IdHandler<namespaceName::className> { \
    public: [[ nodiscard ]] static inline consteval ::std::size_t getId() { return m_id; } \
    private: static inline constexpr const auto m_id{ \
            __COUNTER__ - ::xrn::ecs::component::declaration::detail::baseIdCounter \
        }; \
    }; \
    template < \
    > struct xrn::ecs::component::declaration::detail::IdInfo< \
        ::xrn::ecs::component::declaration::detail::IdHandler<namespaceName::className>::getId() \
    > { using Type = namespaceName::className; }; \
    template <> \
    struct xrn::ecs::component::declaration::detail::IsAbility<namespaceName::className> \
        : public ::std::true_type \
    {}; \
    namespace namespaceName { /* reentering namespace */ \
    class className final \
        : public ::xrn::ecs::component::declaration::detail::IdHandler<::std::remove_cvref_t<className>> \
    { className(); } \




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Test components (details hidden)
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/// Declares the components used for unit testing. Can be concidered as
/// implemetation details.
///////////////////////////////////////////////////////////////////////////
#ifdef TEST
namespace xrn::ecs::component::test {
ABILITY_IN_NAMESPACE(xrn::ecs::component::test, AbilityA);
ABILITY_IN_NAMESPACE(xrn::ecs::component::test, AbilityB);
COMPONENT_IN_NAMESPACE(xrn::ecs::component::test, ComponentA) {
public:
    auto operator<=>(const ::xrn::ecs::component::test::ComponentA& other) const
    { return value <=> other.value; }
    auto operator==(const ::xrn::ecs::component::test::ComponentA& other) const
    { return value == other.value; }
    int value{ 0 };
};
COMPONENT_IN_NAMESPACE(xrn::ecs::component::test, ComponentB) {
public:
    ComponentB(int val = 0) : value{ val } {}
    auto operator<=>(const ::xrn::ecs::component::test::ComponentB& other) const
    { return value <=> other.value; }
    int value{ 0 };
};
COMPONENT_IN_NAMESPACE(xrn::ecs::component::test, Benchmark100ints) {
public:
    int value[100];
};
} // namespace xrn::ecs::component::test
#endif // TEST



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// User-defined Components
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// contains the user-defined components using the macros declared
// above.
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// Ecs/Component/Declaration.hpp is the base file, but more can be added
// and included here.
///////////////////////////////////////////////////////////////////////////
#ifndef TEST
#include <Ecs/Component/Declaration.hpp>
#endif // aTEST



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Start the component declaration
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/// Declares 'IdHandler' class and initializes baseIdCounter
///////////////////////////////////////////////////////////////////////////
namespace xrn::ecs::component {
    static inline constexpr const auto maxId{
        __COUNTER__ - ::xrn::ecs::component::declaration::detail::baseIdCounter
    };
    template <auto id> using IdInfo = ::xrn::ecs::component::declaration::detail::IdInfo<id>;
} // namespace xrn::ecs

namespace xrn::ecs {
    template <typename T> using IsComponent = xrn::ecs::component::declaration::detail::IsComponent<T>;
    template <typename T> inline constexpr const auto IsComponent_v = xrn::ecs::IsComponent<T>::value;
    template <typename T> inline constexpr const auto isComponent = xrn::ecs::IsComponent<T>::value;
    template <typename T> using IsAbility = xrn::ecs::component::declaration::detail::IsAbility<T>;
    template <typename T> inline constexpr const auto IsAbility_v = xrn::ecs::IsAbility<T>::value;
    template <typename T> inline constexpr const auto isAbility = xrn::ecs::IsAbility<T>::value;
} // namespace xrn::ecs



///////////////////////////////////////////////////////////////////////////
/// Macros undefinition
///////////////////////////////////////////////////////////////////////////
#undef COMPONENT
#undef COMPONENT
