#ifndef LIB_DRIVERS_SFML_TEXTURE_IMPLEMENTATION_HPP
#define LIB_DRIVERS_SFML_TEXTURE_IMPLEMENTATION_HPP

#include <lib/include/types.hpp>
#include <lib/drivers/render/texture.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace lib
{
	namespace drivers
	{
		namespace render
		{
			class SFMLTexture : public Texture
			{
			public:
				SFMLTexture();
				virtual ~SFMLTexture();

				virtual bool create(const vector2du32 &size) override;
				virtual bool loadFromFile(const str &filename, const Rects32 &area) override;
				virtual bool loadFromMemory(const void *data, std::size_t size, const Rects32 &area) override;
				virtual vector2du32 getSize() const;
				virtual void setSmooth(bool smooth);
				virtual bool isSmooth() const;
				virtual void setRepeated(bool repeated);
				virtual bool isRepeated() const;
			private:
				sf::Texture m_internalTexture;
			};
		}
	}
}

#endif
