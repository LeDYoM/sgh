#ifndef LIB_DRAW_RENDERTARGET_HPP
#define LIB_DRAW_RENDERTARGET_HPP

#include <lib/draw/vertexarray.hpp>
#include <lib/draw/renderstates.hpp>

namespace lib
{
	namespace core
	{
		class RenderTarget
		{
		public:
			virtual void setViewRectangle(const Rectf32 &rectangle) = 0;
			virtual void setViewport(const vector2df &vPort) = 0;
			virtual void draw(const draw::VertexArray &vertexArray, const draw::RenderStates& states) = 0;
		};
	}
}

#endif
