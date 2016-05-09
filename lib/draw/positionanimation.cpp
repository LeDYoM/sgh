#include "positionanimation.hpp"
#include "rendernode.hpp"

namespace lib
{
	namespace draw
	{
		namespace anim
		{
			PositionAnimation::PositionAnimation(const s32 duration, const vector2df &startPosition, const vector2df &endPosition)
				: IValueAnimation{ duration, startPosition, endPosition }
			{
			}


			PositionAnimation::~PositionAnimation()
			{
			}

			bool PositionAnimation::animate(sptr<SceneNode> &node)
			{
				bool result = IAnimation::animate(node);
				vector2df deltaPosition{ _endValue - _startValue };
				vector2df finalPosition{ _startValue + (deltaPosition*_delta) };
				node->setPosition(finalPosition);
				return result;
			}

			sptr<PositionAnimation> PositionAnimation::create(const s32 duration, const vector2df &startPosition, const vector2df &endPosition)
			{
				auto animation = std::make_shared<PositionAnimation>(duration, startPosition, endPosition);
				return animation;
			}
		}
	}
}
