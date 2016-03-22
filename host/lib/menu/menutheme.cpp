#include "menutheme.hpp"
#include <lib/core/resourcemanager.hpp>

namespace lib
{
	namespace menu
	{
		MenuTheme::MenuTheme(const draw::Color &nsc, const draw::Color &sc, const str&defaultFontId, const u32 normalTextCharacterSize)
			: m_notSelectedColor{ nsc }, m_selectedColor{ sc }, m_defaultFontId(defaultFontId), m_normalTextCharacterSize{ normalTextCharacterSize }
		{
		}

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

		bool MenuTheme::init()
		{
			aquireFont(m_defaultFontId);
			return true;
		}

	}
}
