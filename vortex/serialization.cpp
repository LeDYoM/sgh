#include "include/serialization.hpp"

namespace vtx
{
	Str & vtx::operator<<(Str & string, const u64 n)
	{
		return (string += n);
	}

	Str & vtx::operator<<(Str & string, const s64 n)
	{
		return (string += n);
	}

	Str & vtx::operator<<(Str & string, const f64 n)
	{
		return (string += n);
	}
}
