#ifndef LIB_MENU_SIMPLEMENU_HPP
#define LIB_MENU_SIMPLEMENU_HPP

#include <lib/include/types.hpp>
#include <lib/draw/RenderNode.hpp>
#include "imenucontrol.hpp"
#include "menudescriptors.hpp"
#include <vector>
#include <functional>

namespace lib
{
	namespace core
	{
		class Resource;
	}
	namespace menu
	{
		class OptionDescriptor;
		class MenuStep;
		class SimpleMenu : public IMenuControl
		{
		public:
			SimpleMenu(const str &name, MenuManager *const parentManager, const draw::Alignment alignment,
				std::function<void(const u32, SimpleMenu &self)> onSelected);
			virtual ~SimpleMenu();

		private:
			virtual void onKeyPressed(lib::input::Key key) override;
			virtual void onKeyReleased(lib::input::Key key) override;

			void cursorSelectItem(u32 nodeIndex);
			void goDown();
			void goUp();
			void goLeft();
			void goRight();

			vector2df descriptorCursorSize;
			u32 _cursorItemSelected{ 0 };
			VecSPtr<draw::NodeText> _labelData;
			sptr<draw::NodeShape> _cursor;
			std::function<void(const u32, SimpleMenu &self)> _onSelected;
		};
	}
}

#endif
