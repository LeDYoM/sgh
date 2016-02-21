#ifndef LIB_DRAW_VIEW_HPP
#define LIB_DRAW_VIEW_HPP

#include <lib/include/types.hpp>
#include <lib/include/rect.hpp>

namespace lib
{
	namespace draw
	{
		class View
		{
		public:
			explicit View(const Rectf32 &rectangle);
			View(const vector2df &topLeft, const vector2df &size);
			inline const Rectf32_ &target() const { return m_target; }
			inline Rectf32_ &target() { return m_target; }
		private:
			Rectf32_ m_target;
		};
	}
}

#endif
