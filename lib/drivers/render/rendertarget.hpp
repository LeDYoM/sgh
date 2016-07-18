#ifndef LIB_DRIVERS_RENDERTARGET_HPP
#define LIB_DRIVERS_RENDERTARGET_HPP

#include <lib/include/types.hpp>

namespace lib
{
	namespace draw
	{
		class RenderNode;
	}
	namespace drivers
	{
		namespace render
		{
			class RenderTarget
			{
			public:
				virtual void setView(const Rectf32 &rectangle, const Rectf32 &vPort) = 0;
				virtual void draw(const draw::RenderNode *node) = 0;
			};
		}
	}
}

#endif
