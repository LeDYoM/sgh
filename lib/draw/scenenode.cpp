#include "scenenode.hpp"
#include "rendergroup.hpp"
#include "animation.hpp"

namespace lib
{
	namespace draw
	{
		SceneNode::SceneNode(RenderGroup *const p_parent, const str &name)
			: m_parent{ p_parent }, m_name(name), Object{ p_parent } {}
		
		bool SceneNode::init()
		{
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
					return canimation->name() == nanimation->name();
				});

				if (elemFound != _animations.end())
				{
					LOG_WARNING("Same animation type already in node");
					removeFromspVector(*elemFound, _animations);
				}
			}

			_animations.push_back(nanimation);
		}

		void SceneNode::updateAnimations()
		{
			if (!_animations.empty())
			{
				for (auto &animation : _animations)
				{
					if (!animation->animate())
					{
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
