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
		friend SerializationObject &operator<<(SerializationObject&so, ISerializable&obj);
		friend SerializationObject &operator<<(SerializationObject&so, const s32);
		friend SerializationObject &operator<<(SerializationObject&so, const f32);
		friend SerializationObject &operator<<(SerializationObject&so, const char * const);

		DECLARE_PRIVATE_MPRIVATE_PIMPL(SerializationObject)

	};

	SerializationObject VORTEX_API &operator<<(SerializationObject&so, ISerializable&obj);
	SerializationObject VORTEX_API &operator<<(SerializationObject&so, const s32);
	SerializationObject VORTEX_API &operator<<(SerializationObject&so, const f32);
	SerializationObject VORTEX_API &operator<<(SerializationObject&so, const char * const);

	class VORTEX_API ISerializable
	{
	public:
		virtual SerializationObject &serialize(SerializationObject &so) { return so; };
		virtual SerializationObject &deserialize(SerializationObject&so) { return so; }
	};
}

#endif

