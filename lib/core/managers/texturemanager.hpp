#ifndef LIB_MANAGERS_TEXTUREMANAGER_HPP
#define LIB_MANAGERS_TEXTUREMANAGER_HPP

#include "basemanager.hpp"

namespace lib
{
	namespace core
	{
		namespace managers
		{
			class TextureManager : public BaseManager<int>
			{
			public:
				using BaseManager<int>::BaseManager;
				virtual ~TextureManager();

			};
		}
	}
}

#endif
