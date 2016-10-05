#ifndef VTX_ISERIALIZABLE_INCLUDE_HPP
#define VTX_ISERIALIZABLE_INCLUDE_HPP

#include "comp_config.hpp"
#include "common_def.hpp"

#define SER_NVP(x)	#x,x
namespace vtx
{
	class SerializationObject;

	class ISerializable
	{
	public:
		virtual SerializationObject & serialize(SerializationObject &so) const = 0;
		virtual SerializationObject & deserialize(SerializationObject&so) = 0;
	};
}

#endif

