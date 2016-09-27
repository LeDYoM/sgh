#include "include/str.hpp"
#include "common_def_priv.hpp"

#include <string>

namespace vtx
{
	PRIVATE_STRUCT_DEFINITION(Str)
	{
		std::string str;
		constexpr PRIVATE_STRUCT_NAME(Str)() : str{} {}
		constexpr PRIVATE_STRUCT_NAME(Str)(const char* data) : str(data) {}
		constexpr PRIVATE_STRUCT_NAME(Str)(const PRIVATE_STRUCT_NAME(Str) &rh) : str(rh.str) {}
		PRIVATE_STRUCT_NAME(Str) &operator=(const PRIVATE_STRUCT_NAME(Str) &rh) { str = rh.str; return *this; }
	};

	Str::Str() : m_private{ new PRIVATE_STRUCT_NAME(Str) } { }
	Str::Str(const Str&rh) : m_private{ new PRIVATE_STRUCT_NAME(Str)(*(rh.m_private)) } { }
	Str &Str::operator=(const Str&rh) { m_private->operator=(*(rh.m_private)); return *this; }
	constexpr Str::Str(Str&&rh) : m_private{ std::move(rh.m_private) } { }
	Str &Str::operator=(Str&&rh) { m_private = std::move(rh.m_private); rh.m_private = nullptr; return *this; }

	Str::Str(const char *data) : m_private{ new PRIVATE_STRUCT_NAME(Str)(data) } { }

	const char * Str::c_str() const
	{
		return m_private->str.c_str();
	}

	Str::~Str()
	{
		DELETE_PRIVATE_MPRIVATE_PIMPL(Str);
	}
}