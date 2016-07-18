#ifndef LIB_DRIVERS_SFML_RENDERTARGET_IMPLEMENTATION_HPP
#define LIB_DRIVERS_SFML_RENDERTARGET_IMPLEMENTATION_HPP

#include <lib/drivers/render/rendertarget.hpp>
#include <lib/include/types.hpp>
#include "wwindow_impl.hpp"

namespace lib
{
	namespace drivers
	{
		namespace render
		{
			class SFMLRenderTarget : public RenderTarget
			{
			public:
				SFMLRenderTarget(sf::RenderTarget *mySelf);
				virtual void draw(const draw::VertexArray &vertexArray, const draw::RenderStates& states) override;
				virtual void draw(const sptr<draw::RenderNode> &node) override;
				virtual void setView(const Rectf32 &rectangle, const Rectf32 &vPort) override;
			private:
				sf::RenderTarget *m_renderTarget;
				sf::View m_view;
			};
		}
	}
}
#endif
