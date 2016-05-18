#ifndef __LIB_POSITIONANIMATION_HPP__
#define __LIB_POSITIONANIMATION_HPP__

#include "ianimation.hpp"
#include <lib/include/types.hpp>

namespace lib
{
	namespace draw
	{
		namespace anim
		{
			class PositionAnimation : public IValueAnimation<vector2df>
			{
			public:
				PositionAnimation(const s32 duration, const vector2df &startPosition, const vector2df &endPosition);
				static sptr<PositionAnimation> create(const s32 duration, const vector2df &startPosition, const vector2df &endPosition);
				virtual ~PositionAnimation();
				virtual bool animate(SceneNode *const) override;
				virtual const std::string animationType() const { return "PositionAnimation"; }
			};
		}
	}
}

#endif
