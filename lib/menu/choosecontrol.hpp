#ifndef __LIB_CHOOSECONTROL_HPP__
#define __LIB_CHOOSECONTROL_HPP__

#include <lib/include/types.hpp>
#include <lib/draw/rendernode.hpp>
#include <lib/draw/nodetext.hpp>
#include "imenucontrol.hpp"
#include "menudescriptors.hpp"
#include <vector>
#include <functional>

namespace lib
{
	class Resource;
	namespace menu
	{
		class OptionDescriptor;
		class MenuStep;
		class ChooseControl : public IMenuControl
		{
		public:
			ChooseControl(const std::string &name, sptr<Resource> font,
				const lib::draw::Color &textColor, const lib::draw::Color &selectedTextColor,
				const draw::Alignment alignment,
				u32 chSize, float incY, std::function<void(const u32,ChooseControl &self)> onSelected,
				sptr<CursorDescriptor> cursorDescriptor, 
				const std::vector<sptr<OptionDescriptor>> labels);
			virtual ~ChooseControl();

			u32 getSelectedSubLabel(u32 index) const;
			void setSelectedSubLabel(u32 index, u32 subIndex);
		private:
			virtual void onKeyPressed(lib::Key key) override;
			virtual void onKeyReleased(lib::Key key) override;

			void updateSubLabelText(const u32 index);
			void cursorSelectItem(u32 nodeIndex);
			void goDown();
			void goUp();
			void goLeft();
			void goRight();

			vector2df descriptorCursorSize;
			u32 _cursorItemSelected{ 0 };
			lib::draw::Color _textColor;
			lib::draw::Color _selectedTextColor;

			struct LabelData
			{
				std::vector<std::string> textSubLabel;
				sptr<draw::NodeText> subLabel{ nullptr };
				sptr<draw::NodeText> label{ nullptr };
				u32 selectedSublabel{ 0 };
				LabelData(const std::vector<std::string> textSubLevel_, sptr<draw::NodeText> subLabel_,
					sptr<draw::NodeText> label_, const u32 selectedSubLabel_)
					: textSubLabel(textSubLevel_), subLabel{ subLabel_ }, label{ label_ }, selectedSublabel{ selectedSubLabel_ } {}
			};
			std::vector<LabelData> _labelData;
			sptr<draw::NodeShape> _cursor;
			std::function<void(const u32, ChooseControl &self)> _onSelected;
		};
	}
}

#endif
