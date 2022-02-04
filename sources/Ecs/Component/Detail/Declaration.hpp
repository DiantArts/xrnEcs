#pragma once

#define START_COMPONENT_DECLARATIONS() \
    namespace xrn::ecs::component::declaration::detail { \
        template <typename> class WithId; \
        inline constexpr const ::std::size_t baseIdCounter { __COUNTER__ + 1 }; \
    } \
    class RandomAndTotallyUnexistantVarThatJustIsUsefulForTheSumicolon

#define DECLARE_COMPONENT(className) \
    class className; \
    template <> \
    class xrn::ecs::component::declaration::detail::WithId<className> { \
    public: \
        [[ nodiscard ]] static inline constexpr ::std::size_t getId() { return m_id; } \
    private: \
        static inline constexpr auto m_id { __COUNTER__ - ::xrn::ecs::component::declaration::detail::baseIdCounter }; \
    }

#define DECLARE_COMPONENT_IN_NAMESPACE(namespaceName, className) \
    namespace namespaceName { class className; } \
    template <> \
    class xrn::ecs::component::declaration::detail::WithId<namespaceName::className> { \
    public: \
        [[ nodiscard ]] static inline constexpr ::std::size_t getId() { return m_id; } \
    private: \
        static inline constexpr auto m_id { __COUNTER__ - ::xrn::ecs::component::declaration::detail::baseIdCounter }; \
    }

#define STOP_COMPONENT_DECLARATIONS() \
    namespace xrn::ecs::component::declaration::detail { \
        inline constexpr ::std::size_t numberOfIds \
            { __COUNTER__ - ::xrn::ecs::component::declaration::detail::baseIdCounter }; \
    } \
    class RandomAndTotallyUnexistantVarThatJustIsUsefulForTheSumicolon
