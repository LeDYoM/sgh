#include "simplemenu.hpp"
#include <lib/menu/menumanager.hpp>
#include <lib/menu/menutheme.hpp>
#include <lib/core/resource.hpp>
#include <lib/draw/positionanimation.hpp>
#include <lib/draw/nodeshape.hpp>
#include <lib/draw/nodetext.hpp>
#include <lib/include/key.hpp>
#include <lib/draw/textgroup.hpp>

namespace lib
{
	namespace menu
	{
		SimpleMenu::SimpleMenu(const str &name, const draw::Alignment alignment,
			std::function<void(const u32, SimpleMenu &self)> onSelected)
			: IMenuControl{ name  }, _onSelected {onSelected}, m_textGroup{ }
		{
			alignment;
		}

		SimpleMenu::~SimpleMenu()
		{
			_labelData.clear();
		}

		bool SimpleMenu::init()
		{
			if (IMenuControl::init())
			{
				m_textGroup = createNewRenderGroupOf<draw::TextGroup>(name()+"_textGroup");
				m_textGroup->setFont(menuManager()->menuTheme()->defaultFont());
				m_textGroup->setCharacterSize(menuManager()->menuTheme()->notSelectedTextSize());
				m_textGroup->setColor(menuManager()->menuTheme()->notSelectedColor());
			}
			return false;
		}

		void SimpleMenu::addOption(const str &text)
		{
			m_textGroup->addText(text);
		}

		void SimpleMenu::onKeyPressed(lib::Key key)
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
		}

		void SimpleMenu::onKeyReleased(lib::Key key)
		{
			key;
		}

		void SimpleMenu::cursorSelectItem(u32 nodeIndex)
		{
			nodeIndex;
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
