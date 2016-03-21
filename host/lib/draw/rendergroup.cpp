#include "rendergroup.hpp"
#include "rendernode.hpp"
#include "nodeshape.hpp"
#include "nodetext.hpp"
#include <lib/core/window.hpp>

namespace lib
{
	namespace draw
	{
		RenderGroup::RenderGroup(const std::string &name)
			: IParentable{}, INamedDrawable(name) {}

		RenderGroup::~RenderGroup()
		{
			_renderNodes.clear();
		}

		bool RenderGroup::init()
		{
			return true;
		}

		sptr<NodeText> RenderGroup::createText(const std::string &name)
		{
			auto result = sptr<NodeText>{new NodeText(name)};
			addRenderNode(result);
			return result;
		}

		sptr<NodeShape> RenderGroup::createShape(const std::string &name, const lib::vector2df &radius/*=lib::vector2df()*/, u32 pointCount/*=30*/)
		{
			auto result = sptr<NodeShape>(new NodeShape(name,radius,pointCount));
			addRenderNode(result);
			return result;
		}

		sptr<NodeShape> RenderGroup::createSpriteShape(const std::string &name, const lib::vector2df &radius /*= lib::vector2df()*/)
		{
			auto result = sptr<NodeShape>(new NodeShape(name,radius, 4,NodeShape::NodeMode::Sprite));
			addRenderNode(result);
			return result;
		}

		sptr<draw::RenderNode> RenderGroup::addRenderNode(sptr<RenderNode> newElement)
		{
			newElement->setParent(this);
			_renderNodes.push_back(newElement);
			return newElement;
		}

		bool RenderGroup::removeRenderNode(sptr<RenderNode> element)
		{
			return removeFromspVector(element, _renderNodes);
		}

		u32 RenderGroup::draw(lib::draw::RenderStates &states)
		{
			if (isVisible())
			{
				updateAnimations();
				u32 rNodes{ 0 };
				auto oldTransformation = states.transform;
				states.transform *= transformation();

				for (const auto renderNode : _renderNodes)
				{
					rNodes += renderNode->draw(states);
				}
				states.transform = oldTransformation;
				return rNodes;
			}

			return 0;
		}

		sptr<RenderGroup> RenderGroup::createNewRenderGroup(const std::string & name, sptr<INamedDrawable> beforeNode)
		{
			sptr<RenderGroup> rg = sptr<RenderGroup>{ new RenderGroup(name) };
			addRenderGroup(rg, beforeNode);
			return rg;
		}

		void RenderGroup::addRenderGroup(sptr<RenderGroup> node, sptr<INamedDrawable> beforeNode)
		{
			__ASSERT(node, "Trying to add nullptr node");
			node->setParent(this);
			if (!beforeNode)
			{
				_renderNodes.push_back(node);
			}
			else
			{
				for (auto iterator = _renderNodes.begin(); iterator != _renderNodes.end();++iterator)
				{
					if (*iterator == beforeNode)
					{
						_renderNodes.insert(iterator, node);
						iterator = _renderNodes.end()-1;
					}
				}
			}
			node->init();
		}

		bool RenderGroup::removeRenderGroup(sptr<RenderGroup> element)
		{
			return removeFromspVector(element, _renderNodes);
		}

		void RenderGroup::clear()
		{
			_renderNodes.clear();
		}

		sptr<INamedDrawable> RenderGroup::findByName(const str &name) const
		{
			auto result( std::find_if(_renderNodes.begin(), _renderNodes.end(), [name](const sptr<INamedDrawable> &node)
			{
				return (node->name() == name);
			}) );

			return (result != _renderNodes.end()) ? *result : sptr<INamedDrawable>();
		}

		lib::draw::Scene *const RenderGroup::parentScene()
		{
			__ASSERT(m_parent, "Error getting parent scene: nullptr parent");
			return m_parent->parentScene();
		}

		void RenderGroup::for_each_renderNode(std::function<void(sptr<INamedDrawable> node)> f)
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

		bool RenderGroup::activateOne(sptr<INamedDrawable> node)
		{
			__ASSERT(node, "Node parameter is nullptr");
			bool found{ false };

			for (auto node_ : _renderNodes)
			{
				bool isThis{ node == node_ };
				node_->setVisible(isThis);
				found |= (isThis);
			}
			return found;
		}
	}
}
