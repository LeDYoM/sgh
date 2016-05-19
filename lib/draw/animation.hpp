#ifndef __LIB_IANIMATION_HPP__
#define __LIB_IANIMATION_HPP__

#include "animation.hpp"
#include <lib/include/color.hpp>

#include <functional>

namespace lib
{
	namespace draw
	{
		class ColorAnimation : public Animation<Color, &SceneNode::setColor>
		{
			using ty = Animation<Color, &SceneNode::setColor>;
			using ty::Animation;
		};
	}
}

#endif
