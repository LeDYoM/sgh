#include "ianimation.hpp"
#include "scenenode.hpp"

namespace lib
{
	namespace draw
	{
		IAnimation::IAnimation(const u32 duration)
		: _duration{ duration }
		{
			_clock.restart();
		}

		bool IAnimation::animate(SceneNode*const)
		{
			currentTime = _clock.getElapsedTime().asMilliSeconds();
			if (currentTime > _duration) {
				_delta = 1.0f;
				return false;
			}
			_delta = (static_cast<f32>(currentTime) / _duration);
			return true;
		}

		IAnimation::~IAnimation()
		{

		}
	}
}
