#include "keyredefinitionmenu.hpp"
#include <lib/menu/menumanager.hpp>
#include <lib/menu/choosecontrol.hpp>
#include <lib/menu/menudescriptors.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/resource.hpp>
#include <lib/draw/rendernode.hpp>
#include <lib/draw/nodetext.hpp>

#include "common.hpp"

namespace zoper
{
	namespace zmenu
	{
		KeyRedefinitionMenu::KeyRedefinitionMenu()
			: lib::menu::MenuStep{ "KeyRedefinitionMenu" }
		{
		}


		KeyRedefinitionMenu::~KeyRedefinitionMenu()
		{
		}

		bool KeyRedefinitionMenu::init()
		{
			bool result = MenuStep::init();
			if (!result)
			{
				return false;
			}

			_nextKeyText = createText("pressKey");

			_nextKeyText->setFont(*menuManager()->resourceManager()->getResource("game_menu.mainFont")->getAsFont());
			_nextKeyText->setCharacterSize(90);
			_nextKeyText->setString(" ");
			_nextKeyText->setColor(lib::draw::Color::Blue());
			_nextKeyText->setPosition({ 1000.0f, 1000.0f });
			_nextKeyText->setAlignment(lib::draw::NodeText::Alignment::Center);
			_indexKey = 0;
			setTextForKey();
			return true;
		}

		void KeyRedefinitionMenu::onKeyPressed(lib::input::Key key)
		{
			lib::menu::MenuStep::onKeyPressed(key);
			if (_keyMapping.setKey(_indexKey, key.kCode))
			{
				++_indexKey;
				setTextForKey();
			}
		}

		void KeyRedefinitionMenu::onKeyReleased(lib::input::Key key)
		{
			lib::menu::MenuStep::onKeyReleased(key);
		}

		void KeyRedefinitionMenu::setTextForKey()
		{
			if (_indexKey >= KeyMapping::TotalKeys)
			{
				_indexKey = 0;
				_keyMapping.apply();
				menuManager()->changeStep("OptionsMenu");
			}
			else
			{
				_nextKeyText->setString("Press key for "+getKeyNameStr(_indexKey));
				_nextKeyText->setPosition(lib::vector2df{ 1000.0, 1000.0 });
				_nextKeyText->setAlignment(lib::draw::NodeText::Alignment::Center);
			}
		}

		const std::string KeyRedefinitionMenu::getKeyNameStr(const lib::u32 index) const
		{
			switch (index)
			{
			case 0:
				return "Left";
				break;
			case 1:
				return "Right";
				break;
			case 2:
				return "Up";
				break;
			case 3:
				return "Down";
				break;
			case 4:
				return "Launch";
				break;
			default:
			case 5:
				return "Pause";
				break;
			}
		}
	}
}
