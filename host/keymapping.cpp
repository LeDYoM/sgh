#include "keymapping.hpp"

namespace zoper
{
	KeyMapping::KeyMapping()
	{
//		std::array<lib::input::KeyCode, TotalKeys> defaults{ lib::input::KeyCode::Left, lib::input::KeyCode::Right, lib::input::KeyCode::Up, lib::input::KeyCode::Down, lib::input::KeyCode::Space, lib::input::KeyCode::Escape };

		for (auto i = 0u; i < Direction::Total; ++i)
		{
//			_keys[i] = static_cast<lib::input::KeyCode>(addConfigInt("key" + std::to_string(i), defaults[i]));
		}

//		_keys[Direction::Total] = static_cast<lib::input::KeyCode>(addConfigInt("key_launch" + std::to_string(Direction::Total), defaults[Direction::Total]));
//		_keys[Direction::Total + 1] = static_cast<lib::input::KeyCode>(addConfigInt("key_pause" + std::to_string(Direction::Total + 1), defaults[Direction::Total + 1]));
	}

	KeyMapping::~KeyMapping()
	{
	}

	lib::KeyCode KeyMapping::getKey(Direction d) const
	{
		return _keys[d];
	}
	Direction KeyMapping::getDirectionFromKey(lib::KeyCode k) const
	{
		for (lib::u8 i = 0; i < Direction::Total; ++i)
		{
			if (_keys[i] == k)
			{
				return Direction(static_cast<Direction>(i));
			}
		}
		return Direction::Invalid;
	}

	lib::KeyCode KeyMapping::getLaunchKey() const
	{
		return _keys[Direction::Total];
	}

	bool KeyMapping::isLaunchKey(const lib::KeyCode key) const
	{
		return key == getLaunchKey();
	}

	lib::KeyCode KeyMapping::getPauseKey() const
	{
		return _keys[Direction::Total+1];
	}

	bool KeyMapping::isPauseKey(const lib::KeyCode key) const
	{
		return key == getPauseKey();
	}

	bool KeyMapping::setKey(lib::u32 index, lib::KeyCode key)
	{
		__ASSERT(index < TotalKeys, "Invalid index");

		for (lib::u32 i = 0u; i < index; ++i)
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
