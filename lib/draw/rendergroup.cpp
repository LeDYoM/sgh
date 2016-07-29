#include "rendergroup.hpp"
#include "rendernode.hpp"
#include "nodeshape.hpp"
#include "nodetext.hpp"
#include "scenemanager.hpp"
#include <lib/core/window.hpp>
#include "../core/appcontroller.hpp"

namespace lib
{
	namespace draw
	{
		RenderGroup::RenderGroup(RenderGroup *const p_parent, const std::string &name)
			: SceneNode(p_parent, name) {}

		RenderGroup::~RenderGroup()
		{
			_renderNodes.clear();
		}

		bool RenderGroup::init()
		{
			return SceneNode::init();
		}

		sptr<NodeText> RenderGroup::createText(const std::string &name)
		{
			auto result = sptr<NodeText>{new NodeText(this, name)};
			addNode(result);
			return result;
		}

		sptr<NodeShape> RenderGroup::createShape(const std::string &name, const lib::vector2df &radius/*=lib::vector2df()*/, u32 pointCount/*=30*/)
		{
			auto result = sptr<NodeShape>(new NodeShape(this, name,radius,pointCount));
			addNode(result);
			return result;
		}

		sptr<NodeShape> RenderGroup::createSpriteShape(const std::string &name, const lib::vector2df &radius /*= lib::vector2df()*/)
		{
			auto result = sptr<NodeShape>(new NodeShape(this, name,radius, 4,NodeShape::NodeMode::Sprite));
			addNode(result);
			return result;
		}

		sptr<SceneNode> RenderGroup::addNode(sptr<SceneNode> newElement, sptr<SceneNode> beforeNode)
		{
			__ASSERT(newElement, "Trying to add nullptr node");
			if (!beforeNode)
			{
				_renderNodes.push_back(newElement);
			}
			else
			{
				for (auto iterator = _renderNodes.begin(); iterator != _renderNodes.end(); ++iterator)
				{
					if (*iterator == beforeNode)
					{
						_renderNodes.insert(iterator, newElement);
						iterator = _renderNodes.end() - 1;
					}
				}
			}
			newElement->init();
			return newElement;

		}

		bool RenderGroup::removeNode(sptr<SceneNode> element)
		{
			return removeFromspVector(element, _renderNodes);
		}

		sptr<RenderGroup> RenderGroup::createNewRenderGroup(const std::string & name, sptr<SceneNode> beforeNode)
		{
			sptr<RenderGroup> rg = sptr<RenderGroup>{ new RenderGroup(this, name) };
			addNode(rg, beforeNode);
			return rg;
		}

		void RenderGroup::clear()
		{
			_renderNodes.clear();
		}

		sptr<SceneNode> RenderGroup::findByName(const str &name) const
		{
			auto result(std::find_if(_renderNodes.begin(), _renderNodes.end(), [name](const sptr<SceneNode> &node)
			{
				return (node->name() == name);
			}) );

			return (result != _renderNodes.end()) ? *result : sptr<SceneNode>();
		}

		void RenderGroup::for_each_renderNode(std::function<void(sptr<SceneNode> node)> f)
		{
			for (auto node : _renderNodes)
			{
				f(node);
			}
		}

		bool RenderGroup::activateOne(const str& node)
		{
			return activateOne(findByName(node));
		}

		bool RenderGroup::activateOne(sptr<SceneNode> node)
		{
			__ASSERT(node, "Node parameter is nullptr");
			bool found{ false };

			for (auto node_ : _renderNodes)
			{
				bool isThis{ node == node_ };
//				node_->setVisible(isThis);
				found |= (isThis);
			}
			return found;
		}
	}
}
