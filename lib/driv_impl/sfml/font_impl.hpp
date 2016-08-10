#ifndef LIB_DRIVERS_SFML_FONT_IMPLEMENTATION_HPP
#define LIB_DRIVERS_SFML_FONT_IMPLEMENTATION_HPP

#include <lib/include/types.hpp>
#include <lib/drivers/render/font.hpp>
#include <SFML/Graphics/Font.hpp>

namespace lib
{
	namespace drivers
	{
		namespace render
		{
			class SFMLFont : public Font
			{
			public:
				SFMLFont();
				virtual ~SFMLFont();

				virtual bool loadFromFile(const str &filename) override;
				virtual bool loadFromMemory(const void *data, std::size_t size) override;

			private:
				sf::Font m_internalFont;
			};
		}
	}
}

#endif
