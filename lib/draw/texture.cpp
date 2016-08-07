#include "texture.hpp"
#include <lib/drivers/render/texture.hpp>

namespace lib
{
	namespace draw
	{
		Texture::Texture(drivers::render::Texture *tHandle)
			: m_driverTexture{ tHandle } {}

		Texture::~Texture()
		{
		}
	}
}
