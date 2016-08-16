#ifndef LIB_MANAGERS_TEXTUREMANAGER_HPP
#define LIB_MANAGERS_TEXTUREMANAGER_HPP

#include "basemanager.hpp"

namespace lib
{
	namespace drivers 
	{
		namespace render
		{
			class Texture;
		}
	}
	namespace core
	{
		namespace managers
		{
			class TextureManager : public BaseManager<drivers::render::Texture>
			{
			public:
				using BaseClass = BaseManager<drivers::render::Texture, str>;
				using BaseManager::BaseManager;

				virtual ~TextureManager();

				virtual void load(const BaseClass::IndexType &index, void *, u32 size);
			};
		}
	}
}

#endif
