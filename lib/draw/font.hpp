#ifndef LIB_DRAW_FONT_HPP
#define LIB_DRAW_FONT_HPP

#include <lib/include/types.hpp>

namespace lib
{
	namespace drivers
	{
		namespace render
		{
			class Font;
		}
	}

	namespace core
	{
		namespace managers
		{
			class FontManager;
		}
	}

	namespace draw
	{
		class Texture
		{
		private:
			Texture(drivers::render::Font*);
			virtual ~Texture();

			drivers::render::Font *m_driverFont;
			friend class core::managers::FontManager;
		};
	}
}

#endif
