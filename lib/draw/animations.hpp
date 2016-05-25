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
		class ColorAnimation : public AnimationTemp<Color>
		{
		public:
			ColorAnimation(const str&name, Property<Color> &color) : AnimationTemp( name, color) {}
		};

		class PositionAnimation : public Animation<vector2df, &SceneNode::setPosition>
		{
		public:
			PositionAnimation(const str&name) : Animation{ name } {}
		};
	}
}

#endif
