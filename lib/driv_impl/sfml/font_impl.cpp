#include "font_impl.hpp"

namespace lib
{
	namespace drivers
	{
		namespace render
		{
			SFMLFont::SFMLFont() : m_internalFont{}
			{
			}

			SFMLFont::~SFMLFont()
			{
			}

			bool SFMLFont::loadFromFile(const str & filename)
			{
				return m_internalFont.loadFromFile(filename);
			}

			bool SFMLFont::loadFromMemory(const void * data, std::size_t size)
			{
				return m_internalFont.loadFromMemory(data, size);
			}
		}
	}
}