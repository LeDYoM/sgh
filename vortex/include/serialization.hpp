#ifndef VTX_SERIALIZABLE_INCLUDE_HPP
#define VTX_SERIALIZABLE_INCLUDE_HPP

#include "comp_config.hpp"
#include "common_def.hpp"
#include "types.hpp"
#include "str.hpp"

namespace vtx
{
	class VORTEX_API SerializationObject
	{
	public:
		SerializationObject & SerializationObject::addProperty(const char * const, const s32);
		SerializationObject & SerializationObject::addProperty(const char * const, const f32);
		SerializationObject & SerializationObject::addProperty(const char * const, const char * const);

		DECLARE_PRIVATE_MPRIVATE_PIMPL(SerializationObject)
	};

	class VORTEX_API ISerializable
	{
	public:
		virtual SerializationObject &serialize(SerializationObject &so) { return so; };
		virtual SerializationObject &deserialize(SerializationObject&so) { return so; }
	};

	SerializationObject VORTEX_API &operator<<(SerializationObject&so, ISerializable&obj);
	SerializationObject VORTEX_API &operator<<(SerializationObject&so, const s32);
	SerializationObject VORTEX_API &operator<<(SerializationObject&so, const f32);
	SerializationObject VORTEX_API &operator<<(SerializationObject&so, const char * const);

}

#endif

