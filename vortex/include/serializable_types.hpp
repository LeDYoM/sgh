#ifndef VTX_SERIALIZABLE_TYPES_INCLUDE_HPP
#define VTX_SERIALIZABLE_TYPES_INCLUDE_HPP

#include "comp_config.hpp"
#include "types.hpp"
#include "vector2d.hpp"
#include "iserializable.hpp"
#include "serialization_buffer.hpp"
#include "serialization_object.hpp"

namespace vtx
{
	class VORTEX_API SerializableVector2d : public vector2ds32, public ISerializable
	{
		virtual SerializationBuffer &serialize(SerializationBuffer &so) const override {
			so.getNew("x").setValue(x);
			so.getNew("y").setValue(y);
			return so;
		};
		virtual SerializationBuffer &deserialize(SerializationBuffer&so) override { return so; }
	};

}

#endif

