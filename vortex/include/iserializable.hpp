#ifndef VTX_ISERIALIZABLE_INCLUDE_HPP
#define VTX_ISERIALIZABLE_INCLUDE_HPP

#include "comp_config.hpp"
#include "common_def.hpp"

namespace vtx
{
	class SerializationBuffer;

	class ISerializable
	{
	public:
		virtual SerializationBuffer &serialize(SerializationBuffer &so) const = 0;
		virtual SerializationBuffer &deserialize(SerializationBuffer&so) = 0;
	};
}

#endif

