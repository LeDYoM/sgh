#ifndef __KEYMAPPING_HPP__
#define __KEYMAPPING_HPP__

#include <lib/core/configuration.hpp>
#include <lib/include/key.hpp>
#include "direction.hpp"
#include <array>

namespace zoper
{
	class KeyMapping : public lib::Configuration
	{
	public:
		KeyMapping();
		virtual ~KeyMapping();

		static const lib::u32 TotalKeys = Direction::Total + 2;

		lib::input::KeyCode getKey(Direction d) const;
		Direction getDirectionFromKey(const lib::input::KeyCode k) const;
		lib::input::KeyCode getLaunchKey() const;
		bool isLaunchKey(const lib::input::KeyCode key) const;
		lib::input::KeyCode getPauseKey() const;
		bool isPauseKey(const lib::input::KeyCode key) const;

		bool setKey(lib::u32 index, const lib::input::KeyCode key);
		void apply();
	private:
		std::array<lib::input::KeyCode, KeyMapping::TotalKeys> _keys;
	};
}

#endif
