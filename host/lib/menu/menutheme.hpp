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
			MenuTheme(const draw::Color &nsc, const draw::Color &sc, const str&defaultFontId);
			virtual ~MenuTheme();

			Property<draw::Color,MenuTheme> notSelectedColor;
			Property<draw::Color, MenuTheme> selectedColor;

			sptr<core::Resource> defaultFont() const;
		private:
			void aquireFont(const str&fid);
			sptr<core::Resource> default_font;

		};
	}
}
#endif
