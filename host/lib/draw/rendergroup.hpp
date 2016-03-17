#ifndef __LIB_RENDERGROUP_HPP__
#define __LIB_RENDERGROUP_HPP__

#include <lib/include/types.hpp>
#include "inameddrawable.hpp"
#include "animationmanager.hpp"
#include <lib/core/vecsptr.hpp>
#include "transformable.hpp"

namespace lib
{
	namespace core
	{
		class Window;
	}
	namespace draw
	{
		class RenderNode;
		class NodeShape;
		class NodeText;
		class RenderGroup : public INamedDrawable, public anim::AnimationManager, public Transformable
		{
		public:
			RenderGroup(const std::string &name, RenderGroup *const parent=nullptr);
			virtual ~RenderGroup();

			sptr<NodeText> createText(const std::string &name);
			sptr<NodeShape> createShape(const std::string &name,const lib::vector2df &radius=lib::vector2df(),u32 pointCount=30);
			sptr<NodeShape> createSpriteShape(const std::string &name, const lib::vector2df &radius = lib::vector2df());
			sptr<draw::RenderNode> addRenderNode(sptr<RenderNode> newElement);
			bool removeRenderNode(sptr<RenderNode> element);
			void clear();

			sptr<RenderGroup> createNewRenderGroup(const std::string &name,sptr<IDrawable> beforeNode=nullptr);
			bool removeRenderGroup(sptr<RenderGroup> element);

			u32 draw(lib::draw::RenderStates &states) override;

			sptr<IDrawable> findByName(const str &name) const;
			template <class T> sptr<T> findByNameAs(const str&name) const
			{
				return std::dynamic_pointer_cast<T>(findByName(name));
			}

			RenderGroup &operator=(RenderGroup &r) = delete;

		protected:
			void addRenderGroup(sptr<RenderGroup> node, sptr<IDrawable> beforeNode = nullptr);

			RenderGroup *const parent() const { return _parent; }
			VecSPtr<INamedDrawable> _renderNodes;

		private:
			RenderGroup *_parent{ nullptr };
		};
	}
}

#endif
