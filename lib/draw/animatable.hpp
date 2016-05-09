#ifndef LIB_ANIMATABLE_HPP__
#define LIB_ANIMATABLE_HPP__

#include <vector>
#include "ianimation.hpp"
#include <lib/core/vecsptr.hpp>

namespace lib
{
	namespace draw
	{
		class Animatable
		{
		public:
			Animatable();
			virtual ~Animatable();
			void addAnimation(sptr<IAnimation> nanimation);
			void updateAnimations(const sptr<SceneNode> &node);
//			virtual void onAnimationStarted(sptr<IAnimation> anim, sptr<RenderNode> node);
//			virtual void onAnimationFinished(sptr<IAnimation> anim, sptr<RenderNode> node);
		private:
			VecSPtr<IAnimation> _animations;
			std::vector<sptr<IAnimation>> _animationsToDelete;
		};
	}
}

#endif
