#include "texturemanager.hpp"
#include <lib/draw/texture.hpp>
#include <lib/core/appcontroller.hpp>
#include <lib/core/driver.hpp>
#include <lib/drivers/render/texture.hpp>

namespace lib
{
	namespace core
	{
		namespace managers
		{
			TextureManager::~TextureManager()
			{
			}

			void TextureManager::load(const BaseClass::IndexType &index, void *data, u32 size)
			{
				drivers::render::Texture *driverTexture(appController()->driver()->currentWindow()->newTexture());
				driverTexture->loadFromMemory(data, size);
				draw::Texture *texture = new draw::Texture(driverTexture);
			}

		}
	}
}

