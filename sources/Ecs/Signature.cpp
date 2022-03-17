///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <Ecs/Signature.hpp>
#include <Ecs/Component/Detail/ForEach.hpp>



///////////////////////////////////////////////////////////////////////////
void ::xrn::ecs::Signature::reset()
{
    ::xrn::ecs::detail::ForEach::template run<
        []<typename RawType>(
            ::cbitset::Cbitset<::xrn::ecs::component::maxId>& signature
        ){
            using Type = ::std::remove_cvref_t<::std::remove_pointer_t<RawType>>;
            signature.reset(Type::getId());
        }
    >(m_bitset);
}

///////////////////////////////////////////////////////////////////////////
auto operator<<(
    ::std::ostream& os,
    const ::xrn::ecs::Signature& signature
) -> ::std::ostream&
{
    for (auto i{ 0uz }; i < ::xrn::ecs::component::maxId; ++i) {
        os << signature[i];
    }
    return os;
}
