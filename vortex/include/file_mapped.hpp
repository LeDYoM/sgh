#ifndef VTX_FILEMAPPED_INCLUDE_HPP
#define VTX_FILEMAPPED_INCLUDE_HPP

#include "comp_config.hpp"
#include "common_def.hpp"
#include "str.hpp"
#include "serialization_object.hpp"

namespace vtx
{
	class VORTEX_API FileMapped
	{
	public:
		FileMapped(const Str &fileName);
		~FileMapped();
		virtual void serialize() const;
	private:
		SerializationObject m_serializationObject;
	};
}

#endif

