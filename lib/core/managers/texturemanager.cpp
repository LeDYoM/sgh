#include "texturemanager.hpp"
#include <lib/draw/texture.hpp>
#include <lib/core/appcontroller.hpp>
#include <lib/core/driver.hpp>
#include <lib/drivers/render/texture.hpp>
#include <lib/core/compileconfig.hpp>

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
				auto driverTexture(appController()->driver()->currentWindow()->newTexture());
				driverTexture->loadFromMemory(data, size);
				auto texture = sptr<draw::Texture>(new draw::Texture(driverTexture));
				auto ok (set(index, texture));
				__ASSERT(ok,"Cannot add texture");
			}

		}
	}
}

