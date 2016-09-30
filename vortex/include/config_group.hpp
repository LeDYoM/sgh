#ifndef VTX_CONFIG_GROUP_INCLUDE_HPP
#define VTX_CONFIG_GROUP_INCLUDE_HPP

#include "comp_config.hpp"
#include "types.hpp"
#include "str.hpp"
#include "serialization.hpp"
#include "properties.hpp"

namespace vtx
{
	class VORTEX_API ConfigGroup
	{
	public:
		ConfigGroup() = default;
		~ConfigGroup() = default;

	protected:
		virtual SerializationObject &serialize(SerializationObject&);
	};
}

#endif
