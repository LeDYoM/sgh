#include "scenenode.hpp"
#include "rendergroup.hpp"

namespace lib
{
	namespace draw
	{
		SceneNode::SceneNode(const str &name) : m_name( name ) {}
		
		bool SceneNode::init()
		{
			setProvider(parent());
			return true;
		}
		
		SceneNode::~SceneNode()
		{

		}

		void SceneNode::addAnimation(sptr<IAnimation> nanimation)
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

		void SceneNode::updateAnimations()
		{
			if (!_animations.empty())
			{
				for (auto &animation : _animations)
				{
					if (!animation->animate(this))
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

	
	}
}
