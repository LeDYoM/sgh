#include "rendertarget_impl.hpp"
#include <lib/core/convops.hpp>
#include <lib/draw/rendernode.hpp>

namespace lib
{
	namespace drivers
	{
		namespace render
		{
			SFMLRenderTarget::SFMLRenderTarget(sf::RenderTarget * mySelf)
				: m_renderTarget{ mySelf }
			{
			}

			void SFMLRenderTarget::draw(const draw::RenderNode *node)
			{
				m_renderTarget->draw(convert(node->vertexArray()), node->vertexArray().size(), convert(node->vertexArray().getPrimitiveType()), node->renderStates());
			}

			void SFMLRenderTarget::setView(const Rectf32 & rectangle, const Rectf32 & vPort)
			{
				m_view.reset(convert(rectangle));
				m_renderTarget->setView(m_view);
			}
		}
	}
}

