#ifndef VTX_CONFIG_GROUP_INCLUDE_HPP
#define VTX_CONFIG_GROUP_INCLUDE_HPP

#include "comp_config.hpp"
#include "types.hpp"
#include "str.hpp"

namespace vtx
{
	class VORTEX_API ConfigGroup
	{
	public:
		ConfigGroup() = default;
		~ConfigGroup() = default;

	protected:
		void addProperty(const Str &name, const u64) noexcept;
		void addProperty(const Str &name, const s64) noexcept;
		void addProperty(const Str &name, const f64) noexcept;
	};
}

#endif
