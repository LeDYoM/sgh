#include "texturemanager.hpp"
#include <lib/draw/texture.hpp>
#include <lib/core/appcontroller.hpp>
#include <lib/core/driver.hpp>

namespace lib
{
	namespace core
	{
		namespace managers
		{
			TextureManager::~TextureManager()
			{
			}

			void TextureManager::load(const BaseClass::IndexType &index, void *data)
			{
				drivers::render::Texture *driverTexture (appController()->driver()->currentWindow()->loadTextureFromMemory(data));
				draw::Texture *texture = new draw::Texture(driverTexture);
			}

		}
	}
}

