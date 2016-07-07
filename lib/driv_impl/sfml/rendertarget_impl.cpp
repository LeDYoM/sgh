#include "rendertarget_impl.hpp"
#include <lib/core/convops.hpp>

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

			void SFMLRenderTarget::draw(const draw::VertexArray & vertexArray, const draw::RenderStates & states)
			{
				m_renderTarget->draw(convert(vertexArray), vertexArray.size(), convert(vertexArray.getPrimitiveType()), convert(states));

			}
			void SFMLRenderTarget::setView(const Rectf32 & rectangle, const vector2df & vPort)
			{
				m_view.reset(convert(rectangle));
				m_renderTarget->setView(m_view);
			}
		}
	}
}

