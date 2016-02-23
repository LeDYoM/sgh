#ifndef __LIB_RENDERGROUP_HPP__
#define __LIB_RENDERGROUP_HPP__

#include <lib/include/types.hpp>
#include "HasName.hpp"
#include "idrawable.hpp"
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
		class Renderizable;
		class NodeShape;
		class NodeText;
		class RenderGroup : public lib::core::HasName, public IDrawable, public anim::AnimationManager, public Transformable
		{
		public:
			RenderGroup(const std::string &name, RenderGroup *parent=nullptr);
			virtual ~RenderGroup();

			sptr<NodeText> createText(const std::string &name);
			sptr<NodeShape> createShape(const std::string &name,const lib::vector2df &radius=lib::vector2df(),u32 pointCount=30);
			sptr<NodeShape> createSpriteShape(const std::string &name, const lib::vector2df &radius = lib::vector2df());
			sptr<draw::Renderizable> addRenderizable(sptr<Renderizable> newElement);
			bool removeRenderizable(sptr<Renderizable> element);
			void clear();

			sptr<RenderGroup> createNewRenderGroup(const std::string &name,sptr<IDrawable> beforeNode=nullptr);
			bool removeRenderGroup(sptr<RenderGroup> element);

			u32 draw(lib::core::Window *window, lib::draw::RenderStates &states) override;

		protected:
			void addRenderGroup(sptr<RenderGroup> node, sptr<IDrawable> beforeNode = nullptr);

			RenderGroup *parent() const { return _parent; }
			VecSPtr<IDrawable> _renderNodes;

		private:
			RenderGroup *_parent{ nullptr };
		};
	}
}

#endif
