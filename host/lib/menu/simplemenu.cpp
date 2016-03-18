#include "simplemenu.hpp"
#include <lib/core/resource.hpp>
#include <lib/draw/positionanimation.hpp>
#include <lib/draw/nodeshape.hpp>
#include <lib/draw/nodetext.hpp>
#include <lib/include/key.hpp>

namespace lib
{
	namespace menu
	{
		SimpleMenu::SimpleMenu(const str &name, MenuManager *const parentManager, const draw::Alignment alignment,
			std::function<void(const u32, SimpleMenu &self)> onSelected)
			: IMenuControl{ name, parentManager }, _onSelected {onSelected}
		{
			/*
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
			*/
		}


		SimpleMenu::~SimpleMenu()
		{
			_labelData.clear();
			_cursor = nullptr;
		}

		void SimpleMenu::onKeyPressed(lib::input::Key key)
		{
			if (key.kCode == lib::input::KeyCode::Down || key.kCode == lib::input::KeyCode::Numpad2)
			{
				goDown();
			}
			else if (key.kCode == lib::input::KeyCode::Up || key.kCode == lib::input::KeyCode::Numpad8)
			{
				goUp();
			}
			else if (key.kCode == lib::input::KeyCode::Return || key.kCode == lib::input::KeyCode::Space)
			{
				if (_onSelected)
				{
					_onSelected(_cursorItemSelected,*this);
				}
			}
		}

		void SimpleMenu::onKeyReleased(lib::input::Key key)
		{
			key;
		}

		void SimpleMenu::cursorSelectItem(u32 nodeIndex)
		{
			/*
			__ASSERT(nodeIndex < _labelData.size(), "Invalid select index for cursor");

			_labelData[_cursorItemSelected]->setColor(_textColor);

			_cursorItemSelected = nodeIndex;
			_labelData[nodeIndex]->setColor(_selectedTextColor);

			_cursor->setRotation(90);
			
			addAnimation(draw::anim::PositionAnimation::create(120, _cursor, 
				vector2df{ selectedText->position().x - descriptorCursorSize.x, selectedText->position().y }));
				*/
		}

		void SimpleMenu::goDown()
		{
			if (_cursorItemSelected < (_labelData.size() - 1))
			{
				cursorSelectItem(_cursorItemSelected + 1);
			}
			else
			{
				cursorSelectItem(0);
			}
		}

		void SimpleMenu::goUp()
		{
			if (_cursorItemSelected > 0)
			{
				cursorSelectItem(_cursorItemSelected - 1);
			}
			else
			{
				cursorSelectItem(_labelData.size()-1);
			}
		}

		void SimpleMenu::goLeft()
		{
			/*
			auto index = _labelData[_cursorItemSelected].selectedSublabel;

			if (_labelData[_cursorItemSelected].textSubLabel.size() > 0)
			{
				if (index < 1)
				{
					index = _labelData[_cursorItemSelected].textSubLabel.size()-1;
				}
				else
				{
					--index;
				}
				_labelData[_cursorItemSelected].selectedSublabel = index;
				updateSubLabelText(_cursorItemSelected);
			}
			*/
		}

		void SimpleMenu::goRight()
		{
			/*
			auto index = _labelData[_cursorItemSelected].selectedSublabel;

			if (_labelData[_cursorItemSelected].textSubLabel.size() > 0)
			{
				if (index >= _labelData[_cursorItemSelected].textSubLabel.size() - 1)
				{
					index = 0;
				}
				else
				{
					++index;
				}
				_labelData[_cursorItemSelected].selectedSublabel = index;
				updateSubLabelText(_cursorItemSelected);
			}
			*/
		}
	}
}
