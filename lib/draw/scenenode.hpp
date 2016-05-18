#ifndef LIB_SCENENODE_HPP__
#define LIB_SCENENODE_HPP__

#include <lib/core/obj.hpp>
#include "iparentable.hpp"
#include "transformable.hpp"
#include <lib/core/vecsptr.hpp>

namespace lib
{
	namespace draw
	{
		class RenderGroup;
		class IAnimation;
		class SceneNode : public IParentable<RenderGroup>, public Transformable, public virtual Object
		{
		public:
			SceneNode(const str &name);
			virtual bool init();
			virtual ~SceneNode();

			inline void setActive(bool nv) { m_active = nv; }
			inline const bool isActive() const { return m_active; }

			inline void setVisible(bool nv) { m_visible = nv; }
			inline const bool isVisible() const { return m_visible; }
			inline const str& name() const { return m_name; }

			void addAnimation(sptr<IAnimation> nanimation);
			void updateAnimations();

		private:
			bool m_active{ true };
			bool m_visible{ true };
			str m_name;

			VecSPtr<IAnimation> _animations;
			std::vector<sptr<IAnimation>> _animationsToDelete;
		};
	
	}
}

#endif
