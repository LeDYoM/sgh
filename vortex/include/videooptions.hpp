#ifndef VTX_VIDEOOPTIONS_INCLUDE_HPP
#define VTX_VIDEOOPTIONS_INCLUDE_HPP

#include "comp_config.hpp"
#include "properties.hpp"
#include "serializable_types.hpp"

namespace vtx
{
	class VORTEX_API VideoOptions : public ISerializable
	{
	public:
		VideoOptions() = default;
		virtual ~VideoOptions() = default;

	private:
//		SerializableVector2d resolution;
	};
}

#endif
