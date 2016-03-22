#ifndef LIB__MENU_MENUTHEME_HPP
#define LIB__MENU_MENUTHEME_HPP

#include <lib/draw/iparentable.hpp>
#include <lib/include/color.hpp>
#include "menumanager.hpp"
#include <lib/include/properties.hpp>

namespace lib
{
	namespace core
	{
		class Resource;
	}
	namespace menu
	{
		class MenuTheme : public draw::IParentable<MenuManager>
		{
		public:
			MenuTheme(const draw::Color &nsc, const draw::Color &sc, const str&defaultFontId, const u32 normalTextCharacterSize);
			virtual ~MenuTheme();

			virtual bool init();

			u32 normalTextCharacterSize() const { return m_normalTextCharacterSize; }
			const draw::Color &notSelectedColor() const { return m_notSelectedColor; }
			const draw::Color &selectedColor() const { return m_notSelectedColor; }
			sptr<core::Resource> defaultFont() const;
			const u32 normalCharacterSize() const { return m_normalTextCharacterSize; }
		private:
			void aquireFont(const str&fid);
			sptr<core::Resource> default_font;
			str m_defaultFontId;
			u32 m_normalTextCharacterSize;
			draw::Color m_notSelectedColor;
			draw::Color m_selectedColor;
		};
	}
}
#endif
