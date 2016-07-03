#include "camera.hpp"

namespace lib
{
	namespace draw
	{
		Camera::Camera() :
			m_center{},	m_size{}, m_rotation{},	m_viewport{ 0, 0, 1, 1 },
			m_transformUpdated{ false }
		{
			reset(Rectf32{ 0, 0, 1000, 1000 });
		}

		Camera::Camera(const Rectf32& rectangle) :
			center{}, size{}, m_rotation{},
			m_viewport{ 0, 0, 1, 1 }, m_transformUpdated{ false }
		{
			reset(rectangle);
		}

		Camera::Camera(const vector2df& center, const vector2df& size) :
			m_center{ center }, m_size{ size },	m_rotation{}, m_viewport(0, 0, 1, 1),
			m_transformUpdated{ false } {}

		void Camera::setViewport(const Rectf32& viewport)
		{
			m_viewport = viewport;
		}

		void Camera::reset(const Rectf32& rectangle)
		{
			m_center.x = rectangle.left + rectangle.width / 2.f;
			m_center.y = rectangle.top + rectangle.height / 2.f;
			m_size.x = rectangle.width;
			m_size.y = rectangle.height;
			m_rotation = 0;

			m_transformUpdated = false;
		}

		const Rectf32 &Camera::getViewport() const
		{
			return m_viewport;
		}

		void Camera::move(f32 offsetX, f32 offsetY)
		{
			center = vector2df{ center().x + offsetX, center().y + offsetY };
		}

		void Camera::rotate(f32 angle)
		{
			rotation() += angle;
		}

		void Camera::zoom(f32 factor)
		{
			size = vector2df{ size() * factor };
		}

		const Transformation& Camera::getTransform() const
		{
			// Recompute the matrix if needed
			if (!m_transformUpdated)
			{
				// Rotation components
				f32 angle = m_rotation * 3.141592654f / 180.f;
				f32 cosine = static_cast<float>(std::cos(angle));
				f32 sine = static_cast<float>(std::sin(angle));
				f32 tx = -m_center.x * cosine - m_center.y * sine + m_center.x;
				f32 ty = m_center.x * sine - m_center.y * cosine + m_center.y;

				// Projection components
				f32 a = 2.f / m_size.x;
				f32 b = -2.f / m_size.y;
				f32 c = -a * m_center.x;
				f32 d = -b * m_center.y;

				// Rebuild the projection matrix
				m_transform = Transformation{ a * cosine, a * sine, a * tx + c,
					-b * sine, b * cosine, b * ty + d,
					0.f, 0.f, 1.f };
				m_transformUpdated = true;
			}

			return m_transform;
		}
	}
}

