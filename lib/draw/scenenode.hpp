#ifndef LIB_SCENENODE_HPP__
#define LIB_SCENENODE_HPP__

#include <lib/core/obj.hpp>
#include "transformable.hpp"
#include <lib/core/vecsptr.hpp>
#include <lib/include/color.hpp>

namespace lib
{
	namespace draw
	{
		class RenderGroup;
		class IAnimation;

		class LIB_API SceneNode : public Transformable, public Object
		{
		public:
			SceneNode(RenderGroup *const p_parent, const str &name);
			virtual bool init();
			virtual ~SceneNode();

			inline void setActive(bool nv) { m_active = nv; }
			inline const bool isActive() const { return m_active; }

			inline void setVisible(bool nv) { m_visible = nv; }
			inline const bool isVisible() const { return m_visible; }
			inline const str& name() const { return m_name; }

			void addAnimation(sptr<IAnimation> nanimation);
			void updateAnimations();

			const RenderGroup *const parent() const { return m_parent; }
			RenderGroup *parent() { return m_parent; }

		private:
			bool m_active{ true };
			bool m_visible{ true };
			RenderGroup *m_parent;
			str m_name;
			VecSPtr<IAnimation> _animations;
			std::vector<sptr<IAnimation>> _animationsToDelete;
		};
	
	}
}

#endif
