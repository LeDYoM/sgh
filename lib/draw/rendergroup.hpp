#ifndef __LIB_RENDERGROUP_HPP__
#define __LIB_RENDERGROUP_HPP__

#include <lib/include/types.hpp>
#include "node.hpp"
#include "animationmanager.hpp"
#include <lib/core/vecsptr.hpp>
#include "iparentable.hpp"
#include "transformable.hpp"

#include <functional>

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
		class Scene;
		class RenderGroup : public IParentable<RenderGroup>, public Node, public anim::AnimationManager, public Transformable
		{
		public:
			RenderGroup(const std::string &name);
			virtual ~RenderGroup();

			virtual bool init();
			sptr<NodeText> createText(const std::string &name);
			sptr<NodeShape> createShape(const std::string &name,const lib::vector2df &radius=lib::vector2df(),u32 pointCount=30);
			sptr<NodeShape> createSpriteShape(const std::string &name, const lib::vector2df &radius = lib::vector2df());
			sptr<draw::RenderNode> addRenderNode(sptr<RenderNode> newElement);
			bool removeRenderNode(sptr<RenderNode> element);
			void clear();

			sptr<RenderGroup> createNewRenderGroup(const std::string &name, sptr<Node> beforeNode = nullptr);
			template <class T> sptr<T> createNewRenderGroupOf(const std::string &name, sptr<Node> beforeNode = nullptr)
			{
				sptr<T> t{ new T(name) };
				addRenderGroup(t, beforeNode);
				return t;
			}
			bool removeRenderGroup(sptr<RenderGroup> element);
			u32 draw(lib::draw::RenderStates &states) override;
			sptr<Node> findByName(const str &name) const;
			template <class T> sptr<T> findByNameAs(const str&name) const
			{
				return as<T>(findByName(name));
			}

			RenderGroup &operator=(RenderGroup &r) = delete;
			void for_each_renderNode(std::function<void(sptr<Node> node)> f);
			void addRenderGroup(sptr<RenderGroup> node, sptr<Node> beforeNode = nullptr);
			template <class T,class S> static sptr<T> as(sptr<S> node) { return std::dynamic_pointer_cast<T>(node); }
			virtual Scene *const parentScene();

			bool activateOne(const str& node);
			bool activateOne(sptr<Node> node);

		protected:
			VecSPtr<Node> _renderNodes;
		};
	}
}

#endif