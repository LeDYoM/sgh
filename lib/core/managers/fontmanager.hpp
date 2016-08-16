#ifndef LIB_MANAGERS_FONTMANAGER_HPP
#define LIB_MANAGERS_FONTMANAGER_HPP

#include "basemanager.hpp"

namespace lib
{
	namespace drivers
	{
		namespace render
		{
			class Font;
		}
	}

	namespace core
	{
		namespace managers
		{
			class FontManager : public BaseManager<drivers::render::Font>
			{
			public:
				using BaseClass = BaseManager<drivers::render::Font, str>;
				using BaseManager::BaseManager;

				virtual ~FontManager();

				virtual void load(const BaseClass::IndexType &index, void *, u32 size);
			};
		}
	}
}

#endif
