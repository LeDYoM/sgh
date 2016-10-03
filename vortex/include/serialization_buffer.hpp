#ifndef VTX_SERIALIZATION_BUFFER_INCLUDE_HPP
#define VTX_SERIALIZATION_BUFFER_INCLUDE_HPP

#include "comp_config.hpp"
#include "common_def.hpp"
#include "types.hpp"
#include "str.hpp"

namespace vtx
{
	class ISerializable;
	class SerializationObject;
	class VORTEX_API SerializationBuffer
	{
	public:
		friend class SerializationObject;
		SerializationObject &getNew(const char *const);

		DECLARE_PRIVATE_MPRIVATE_PIMPL(SerializationBuffer)
	};

	class VORTEX_API ISerializable
	{
	public:
		virtual SerializationObject &serialize(SerializationObject &so) { return so; };
		virtual SerializationObject &deserialize(SerializationObject&so) { return so; }
	};
}

#endif

