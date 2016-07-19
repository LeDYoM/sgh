#include "keymapping.hpp"
#include <lib/core/configuration.hpp>
#include <lib/core/appcontroller.hpp>

using namespace lib;

namespace zoper
{
	KeyMapping::KeyMapping(Object *const obj)
		: Object{ obj } {}

	KeyMapping::~KeyMapping() {}

	void KeyMapping::init()
	{
		auto configuration(service<Configuration>());
		std::array<KeyCode, TotalKeys> defaults = { KeyCode::Left, KeyCode::Right, KeyCode::Up, KeyCode::Down, KeyCode::Space, KeyCode::Escape };

		for (auto i = 0u; i < Direction::Total; ++i) {
			_keys[i] = static_cast<KeyCode>(configuration->get("Keyboard/key" + std::to_string(i), DataValue{ static_cast<s32>(defaults[i]) }).gets32());
		}

		_keys[Direction::Total] = static_cast<KeyCode>(configuration->get("Keyboard/key_launch" + std::to_string(Direction::Total), DataValue{ static_cast<s32>(defaults[Direction::Total]) }).gets32());
		_keys[Direction::Total + 1] = static_cast<KeyCode>(configuration->get("Keyboard/key_pause" + std::to_string(Direction::Total + 1), DataValue{ static_cast<s32>(defaults[Direction::Total + 1]) }).gets32());
	}

	KeyCode KeyMapping::getKey(Direction d) const
	{
		return _keys[d];
	}

	Direction KeyMapping::getDirectionFromKey(KeyCode k) const
	{
		for (u8 i = 0; i < Direction::Total; ++i)
		{
			if (_keys[i] == k)
			{
				return Direction(static_cast<Direction>(i));
			}
		}
		return Direction::Invalid;
	}

	KeyCode KeyMapping::getLaunchKey() const
	{
		return _keys[Direction::Total];
	}

	bool KeyMapping::isLaunchKey(const KeyCode key) const
	{
		return key == getLaunchKey();
	}

	KeyCode KeyMapping::getPauseKey() const
	{
		return _keys[Direction::Total+1];
	}

	bool KeyMapping::isPauseKey(const KeyCode key) const
	{
		return key == getPauseKey();
	}

	bool KeyMapping::setKey(u32 index, KeyCode key)
	{
		__ASSERT(index < TotalKeys, "Invalid index");

		for (u32 i = 0u; i < index; ++i)
		{
			if (_keys[i] == key)
			{
				return false;
			}
		}
		_keys[index] = key;
		return true;
	}

	void KeyMapping::apply()
	{
		for (auto i = 0u; i < Direction::Total; ++i)
		{
//			addConfigInt("key" + std::to_string(i), _keys[i],true);
		}

//		addConfigInt("key_launch" + std::to_string(Direction::Total), _keys[Direction::Total]);
//		addConfigInt("key_pause" + std::to_string(Direction::Total + 1), _keys[Direction::Total + 1]);
	}

}
