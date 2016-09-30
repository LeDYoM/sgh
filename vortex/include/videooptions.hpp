#ifndef VTX_VIDEOOPTIONS_INCLUDE_HPP
#define VTX_VIDEOOPTIONS_INCLUDE_HPP

#include "config_group.hpp"
#include "comp_config.hpp"
#include "properties.hpp"
#include "vector2d.hpp"

namespace vtx
{
	class VORTEX_API VideoOptions : public ConfigGroup
	{
	public:
		VideoOptions() = default;
		virtual ~VideoOptions() = default;

	private:
		vector2ds32 resolution;
	};
}

#endif
