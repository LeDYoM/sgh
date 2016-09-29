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

	vtx::Str::Str(const u64 data) noexcept : m_private{ new PRIVATE_STRUCT_NAME(Str)(std::to_string(data).c_str()) } { }
	vtx::Str::Str(const s64 data) noexcept : m_private{ new PRIVATE_STRUCT_NAME(Str)(std::to_string(data).c_str()) } { }
	vtx::Str::Str(const f64 data) noexcept : m_private{ new PRIVATE_STRUCT_NAME(Str)(std::to_string(data).c_str()) } { }
	Str::Str(const Str&rh) noexcept : m_private{ new PRIVATE_STRUCT_NAME(Str)(*(rh.m_private)) } { }
	Str &Str::operator=(const Str&rh) noexcept { m_private->operator=(*(rh.m_private)); return *this; }
	constexpr Str::Str(Str&&rh) noexcept : m_private{ std::move(rh.m_private) } { }
	Str &Str::operator=(Str&&rh) noexcept { m_private = std::move(rh.m_private); rh.m_private = nullptr; return *this; }

	Str::Str(const char *data) noexcept : m_private{ new PRIVATE_STRUCT_NAME(Str)(data) } { }

	const char * Str::c_str() const noexcept { return m_private->str.c_str(); }

	Str & Str::operator+=(const Str & other)
	{
		m_private->str += other.m_private->str;
		return *this;
	}

	Str & Str::operator+=(const u64 n)
	{
		m_private->str += std::to_string(n);
		return *this;
	}

	Str & Str::operator+=(const s64 n)
	{
		m_private->str += std::to_string(n);
		return *this;
	}

	Str & Str::operator+=(const u32 n)
	{
		m_private->str += std::to_string(n);
		return *this;
	}

	Str & Str::operator+=(const s32 n)
	{
		m_private->str += std::to_string(n);
		return *this;
	}

	Str & Str::operator+=(const u16 n)
	{
		m_private->str += std::to_string(n);
		return *this;
	}

	Str & Str::operator+=(const s16 n)
	{
		m_private->str += std::to_string(n);
		return *this;
	}

	Str & Str::operator+=(const u8 n)
	{
		m_private->str += std::to_string(n);
		return *this;
	}

	Str & Str::operator+=(const s8 n)
	{
		m_private->str += std::to_string(n);
		return *this;
	}

	Str & Str::operator+=(const f64 n)
	{
		m_private->str += std::to_string(n);
		return *this;
	}

	Str & Str::operator+=(const f32 n)
	{
		m_private->str += std::to_string(n);
		return *this;
	}

	Str & Str::operator<<(const Str & other)
	{
		return operator+=(other);
	}

	Str & vtx::Str::operator<<(const u64 n)
	{
		return operator+=(n);
	}

	Str & vtx::Str::operator<<(const s64 n)
	{
		return operator+=(n);
	}

	Str & vtx::Str::operator<<(const f64 n)
	{
		return operator+=(n);
	}

	Str::~Str()
	{
		DELETE_PRIVATE_MPRIVATE_PIMPL(Str);
	}
}