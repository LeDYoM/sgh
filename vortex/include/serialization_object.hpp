#ifndef VTX_SERIALIZATION_OBJECT_INCLUDE_HPP
#define VTX_SERIALIZATION_OBJECT_INCLUDE_HPP

#include "comp_config.hpp"
#include "common_def.hpp"
#include "str.hpp"

namespace vtx
{
	class ISerializable;
	class SerializationBuffer;

	class VORTEX_API SerializationObject
	{
	public:
		friend class SerializationBuffer;
		SerializationObject & setName(const Str&);
		SerializationObject & setValue(const s32);
	private:
		SerializationObject(const SerializationBuffer *parentBuffer);
		DECLARE_PRIVATE_MPRIVATE_PIMPL(SerializationObject)
	};
}

#endif

