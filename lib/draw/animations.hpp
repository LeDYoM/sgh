#ifndef __LIB_IANIMATIONS_HPP__
#define __LIB_IANIMATIONS_HPP__

#include "animation.hpp"
#include "scenenode.hpp"
#include <lib/include/color.hpp>


namespace lib
{
	namespace draw
	{
		class ColorAnimation : public Animation<Color, &SceneNode::setColor>
		{
		public:
			ColorAnimation(const str&name) : Animation{ name } {}
		};

		class PositionAnimation : public Animation<vector2df, &SceneNode::setPosition>
		{
		public:
			PositionAnimation(const str&name) : Animation{ name } {}
		};
	}
}

#endif
