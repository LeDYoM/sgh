#ifndef __KEYMAPPING_HPP__
#define __KEYMAPPING_HPP__

#include <lib/include/key.hpp>
#include <lib/core/obj.hpp>
#include "direction.hpp"
#include <array>

namespace zoper
{
	class KeyMapping : public lib::Object
	{
	public:
		KeyMapping();
		virtual ~KeyMapping();

		void init();

		static const lib::u32 TotalKeys = Direction::Total + 2;

		lib::KeyCode getKey(Direction d) const;
		Direction getDirectionFromKey(const lib::KeyCode k) const;
		lib::KeyCode getLaunchKey() const;
		bool isLaunchKey(const lib::KeyCode key) const;
		lib::KeyCode getPauseKey() const;
		bool isPauseKey(const lib::KeyCode key) const;

		bool setKey(lib::u32 index, const lib::KeyCode key);
		void apply();
	private:
		std::array<lib::KeyCode, KeyMapping::TotalKeys> _keys;
	};
}

#endif
