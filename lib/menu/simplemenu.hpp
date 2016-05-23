#ifndef LIB_MENU_SIMPLEMENU_HPP
#define LIB_MENU_SIMPLEMENU_HPP

#include <lib/include/types.hpp>
#include <lib/draw/rendernode.hpp>
#include <lib/draw/nodetext.hpp>
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
	namespace draw
	{
		class TextGroup;
	}
	namespace menu
	{
		class SimpleMenu : public IMenuControl
		{
		public:
			SimpleMenu(const str &name, const draw::Alignment alignment,
				std::function<void(const u32, SimpleMenu &self)> onSelected);
			virtual ~SimpleMenu();

			virtual bool init() override;
			void addOption(const str &text);
		private:
			virtual void onKeyPressed(lib::Key key) override;
			virtual void onKeyReleased(lib::Key key) override;

			void cursorSelectItem(u32 nodeIndex);
			void goDown();
			void goUp();
			void goLeft();
			void goRight();

			u32 _cursorItemSelected{ 0 };
			VecSPtr<draw::NodeText> _labelData;
			std::function<void(const u32, SimpleMenu &self)> _onSelected;
			sptr<draw::TextGroup> m_textGroup;
		};
	}
}

#endif
