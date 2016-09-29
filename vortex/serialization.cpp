#include "include/serialization.hpp"

#include "common_def_priv.hpp"

namespace vtx
{
	PRIVATE_STRUCT_DEFINITION(SerializationBuffer)
	{
	};

	SerializationBuffer & SerializationBuffer::addProperty(const char * const, const s32)
	{
		return *this;
	}
	SerializationBuffer & SerializationBuffer::addProperty(const char * const, const f32)
	{
		return *this;
	}
}
