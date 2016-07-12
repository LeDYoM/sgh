#ifndef LIB_DRAW_CAMERA_HPP
#define LIB_DRAW_CAMERA_HPP

#include <lib/include/types.hpp>
#include <lib/include/properties.hpp>
#include "transformation.hpp"

namespace lib
{
	namespace draw
	{
		class LIB_API Camera
		{
		public:
			Camera();
			~Camera();
			NotifableProperty<Rectf32> view;
			NotifableProperty<f32> rotation;
			void setViewport(const Rectf32& viewport);
			void reset(const Rectf32& rectangle);
			const Rectf32& getViewport() const;
			void move(f32 offsetX, f32 offsetY);
			void move(const vector2df& offset);
			void rotate(f32 angle);
			void zoom(f32 factor);
			const Transformation& getTransform();
		private:
			Rectf32 m_viewport;
			Transformation m_transform;
			bool m_transformUpdated;
		};
	}
}

#endif
