#ifndef LIB_DRIVERS_TEXTURE_HPP
#define LIB_DRIVERS_TEXTURE_HPP

#include <lib/include/types.hpp>

namespace lib
{
	namespace drivers
	{
		namespace render
		{
			class Texture
			{
				virtual bool create(const vector2du32 &size) = 0;
				virtual bool loadFromFile(const str &filename, const Rects32 &area) = 0;
				virtual bool loadFromMemory(const void *data, std::size_t size, const Rects32 &area) = 0;
			};
		}
	}
}

#endif
