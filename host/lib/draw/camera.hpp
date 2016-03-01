#ifndef LIB_DRAW_VIEW_HPP
#define LIB_DRAW_VIEW_HPP

#include <lib/include/types.hpp>

namespace lib
{
	namespace draw
	{
		class Camera
		{
		public:
			explicit Camera() {}
			explicit Camera(const Rectf32 &rectangle) : m_target{ rectangle } {}
			inline const Rectf32 &target() const { return m_target; }
			inline Rectf32 &target() { return m_target; }
			inline void setSize(const vector2df &size)
			{
				m_target.width = size.x;
				m_target.height = size.y;
			}

		private:
			Rectf32 m_target;
		};
	}
}

#endif
