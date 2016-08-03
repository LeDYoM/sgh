#ifndef LIB_TEXTURE_HPP
#define LIB_TEXTURE_HPP

#include <lib/include/types.hpp>

namespace lib
{
	namespace drivers
	{
		namespace render
		{
			class Texture;
		}
	}

	namespace draw
	{
		class Texture
		{
		private:
			Texture(uptr<drivers::render::Texture>&);
			virtual ~Texture();

			uptr<drivers::render::Texture> m_driverTexture;
		};
	}
}

#endif
