#ifndef __LIB_IDRAWABLE_HPP__
#define __LIB_IDRAWABLE_HPP__

#include <lib/include/types.hpp>
#include "renderstates.hpp"

namespace lib
{
	namespace core
	{
		class Window;
	}
	namespace draw
	{
		class IDrawable
		{
		public:
			IDrawable() {}
			virtual ~IDrawable() {}

			virtual u32 draw(lib::core::Window *window, RenderStates &states) = 0;

			inline bool isVisible() const { return visible; }
			inline void setVisible(bool nv) { visible = nv; }
		protected:
			bool visible{ true };
		};
	}
}

#endif
