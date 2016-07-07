#ifndef LIB_DRAW_RENDERTARGET_HPP
#define LIB_DRAW_RENDERTARGET_HPP

#include <lib/draw/vertexarray.hpp>
#include <lib/draw/renderstates.hpp>
#include <lib/drivers/render/rendertarget.hpp>

namespace lib
{
	namespace draw
	{
		class RenderTarget
		{
		public:
			virtual void setView(const Rectf32 &rectangle, const vector2df &vPort) = 0;
			virtual void draw(const draw::VertexArray &vertexArray, const draw::RenderStates& states) = 0;
		};
	}
}

#endif
