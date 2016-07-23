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
			struct WindowData
			{
				vector2du16 size;
				vector2du16 initialPosition{ 0,0 };
				u8 depth{ 0 };
				u8 bpp{ 32 };
				u16 major{ 0 };
				u16 minor{ 0 };
				u32 antialiasing{ 0 };
				bool fullscreen{ false };
				bool resizable{ true };
			};
			class IWWindow
			{
			public:
				virtual bool create(const WindowData&) = 0;
				virtual bool resizePending() const = 0;
				virtual vector2du16 size() const = 0;
				virtual void setVerticalSync(bool) = 0;
				virtual void setTitle(const str &title) = 0;
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
