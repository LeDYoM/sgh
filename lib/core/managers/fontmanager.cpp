#include "fontmanager.hpp"
#include <lib/draw/font.hpp>
#include <lib/core/appcontroller.hpp>
#include <lib/core/driver.hpp>
#include <lib/drivers/render/font.hpp>

namespace lib
{
	namespace core
	{
		namespace managers
		{
			FontManager::~FontManager()
			{
			}

			void FontManager::load(const BaseClass::IndexType &index, void *data, u32 size)
			{
				auto *driverFont(appController()->driver()->currentWindow()->newFont());
				driverFont->loadFromMemory(data, size);
				draw::Font *texture = new draw::Font(driverTexture);
			}

		}
	}
}

