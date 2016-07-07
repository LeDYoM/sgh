#ifndef LIB_DRIVERS_WWINDOW_HPP
#define LIB_DRIVERS_WWINDOW_HPP

#include <lib/include/types.hpp>
#include <lib/core/data.hpp>

namespace lib
{
	namespace drivers
	{
		namespace render
		{
			class RenderTarget;
		}
		namespace window
		{
			class IWWindow
			{
			public:
				virtual bool create(u32 width, u32 height, u32 bpp, const char *title, u32 depth, u32 stencil, u32 antialiasing, u32  major, u32 minor, u32 attributes) = 0;
				virtual bool resizePending() const = 0;
				virtual vector2du32 size() const = 0;
				virtual void setVerticalSync(bool enabled) = 0;
				virtual void setTitle(const char *title) = 0;
				virtual void clear() = 0;
				virtual void display() = 0;
				virtual void collectEvents() = 0;
				virtual sptr<DataMap> nextEvent() = 0;
				virtual u32 pendingEvents() = 0;
				virtual sptr<render::RenderTarget> windowRenderTarget() const = 0;
			};
		}
	}
}

#endif
