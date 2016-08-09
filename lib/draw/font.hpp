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

	namespace core
	{
		namespace managers
		{
			class TextureManager;
		}
	}

	namespace draw
	{
		class Texture
		{
		private:
			Texture(drivers::render::Texture*);
			virtual ~Texture();

			drivers::render::Texture *m_driverTexture;
			friend class core::managers::TextureManager;
		};
	}
}

#endif
