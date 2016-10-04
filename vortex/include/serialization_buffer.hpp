#ifndef VTX_SERIALIZATION_BUFFER_INCLUDE_HPP
#define VTX_SERIALIZATION_BUFFER_INCLUDE_HPP

#include "comp_config.hpp"
#include "common_def.hpp"
#include "types.hpp"
#include "str.hpp"

namespace vtx
{
	class SerializationObject;
	class VORTEX_API SerializationBuffer
	{
	public:
		friend class SerializationObject;
		SerializationObject &getNew(const char *const);

		SerializationBuffer() = default;
		~SerializationBuffer() = default;

		bool writeFile(const Str&);

	private:
		DECLARE_PRIVATE_MPRIVATE_PIMPL(SerializationBuffer)
	};
}

#endif

