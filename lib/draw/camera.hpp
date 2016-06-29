#ifndef LIB_DRAW_CAMERA_HPP
#define LIB_DRAW_CAMERA_HPP

#include <lib/include/types.hpp>

namespace lib
{
	namespace draw
	{
		class CameraPriv;

		class Camera
		{
		public:
			explicit Camera(const Rectf32 &rectangle);
			inline const Rectf32 &target() const { return m_target; }
			void setSize(const vector2df &size);
			~Camera();
		private:
			uptr<CameraPriv> m_priv;
			Rectf32 m_target;
		};
	}
}

#endif
