#include "camera.hpp"

namespace lib
{
	namespace draw
	{
		Camera::Camera() :
			m_center{},	m_size{}, m_rotation{},	m_viewport{ 0, 0, 1, 1 },
			m_transformUpdated{ false }, m_invTransformUpdated{ false }
		{
			reset(Rectf32{ 0, 0, 1000, 1000 });
		}

		Camera::Camera(const Rectf32& rectangle) :
			m_center{}, m_size{}, m_rotation{},
			m_viewport{ 0, 0, 1, 1 }, m_transformUpdated{ false }, m_invTransformUpdated{ false }
		{
			reset(rectangle);
		}

		Camera::Camera(const vector2df& center, const vector2df& size) :
			m_center{ center }, m_size{ size },	m_rotation{}, m_viewport(0, 0, 1, 1),
			m_transformUpdated{ false }, m_invTransformUpdated{ false } {}

		void Camera::setCenter(f32 x, f32 y)
		{
			m_center.x = x;
			m_center.y = y;

			m_transformUpdated = false;
			m_invTransformUpdated = false;
		}

		void Camera::setCenter(const vector2df& center)
		{
			setCenter(center.x, center.y);
		}

		void Camera::setSize(f32 width, f32 height)
		{
			m_size.x = width;
			m_size.y = height;

			m_transformUpdated = false;
			m_invTransformUpdated = false;
		}

		void Camera::setSize(const vector2df& size)
		{
			setSize(size.x, size.y);
		}

		void Camera::setRotation(f32 angle)
		{
			m_rotation = static_cast<float>(fmod(angle, 360));
			if (m_rotation < 0)
				m_rotation += 360.f;

			m_transformUpdated = false;
			m_invTransformUpdated = false;
		}

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
			m_invTransformUpdated = false;
		}

		const vector2df& Camera::getCenter() const
		{
			return m_center;
		}

		const vector2df& Camera::getSize() const
		{
			return m_size;
		}

		float Camera::getRotation() const
		{
			return m_rotation;
		}

		const Rectf32 &Camera::getViewport() const
		{
			return m_viewport;
		}

		void Camera::move(float offsetX, float offsetY)
		{
			setCenter(m_center.x + offsetX, m_center.y + offsetY);
		}

		void Camera::move(const vector2df& offset)
		{
			setCenter(m_center + offset);
		}

		void Camera::rotate(float angle)
		{
			setRotation(m_rotation + angle);
		}

		void Camera::zoom(float factor)
		{
			setSize(m_size.x * factor, m_size.y * factor);
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

		const Transformation& Camera::getInverseTransform() const
		{
			// Recompute the matrix if needed
			if (!m_invTransformUpdated)
			{
				m_inverseTransform = getTransform().getInverse();
				m_invTransformUpdated = true;
			}

			return m_inverseTransform;
		}
	}
}

