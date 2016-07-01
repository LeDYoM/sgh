#ifndef LIB_DRAW_CAMERA_HPP
#define LIB_DRAW_CAMERA_HPP

#include <lib/include/types.hpp>
#include <lib/include/properties.hpp>
#include "transformation.hpp"

namespace lib
{
	namespace draw
	{
		class Camera
		{
		public:
			Camera();
			explicit Camera(const Rectf32 &rectangle);
			Camera(const vector2df& center, const vector2df& size);
			NotifableProperty<vector2df> center;
			NotifableProperty<vector2df> size;
			void setRotation(f32 angle);
			void setViewport(const Rectf32& viewport);
			void reset(const Rectf32& rectangle);
			const vector2df& getCenter() const;
			const vector2df& getSize() const;
			f32 getRotation() const;
			const Rectf32& getViewport() const;
			void move(f32 offsetX, f32 offsetY);
			void move(const vector2df& offset);
			void rotate(f32 angle);
			void zoom(f32 factor);
			const Transformation& getTransform() const;
		private:
			vector2df m_center;
			vector2df m_size;
			f32 m_rotation;
			Rectf32 m_viewport;
			mutable Transformation m_transform;
			mutable bool m_transformUpdated;
		};
	}
}

#endif
