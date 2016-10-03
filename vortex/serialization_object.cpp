#include "include/serialization_object.hpp"
#include "include/serialization_buffer.hpp"

#include "common_def_priv.hpp"

namespace vtx
{
	enum SerializationPropertyTypes : int
	{
		Ts32 = 0,
		Tf32,
		Tstr,
	};

	PRIVATE_STRUCT_DEFINITION(SerializationObject)
	{
		const SerializationBuffer *m_parentBuffer;
		SerializationPropertyTypes m_prtype;
		Str m_prName;
		Str m_prValue;
		PRIVATE_STRUCT_NAME(SerializationObject)(const SerializationBuffer *parentBuffer)
			: m_parentBuffer{ parentBuffer } {}
	};

	SerializationObject::SerializationObject(const SerializationBuffer *parentBuffer)
		: m_private{new PRIVATE_STRUCT_NAME(SerializationObject)(parentBuffer) } {}

	SerializationObject & SerializationObject::setName(const Str &name)
	{
		m_private->m_prName = name;
	}

	SerializationObject & SerializationObject::setValue(const s32 value)
	{
		m_private->m_prtype = SerializationPropertyTypes::Ts32;
		m_private->m_prValue = value;
	}

}
