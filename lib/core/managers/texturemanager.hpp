#ifndef LIB_MANAGERS_TEXTUREMANAGER_HPP
#define LIB_MANAGERS_TEXTUREMANAGER_HPP

#include "basemanager.hpp"

namespace lib
{
	namespace draw
	{
		class Texture;
	}
	namespace core
	{
		namespace managers
		{
			class TextureManager : public BaseManager<draw::Texture>
			{
			public:
				using BaseClass = BaseManager<draw::Texture, str>;
				using BaseManager::BaseManager;

				virtual ~TextureManager();

				virtual void load(const BaseClass::IndexType &index, void *, u32 size);
			};
		}
	}
}

#endif
