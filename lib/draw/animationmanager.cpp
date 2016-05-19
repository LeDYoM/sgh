#include "animationmanager.hpp"
#include <lib/core/log.hpp>

#include <algorithm>

namespace lib
{
	namespace draw
	{
		namespace anim
		{
			AnimationManager::AnimationManager()
			{
			}


			AnimationManager::~AnimationManager()
			{
				m_animations.clear();
			}


			void AnimationManager::onAnimationStarted(sptr<IAnimation> anim, sptr<RenderNode> node)
			{

			}

			void AnimationManager::onAnimationFinished(sptr<IAnimation> anim, sptr<RenderNode> node)
			{

			}
		}
	}
}
