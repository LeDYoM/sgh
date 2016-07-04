#ifndef __LIB_IANIMATIONS_HPP__
#define __LIB_IANIMATIONS_HPP__

#include "animation.hpp"
#include "scenenode.hpp"
#include <lib/include/color.hpp>
#include <lib/include/properties.hpp>

namespace lib
{
	namespace draw
	{
		class ColorAnimation : public Animation<Color>
		{
		public:
			ColorAnimation(const str&name, NotifableProperty<Color> &color) : Animation{ name, color } {}
		};

		class PositionAnimation : public Animation<vector2df>
		{
		public:
			PositionAnimation(const str&name, NotifableProperty<vector2df> &position) : Animation{ name, position } {}
		};
	}
}

#endif
