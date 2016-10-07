#ifndef VTX_VIDEOOPTIONS_INCLUDE_HPP
#define VTX_VIDEOOPTIONS_INCLUDE_HPP

#include "comp_config.hpp"
#include "vector2d.hpp"
#include "file_mapped.hpp"

namespace vtx
{
	class VORTEX_API VideoOptions : public FileMapped
	{
	public:
		VideoOptions() : FileMapped() {}
		virtual ~VideoOptions() = default;

		virtual void save() const override {}

	private:
		vector2ds32 resolution;
	};
}

#endif
