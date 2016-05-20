#include "choosecontrol.hpp"
#include "menudescriptors.hpp"
#include <lib/core/resource.hpp>
#include <lib/draw/nodeshape.hpp>
#include <lib/draw/nodetext.hpp>
#include <lib/include/key.hpp>
#include <lib/draw/animations.hpp>

namespace lib
{
	namespace menu
	{
		ChooseControl::ChooseControl(const std::string &name, sptr<Resource> font, 
			const lib::draw::Color &textColor, const lib::draw::Color &selectedTextColor,
			const draw::Alignment alignment,
			u32 chSize,float incY,
			std::function<void(const u32, ChooseControl &self)> onSelected,
			sptr<CursorDescriptor> cursorDescriptor, 
			const std::vector<sptr<OptionDescriptor>> labels)
			: IMenuControl{ name }, _textColor{ textColor }, _selectedTextColor{ selectedTextColor }, _onSelected {onSelected}
		{
			descriptorCursorSize = cursorDescriptor->_size;
			_cursor = createShape("cursor");
			_cursor->setPointCount(cursorDescriptor->_nVertex);
			_cursor->setColor(cursorDescriptor->_color);
			_cursor->setSize(descriptorCursorSize);

			u32 count{ 0 };
			vector2df currentPos{ 0.0f, 0.0f };
			for (const auto label : labels)
			{
				auto text = createText("name" + count);
				text->setFont(*(font->getAsFont()));
				text->setCharacterSize(chSize);
				text->setString(labels[count]->_text);
				text->setColor(textColor);
				text->setPositionX(0, alignment);
				text->setPositionY(currentPos.y);

				sptr<draw::NodeText> subtext{ nullptr };
				if (labels[count]->_subOptionsLabels.size()>0)
				{
					subtext = createText("sub_name" + count);
					subtext->setFont(*(font->getAsFont()));
					subtext->setCharacterSize(chSize);
					subtext->setString(labels[count]->_subOptionsLabels[labels[count]->_startValueIndex]);
					subtext->setColor(textColor);
					subtext->setPositionX(1800, lib::draw::Alignment::Right);
					subtext->setPositionY(currentPos.y);
				}

				currentPos.y += (chSize + incY);
				_labelData.push_back(LabelData(labels[count]->_subOptionsLabels,subtext,text, labels[count]->_startValueIndex));
				++count;
			}

			cursorSelectItem(0);
		}


		ChooseControl::~ChooseControl()
		{
			_labelData.clear();
			_cursor = nullptr;
		}

		lib::u32 ChooseControl::getSelectedSubLabel(u32 index) const
		{
			__ASSERT(index < _labelData.size(), "Invalid index");
			return _labelData[index].selectedSublabel;
		}

		void ChooseControl::setSelectedSubLabel(u32 index, u32 subIndex)
		{
			__ASSERT(index < _labelData.size(), "Invalid index");
			_labelData[index].selectedSublabel = subIndex;
			updateSubLabelText(index);
		}

		void ChooseControl::onKeyPressed(lib::Key key)
		{
			using namespace lib;
			if (key.kCode == KeyCode::Down || key.kCode == KeyCode::Numpad2)
			{
				goDown();
			}
			else if (key.kCode == KeyCode::Up || key.kCode == KeyCode::Numpad8)
			{
				goUp();
			}
			else if (key.kCode == KeyCode::Return || key.kCode == KeyCode::Space)
			{
				if (_onSelected)
				{
					_onSelected(_cursorItemSelected,*this);
				}
			}
			else if (_labelData[_cursorItemSelected].textSubLabel.size() > 0)
			{
				if (key.kCode == KeyCode::Left || key.kCode == KeyCode::Numpad4)
				{
					goLeft();
				}
				else if (key.kCode == KeyCode::Right || key.kCode == KeyCode::Numpad6)
				{
					goRight();
				}
			}
		}

		void ChooseControl::onKeyReleased(lib::Key key)
		{
			key;
		}

		void ChooseControl::updateSubLabelText(const u32 index)
		{
			_labelData[index].subLabel->setString(_labelData[index].textSubLabel[_labelData[index].selectedSublabel]);
			_labelData[index].subLabel->setPositionX(1800.0f, lib::draw::Alignment::Right);
		}

		void ChooseControl::cursorSelectItem(u32 nodeIndex)
		{
			__ASSERT(nodeIndex < _labelData.size(), "Invalid select index for cursor");

			_labelData[_cursorItemSelected].label->setColor(_textColor);
			if (_labelData[_cursorItemSelected].subLabel)
			{
				_labelData[_cursorItemSelected].subLabel->setColor(_textColor);
			}

			_cursorItemSelected = nodeIndex;
			auto selectedText = _labelData[nodeIndex].label;

			selectedText->setColor(_selectedTextColor);
			if (_labelData[_cursorItemSelected].subLabel)
			{
				_labelData[_cursorItemSelected].subLabel->setColor(_selectedTextColor);
			}

			_cursor->setRotation(90);
			
			lib::sptr<lib::draw::PositionAnimation> pa = lib::sptr<lib::draw::PositionAnimation>(new lib::draw::PositionAnimation("myPositionAnimationId"));
			pa->setDuration(120);
			pa->setStartValue(_cursor->position());
			pa->setEndValue(vector2df{ selectedText->position().x - descriptorCursorSize.x, selectedText->position().y });
			_cursor->addAnimation(pa);
		}

		void ChooseControl::goDown()
		{
			if (_cursorItemSelected < (_labelData.size() - 1)) {
				cursorSelectItem(_cursorItemSelected + 1);
			}
			else {
				cursorSelectItem(0);
			}
		}

		void ChooseControl::goUp()
		{
			if (_cursorItemSelected > 0) {
				cursorSelectItem(_cursorItemSelected - 1);
			}
			else {
				cursorSelectItem(_labelData.size()-1);
			}
		}

		void ChooseControl::goLeft()
		{
			auto index(_labelData[_cursorItemSelected].selectedSublabel);

			if (_labelData[_cursorItemSelected].textSubLabel.size() > 0)
			{
				if (index < 1) {
					index = _labelData[_cursorItemSelected].textSubLabel.size()-1;
				}
				else {
					--index;
				}
				_labelData[_cursorItemSelected].selectedSublabel = index;
				updateSubLabelText(_cursorItemSelected);
			}
		}

		void ChooseControl::goRight()
		{
			auto index (_labelData[_cursorItemSelected].selectedSublabel);

			if (_labelData[_cursorItemSelected].textSubLabel.size() > 0)
			{
				if (index >= _labelData[_cursorItemSelected].textSubLabel.size() - 1) {
					index = 0;
				}
				else {
					++index;
				}
				_labelData[_cursorItemSelected].selectedSublabel = index;
				updateSubLabelText(_cursorItemSelected);

			}
		}
	}
}
