#include "texture.hpp"
#include <lib/drivers/render/texture.hpp>

namespace lib
{
	namespace draw
	{
		Texture::Texture(uptr<drivers::render::Texture>&tHandle)
			: m_driverTexture{ std::move(tHandle) } {}

		Texture::~Texture()
		{
			m_driverTexture.reset(nullptr);
		}
	}
}
