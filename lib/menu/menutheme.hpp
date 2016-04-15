#ifndef LIB__MENU_MENUTHEME_HPP
#define LIB__MENU_MENUTHEME_HPP

#include <lib/draw/iparentable.hpp>
#include <lib/include/color.hpp>
#include "menumanager.hpp"
#include <lib/include/properties.hpp>

namespace lib
{
	class Resource;
	namespace menu
	{
		class MenuTheme : public draw::IParentable<MenuManager>
		{
		public:
			MenuTheme(const draw::Color &nsc, const draw::Color &sc, const str&defaultFontId,
				const u32 notSelectedTextSize, const u32 selectedTextSize);
			virtual ~MenuTheme();

			MenuTheme &operator=(const MenuTheme&) = delete;

			virtual bool init();
			sptr<Resource> defaultFont() const;
			const draw::Color &notSelectedColor() const { return m_notSelectedColor; }
			const draw::Color &selectedColor() const { return m_selectedColor; }
			const u32 notSelectedTextSize() const { return m_notSelectedTextSize; }
			const u32 selectedTextSize() const { return m_selectedTextSize; }

		private:
			draw::Color m_notSelectedColor;
			draw::Color m_selectedColor;
			const u32 m_notSelectedTextSize;
			const u32 m_selectedTextSize;
			str m_defaultFontId;
			void aquireFont(const str&fid);
			sptr<Resource> default_font;
		};
	}
}
#endif