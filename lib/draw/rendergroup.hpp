#ifndef __LIB_RENDERGROUP_HPP__
#define __LIB_RENDERGROUP_HPP__

#include <lib/include/types.hpp>
#include "scenenode.hpp"
#include <lib/core/vecsptr.hpp>
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
		class RenderGroup : public SceneNode
		{
		public:
			RenderGroup(RenderGroup *const p_parent, const std::string &name);
			virtual ~RenderGroup();

			virtual bool init() override;
			sptr<NodeText> createText(const std::string &name);
			sptr<NodeShape> createShape(const std::string &name,const lib::vector2df &radius=lib::vector2df(),u32 pointCount=30);
			sptr<NodeShape> createSpriteShape(const std::string &name, const lib::vector2df &radius = lib::vector2df());
			sptr<SceneNode> addNode(sptr<SceneNode> newElement, sptr<SceneNode> beforeNode = nullptr);
			bool removeNode(sptr<SceneNode> element);
			void clear();

			sptr<RenderGroup> createNewRenderGroup(const std::string &name, sptr<SceneNode> beforeNode = nullptr);
			template <class T> sptr<T> createNewRenderGroupOf(const std::string &name, sptr<SceneNode> beforeNode = nullptr)
			{
				sptr<T> t{ new T(this, name) };
				addNode(t, beforeNode);
				return t;
			}
			sptr<SceneNode> findByName(const str &name) const;
			template <class T> sptr<T> findByNameAs(const str&name) const
			{
				return as<T>(findByName(name));
			}

			void for_each_renderNode(std::function<void(sptr<SceneNode> node)> f);
			virtual Scene *const parentScene();

			bool activateOne(const str& node);
			bool activateOne(sptr<SceneNode> node);

			inline const VecSPtr<SceneNode> renderNodes() { return _renderNodes; }

		protected:
			VecSPtr<SceneNode> _renderNodes;
		};
	}
}

#endif
