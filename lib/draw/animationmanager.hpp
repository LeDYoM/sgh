#ifndef __LIB_ANIMATIONMANAGER_HPP__
#define __LIB_ANIMATIONMANAGER_HPP__

#include <vector>
#include "animation.hpp"
#include <lib/core/vecsptr.hpp>

namespace lib
{
	namespace draw
	{
		class RenderNode;
		namespace anim
		{
			class AnimationManager
			{
			public:
				AnimationManager();
				virtual ~AnimationManager();
				virtual void onAnimationStarted(sptr<IAnimation> anim, sptr<RenderNode> node);
				virtual void onAnimationFinished(sptr<IAnimation> anim, sptr<RenderNode> node);
			private:
				VecSPtr<IAnimation> m_animations;
				std::vector<sptr<IAnimation>> m_animationsToDelete;
			};
		}
	}
}

#endif
