#ifndef VTX_SERIALIZABLE_INCLUDE_HPP
#define VTX_SERIALIZABLE_INCLUDE_HPP

#include "comp_config.hpp"
#include "common_def.hpp"
#include "types.hpp"
#include "str.hpp"

namespace vtx
{
	class SerializationObject
	{
		SerializationObject & SerializationObject::addProperty(const char * const, const s32);
		SerializationObject & SerializationObject::addProperty(const char * const, const f32);

		DECLARE_PRIVATE_MPRIVATE_PIMPL(SerializationObject)
	};

}

#endif

