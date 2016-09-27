#include "include/str.hpp"
#include "common_def_priv.hpp"

#include <string>

namespace vtx
{
	PRIVATE_STRUCT_DEFINITION(Str)
	{
		std::string str;
		PRIVATE_STRUCT_NAME(Str)() : str{} {}
		PRIVATE_STRUCT_NAME(Str)(const char* data) : str(data) {}
		PRIVATE_STRUCT_NAME(Str)(const PRIVATE_STRUCT_NAME(Str) &rh) : str(rh.str) {}
		PRIVATE_STRUCT_NAME(Str) &operator=(const PRIVATE_STRUCT_NAME(Str) &rh) { str = rh.str; return *this; }
	};

	Str::Str() : m_private{ new PRIVATE_STRUCT_NAME(Str) } { }
	Str::Str(const char *data) : m_private{ new PRIVATE_STRUCT_NAME(Str)(data) } { }
	Str::Str(const Str&rh) : m_private{ new PRIVATE_STRUCT_NAME(Str)(*(rh.m_private)) } { }
	Str &Str::operator=(const Str&rh) { m_private->operator=(*(rh.m_private)); return *this; }

	Str::~Str()
	{
		DELETE_PRIVATE_MPRIVATE_PIMPL(Str);
	}
}