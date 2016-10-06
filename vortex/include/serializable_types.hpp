#ifndef VTX_SERIALIZABLE_TYPES_INCLUDE_HPP
#define VTX_SERIALIZABLE_TYPES_INCLUDE_HPP

#include "comp_config.hpp"
#include "types.hpp"
#include "vector2d.hpp"
#include "serialization_object.hpp"

namespace vtx
{
	void VORTEX_API DoSerialize(SerializationObject&, const vector2ds32&);
}

#endif

