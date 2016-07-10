#include "camera.hpp"
#include <SFML/Graphics/View.hpp>

namespace lib
{
	namespace draw
	{
		Camera::Camera() :
			center{},	size{}, rotation{},	m_viewport{ 0, 0, 1, 1 },
			m_transformUpdated{ false }
		{
			reset(Rectf32{ 0, 0, 1000, 1000 });
		}
		/*
		Camera::Camera(const Rectf32& rectangle) :
			center{}, size{}, rotation{},
			m_viewport{ 0, 0, 1, 1 }, m_transformUpdated{ false }
		{
			reset(rectangle);
		}

		Camera::Camera(const vector2df& center, const vector2df& size) :
			center{ center }, size{ size },	rotation{}, m_viewport(0, 0, 1, 1),
			m_transformUpdated{ false } 
		{}
		*/
		Camera::~Camera() {}

		void Camera::setViewport(const Rectf32& viewport)
		{
			m_viewport = viewport;
		}

		void Camera::reset(const Rectf32& rectangle)
		{
			center().x = rectangle.left + rectangle.width / 2.f;
			center().y = rectangle.top + rectangle.height / 2.f;
			size().x = rectangle.width;
			size().y = rectangle.height;
			rotation = 0;

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

		const Transformation& Camera::getTransform()
		{
			// Recompute the matrix if needed
			if (!m_transformUpdated)
			{
				// Rotation components
				f32 angle = rotation() * 3.141592654f / 180.f;
				f32 cosine = static_cast<float>(std::cos(angle));
				f32 sine = static_cast<float>(std::sin(angle));
				f32 tx = -center().x * cosine - center().y * sine + center().x;
				f32 ty = center().x * sine - center().y * cosine + center().y;

				// Projection components
				f32 a = 2.f / size().x;
				f32 b = -2.f / size().y;
				f32 c = -a * center().x;
				f32 d = -b * center().y;

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

