#include "transformation.hpp"
#include <cmath>

namespace lib
{
	namespace draw
	{
		const Transformation Transformation::Identity;

		Transformation::Transformation()
		{
			m_matrix[0] = 1.f; m_matrix[4] = 0.f; m_matrix[8] = 0.f; m_matrix[12] = 0.f;
			m_matrix[1] = 0.f; m_matrix[5] = 1.f; m_matrix[9] = 0.f; m_matrix[13] = 0.f;
			m_matrix[2] = 0.f; m_matrix[6] = 0.f; m_matrix[10] = 1.f; m_matrix[14] = 0.f;
			m_matrix[3] = 0.f; m_matrix[7] = 0.f; m_matrix[11] = 0.f; m_matrix[15] = 1.f;
		}

		Transformation::Transformation(f32 a00, f32 a01, f32 a02,
			f32 a10, f32 a11, f32 a12,
			f32 a20, f32 a21, f32 a22)
		{
			m_matrix[0] = a00; m_matrix[4] = a01; m_matrix[8] = 0.f; m_matrix[12] = a02;
			m_matrix[1] = a10; m_matrix[5] = a11; m_matrix[9] = 0.f; m_matrix[13] = a12;
			m_matrix[2] = 0.f; m_matrix[6] = 0.f; m_matrix[10] = 1.f; m_matrix[14] = 0.f;
			m_matrix[3] = a20; m_matrix[7] = a21; m_matrix[11] = 0.f; m_matrix[15] = a22;
		}

		const f32* Transformation::getMatrix() const
		{
			return m_matrix;
		}

		Transformation Transformation::getInverse() const
		{
			// Compute the determinant
			float det = m_matrix[0] * (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) -
				m_matrix[1] * (m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) +
				m_matrix[3] * (m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]);

			// Compute the inverse if the determinant is not zero
			// (don't use an epsilon because the determinant may *really* be tiny)
			if (det != 0.f)
			{
				return Transformation{ (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) / det,
					-(m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) / det,
					(m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]) / det,
					-(m_matrix[15] * m_matrix[1] - m_matrix[3] * m_matrix[13]) / det,
					(m_matrix[15] * m_matrix[0] - m_matrix[3] * m_matrix[12]) / det,
					-(m_matrix[13] * m_matrix[0] - m_matrix[1] * m_matrix[12]) / det,
					(m_matrix[7] * m_matrix[1] - m_matrix[3] * m_matrix[5]) / det,
					-(m_matrix[7] * m_matrix[0] - m_matrix[3] * m_matrix[4]) / det,
					(m_matrix[5] * m_matrix[0] - m_matrix[1] * m_matrix[4]) / det };
			}
			else
			{
				return Identity;
			}
		}

		vector2df Transformation::transformPoint(f32 x, f32 y) const
		{
			return vector2df{ m_matrix[0] * x + m_matrix[4] * y + m_matrix[12],
				m_matrix[1] * x + m_matrix[5] * y + m_matrix[13] };
		}

		vector2df Transformation::transformPoint(const vector2df &point) const
		{
			return transformPoint(point.x, point.y);
		}

		Rectf32 Transformation::transformRect(const Rectf32 &rectangle) const
		{
			// Transform the 4 corners of the rectangle
			const vector2df points[] =
			{
				transformPoint(rectangle.left, rectangle.top),
				transformPoint(rectangle.left, rectangle.top + rectangle.height),
				transformPoint(rectangle.left + rectangle.width, rectangle.top),
				transformPoint(rectangle.left + rectangle.width, rectangle.top + rectangle.height)
			};

			// Compute the bounding rectangle of the transformed points
			float left = points[0].x;
			float top = points[0].y;
			float right = points[0].x;
			float bottom = points[0].y;
			for (int i = 1; i < 4; ++i)
			{
				if (points[i].x < left)   left = points[i].x;
				else if (points[i].x > right)  right = points[i].x;
				if (points[i].y < top)    top = points[i].y;
				else if (points[i].y > bottom) bottom = points[i].y;
			}

			return Rectf32{ left, top, right - left, bottom - top };
		}

		Transformation &Transformation::combine(const Transformation &transform)
		{
			const f32 *a = m_matrix;
			const f32 *b = transform.m_matrix;

			*this = Transformation{ a[0] * b[0] + a[4] * b[1] + a[12] * b[3],
				a[0] * b[4] + a[4] * b[5] + a[12] * b[7],
				a[0] * b[12] + a[4] * b[13] + a[12] * b[15],
				a[1] * b[0] + a[5] * b[1] + a[13] * b[3],
				a[1] * b[4] + a[5] * b[5] + a[13] * b[7],
				a[1] * b[12] + a[5] * b[13] + a[13] * b[15],
				a[3] * b[0] + a[7] * b[1] + a[15] * b[3],
				a[3] * b[4] + a[7] * b[5] + a[15] * b[7],
				a[3] * b[12] + a[7] * b[13] + a[15] * b[15] };

			return *this;
		}

		Transformation &Transformation::translate(f32 x, f32 y)
		{
			Transformation translation{ 1, 0, x,
				0, 1, y,
				0, 0, 1 };

			return combine(translation);
		}

		Transformation &Transformation::translate(const vector2df &offset)
		{
			return translate(offset.x, offset.y);
		}

		Transformation &Transformation::rotate(f32 angle)
		{
			float rad = angle * 3.141592654f / 180.f;
			float cos = std::cos(rad);
			float sin = std::sin(rad);

			Transformation rotation{ cos, -sin, 0,
				sin, cos, 0,
				0, 0, 1 };

			return combine(rotation);
		}

		Transformation &Transformation::rotate(f32 angle, f32 centerX, f32 centerY)
		{
			f32 rad = angle * 3.141592654f / 180.f;
			f32 cos = std::cos(rad);
			f32 sin = std::sin(rad);

			Transformation rotation{ cos, -sin, centerX * (1 - cos) + centerY * sin,
				sin, cos, centerY * (1 - cos) - centerX * sin,
				0, 0, 1 };

			return combine(rotation);
		}

		Transformation &Transformation::rotate(f32 angle, const vector2df& center)
		{
			return rotate(angle, center.x, center.y);
		}

		Transformation& Transformation::scale(f32 scaleX, f32 scaleY)
		{
			Transformation scaling(scaleX, 0, 0,
				0, scaleY, 0,
				0, 0, 1);

			return combine(scaling);
		}

		Transformation &Transformation::scale(f32 scaleX, f32 scaleY, f32 centerX, f32 centerY)
		{
			Transformation scaling{ scaleX, 0, centerX * (1 - scaleX),
				0, scaleY, centerY * (1 - scaleY),
				0, 0, 1 };

			return combine(scaling);
		}

		Transformation &Transformation::scale(const vector2df& factors)
		{
			return scale(factors.x, factors.y);
		}

		Transformation &Transformation::scale(const vector2df& factors, const vector2df& center)
		{
			return scale(factors.x, factors.y, center.x, center.y);
		}

		Transformation Transformation::operator *(const Transformation& right)
		{
			return Transformation(*this).combine(right);
		}

		Transformation &Transformation::operator *=(const Transformation& right)
		{
			return combine(right);
		}

		vector2df Transformation::operator *(const vector2df &right)
		{
			return transformPoint(right);
		}
	}
}
