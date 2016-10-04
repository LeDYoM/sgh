#ifndef VTX_VIDEOOPTIONS_INCLUDE_HPP
#define VTX_VIDEOOPTIONS_INCLUDE_HPP

#include "file_map.hpp"
#include "comp_config.hpp"
#include "properties.hpp"
#include "serializable_types.hpp"
#include "serialization_buffer.hpp"

namespace vtx
{
	class VORTEX_API VideoOptions : public FileMap, public ISerializable
	{
	public:
		VideoOptions() = default;
		virtual ~VideoOptions() = default;

	private:
		SerializableVector2d resolution;
	};
}

#endif
