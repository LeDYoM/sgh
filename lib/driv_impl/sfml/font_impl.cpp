#include "texture_impl.hpp"

namespace lib
{
	namespace drivers
	{
		namespace render
		{
			SFMLTexture::SFMLTexture() : m_internalTexture{}
			{
			}

			SFMLTexture::~SFMLTexture()
			{
			}

			bool SFMLTexture::create(const vector2du32 & size)
			{
				return m_internalTexture.create(size.x, size.y);
			}

			bool SFMLTexture::loadFromFile(const str & filename)
			{
				return m_internalTexture.loadFromFile(filename);
			}

			bool SFMLTexture::loadFromMemory(const void * data, std::size_t size)
			{
				return m_internalTexture.loadFromMemory(data, size);
			}

			vector2du32 SFMLTexture::getSize() const
			{
				return vector2du32{ m_internalTexture.getSize().x,m_internalTexture.getSize().y };
			}

			void SFMLTexture::setSmooth(bool smooth)
			{
				m_internalTexture.setSmooth(smooth);
			}

			bool SFMLTexture::isSmooth() const
			{
				return m_internalTexture.isSmooth();
			}

			void SFMLTexture::setRepeated(bool repeated)
			{
				m_internalTexture.setRepeated(repeated);
			}

			bool SFMLTexture::isRepeated() const
			{
				return m_internalTexture.isRepeated();
			}
		}
	}
}