#include "menutheme.hpp"
#include <lib/core/resourcemanager.hpp>

namespace lib
{
	namespace menu
	{
		MenuTheme::MenuTheme(const draw::Color &nsc, const draw::Color &sc, const str&defaultFontId,
			const u32 notSelectedTextSize, const u32 selectedTextSize)
			: m_notSelectedColor{ nsc }, m_selectedColor{ sc }, m_defaultFontId( defaultFontId ),
			m_notSelectedTextSize{ notSelectedTextSize }, m_selectedTextSize{ selectedTextSize }
		{}

		MenuTheme::~MenuTheme()
		{
		}

		bool MenuTheme::init()
		{
			aquireFont(m_defaultFontId);
			return true;
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
