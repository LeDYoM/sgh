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
			Camera() : view { Rectf32{ .0f,.0f,1000.0f,1000.0f } }, rotation{}, 
				m_viewport{ 0, 0, 1, 1 }, m_transformUpdated{ false }
			{
				reset(Rectf32{ 0, 0, 1000, 1000 });
			}

			~Camera() {}

			NotifableProperty<Rectf32> view;
			NotifableProperty<f32> rotation;

			void setViewport(const Rectf32& viewport)
			{
				m_viewport = viewport;
			}

			void reset(const Rectf32& rectangle)
			{
				view() = rectangle;
				rotation = 0;

				m_transformUpdated = false;
			}

			const Rectf32& getViewport() const { return m_viewport; }
			void move(f32 offsetX, f32 offsetY) { view().move({ view->center().x + offsetX, view->center().y + offsetY }); }
			void move(const vector2df& offset) { move(offset.x, offset.y); }
			void rotate(f32 angle) { rotation() += angle; }
			void zoom(f32 factor) {
				factor;
				//			size = vector2df{ size() * factor };
			}
			
			const Transformation& getTransform()
			{
				// Recompute the matrix if needed
				if (!m_transformUpdated)
				{
					auto center(view().center());
					auto size(view().size());
					// Rotation components
					f32 angle = rotation() * 3.141592654f / 180.f;
					f32 cosine = static_cast<float>(std::cos(angle));
					f32 sine = static_cast<float>(std::sin(angle));
					f32 tx = -center.x * cosine - center.y * sine + center.x;
					f32 ty = center.x * sine - center.y * cosine + center.y;

					// Projection components
					f32 a = 2.f / size.x;
					f32 b = -2.f / size.y;
					f32 c = -a * center.x;
					f32 d = -b * center.y;

					// Rebuild the projection matrix
					m_transform = Transformation{ a * cosine, a * sine, a * tx + c,
						-b * sine, b * cosine, b * ty + d,
						0.f, 0.f, 1.f };
					m_transformUpdated = true;
				}

				return m_transform;
			}

		private:
			Rectf32 m_viewport;
			Transformation m_transform;
			bool m_transformUpdated;
		};
	}
}

#endif
