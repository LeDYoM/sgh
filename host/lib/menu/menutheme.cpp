#include "menutheme.hpp"
#include <lib/core/resourcemanager.hpp>

namespace lib
{
	namespace menu
	{
		MenuTheme::MenuTheme(const draw::Color &nsc, const draw::Color &sc, const str&defaultFontId)
			: notSelectedColor{ nsc }, selectedColor{ sc }
		{}

		MenuTheme::~MenuTheme()
		{

		}

		void MenuTheme::aquireFont(const str&fid)
		{
			default_font = parent()->resourceManager()->getResource(fid);
		}

		sptr<core::Resource> MenuTheme::defaultFont() const
		{
			return default_font;
		}

	}
}
