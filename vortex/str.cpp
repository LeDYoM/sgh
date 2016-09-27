#include "include/str.hpp"
#include "common_def_priv.hpp"

#include <string>

namespace vtx
{
	PRIVATE_STRUCT_DEFINITION(Str)
	{
		std::string str;
		constexpr PRIVATE_STRUCT_NAME(Str)() noexcept : str{} {}
		constexpr PRIVATE_STRUCT_NAME(Str)(const char* data) noexcept : str(data) {}
		constexpr PRIVATE_STRUCT_NAME(Str)(const PRIVATE_STRUCT_NAME(Str) &rh) noexcept : str(rh.str) {}
		PRIVATE_STRUCT_NAME(Str) &operator=(const PRIVATE_STRUCT_NAME(Str) &rh) noexcept { str = rh.str; return *this; }
	};

	Str::Str() noexcept : m_private{ new PRIVATE_STRUCT_NAME(Str) } { }
	Str::Str(const Str&rh) noexcept : m_private{ new PRIVATE_STRUCT_NAME(Str)(*(rh.m_private)) } { }
	Str &Str::operator=(const Str&rh) noexcept { m_private->operator=(*(rh.m_private)); return *this; }
	constexpr Str::Str(Str&&rh) noexcept : m_private{ std::move(rh.m_private) } { }
	Str &Str::operator=(Str&&rh) noexcept { m_private = std::move(rh.m_private); rh.m_private = nullptr; return *this; }

	Str::Str(const char *data) noexcept : m_private{ new PRIVATE_STRUCT_NAME(Str)(data) } { }

	const char * Str::c_str() const noexcept { return m_private->str.c_str(); }

	Str::~Str()
	{
		DELETE_PRIVATE_MPRIVATE_PIMPL(Str);
	}
}