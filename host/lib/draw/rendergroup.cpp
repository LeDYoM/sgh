#include "rendergroup.hpp"
#include "renderizable.hpp"
#include "nodeshape.hpp"
#include "nodetext.hpp"
#include <lib/core/window.hpp>

namespace lib
{
	namespace draw
	{
		RenderGroup::RenderGroup(const std::string &name, RenderGroup *parent)
			: HasName{ name }, _parent{ parent }
		{
		}


		RenderGroup::~RenderGroup()
		{
			_renderNodes.clear();
		}

		sptr<NodeText> RenderGroup::createText(const std::string &name)
		{
			auto result = sptr<NodeText>(new NodeText(name));
			addRenderizable(result);
			return result;
		}

		sptr<NodeShape> RenderGroup::createShape(const std::string &name, const lib::vector2df &radius/*=lib::vector2df()*/, u32 pointCount/*=30*/)
		{
			auto result = sptr<NodeShape>(new NodeShape(name,radius,pointCount));
			addRenderizable(result);
			return result;
		}

		sptr<NodeShape> RenderGroup::createSpriteShape(const std::string &name, const lib::vector2df &radius /*= lib::vector2df()*/)
		{
			auto result = sptr<NodeShape>(new NodeShape(name,radius, 4,NodeShape::NodeMode::Sprite));
			addRenderizable(result);
			return result;
		}

		sptr<draw::Renderizable> RenderGroup::addRenderizable(sptr<Renderizable> newElement)
		{
			_renderNodes.push_back(newElement);
			return newElement;
		}

		bool RenderGroup::removeRenderizable(sptr<Renderizable> element)
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

				for (const auto renderizable : _renderNodes)
				{
					rNodes += renderizable->draw(states);
				}
				states.transform = oldTransformation;
				return rNodes;
			}

			return 0;
		}

		sptr<RenderGroup> RenderGroup::createNewRenderGroup(const std::string & name, sptr<IDrawable> beforeNode)
		{
			sptr<RenderGroup> rg = std::make_shared<RenderGroup>(name, this);
			addRenderGroup(rg, beforeNode);
			return rg;
		}

		void RenderGroup::addRenderGroup(sptr<RenderGroup> node, sptr<IDrawable> beforeNode)
		{
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
			node->_parent = this;
		}

		bool RenderGroup::removeRenderGroup(sptr<RenderGroup> element)
		{
			return removeFromspVector(element, _renderNodes);
		}

		void RenderGroup::clear()
		{
			_renderNodes.clear();
		}
	}
}
