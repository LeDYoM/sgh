#include "animatable.hpp"
#include <lib/core/log.hpp>

#include <algorithm>

namespace lib
{
	namespace draw
	{
		Animatable::Animatable()
		{
		}


		Animatable::~Animatable()
		{
			_animations.clear();
		}

		void Animatable::addAnimation(sptr<IAnimation> nanimation)
		{
			if (!_animations.empty())
			{
				auto elemFound = std::find_if(_animations.begin(), _animations.end(), [&nanimation](sptr<IAnimation> canimation)
				{
					return canimation->animationType() == nanimation->animationType();
				});

				if (elemFound != _animations.end())
				{
					LOG_DEBUG("Same animation type already in node");
					removeFromspVector(*elemFound, _animations);
				}
			}

			_animations.push_back(nanimation);
//			onAnimationStarted(nanimation, nanimation->node());
		}

		void Animatable::updateAnimations(const sptr<SceneNode> &node)
		{
			if (!_animations.empty())
			{
				for (auto &animation : _animations)
				{
					if (!animation->animate(node))
					{
//						onAnimationFinished(animation, animation->node());
						_animationsToDelete.push_back(animation);
					}
				}

				if (!_animationsToDelete.empty())
				{
					for (auto animation : _animationsToDelete)
					{
						removeFromspVector(animation, _animations);
					}
					_animationsToDelete.clear();
				}
			}
		}

		/*
		void Animatable::onAnimationStarted(sptr<IAnimation> anim, sptr<RenderNode> node)
		{

		}

		void Animatable::onAnimationFinished(sptr<IAnimation> anim, sptr<RenderNode> node)
		{

		}
		*/
	}
}
