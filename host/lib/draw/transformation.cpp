#include "transformation.hpp"
#include <cmath>

namespace lib
{
	namespace draw
	{
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

		const Transformation::TransformationDataType &Transformation::matrix() const
		{
			return m_matrix;
		}

		Transformation Transformation::inverse() const
		{
			// Compute the determinant
			f64 det_{ m_matrix[0] * (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) -
				m_matrix[1] * (m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) +
				m_matrix[3] * (m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]) };

			f32 det{ static_cast<f32>(det_) };

			// Compute the inverse if the determinant is not zero
			// (don't use an epsilon because the determinant may *really* be tiny)
			if (det_ != 0.f)
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
				return Transformation{};
			}
		}

		vector2df Transformation::transformPoint(const vector2df &point) const
		{
			return vector2df{ m_matrix[0] * point.x + m_matrix[4] * point.y + m_matrix[12],
				m_matrix[1] * point.x + m_matrix[5] * point.y + m_matrix[13] };
		}

		Rectf32 Transformation::transformRect(const Rectf32 &rectangle) const
		{
			// Transform the 4 corners of the rectangle
			const vector2df points[] =
			{
				transformPoint(rectangle.origin()),
				transformPoint({ rectangle.left, rectangle.top + rectangle.height }),
				transformPoint({ rectangle.left + rectangle.width, rectangle.top }),
				transformPoint(rectangle.dest())
			};

			// Compute the bounding rectangle of the transformed points
			f32 left = points[0].x;
			f32 top = points[0].y;
			f32 right = points[0].x;
			f32 bottom = points[0].y;
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
			const TransformationDataType &a = m_matrix;
			const TransformationDataType &b = transform.m_matrix;

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

		Transformation &Transformation::translate(const vector2df &offset)
		{
			Transformation translation{ 1, 0, offset.x,
				0, 1, offset.y,
				0, 0, 1 };

			return combine(translation);
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

		Transformation &Transformation::rotate(f32 angle, const vector2df& center)
		{
			f32 rad = angle * 3.141592654f / 180.f;
			f32 cos = std::cos(rad);
			f32 sin = std::sin(rad);

			Transformation rotation{ cos, -sin, center.x * (1 - cos) + center.y * sin,
				sin, cos, center.y * (1 - cos) - center.x * sin,
				0, 0, 1 };

			return combine(rotation);
		}

		Transformation &Transformation::scale(const vector2df& factors)
		{
			Transformation scaling(factors.x, 0, 0,
				0, factors.y, 0,
				0, 0, 1);

			return combine(scaling);
		}

		Transformation &Transformation::scale(const vector2df& factors, const vector2df& center)
		{
			Transformation scaling{ factors.x, 0, center.x * (1 - factors.x),
				0, factors.y, center.y * (1 - factors.y),
				0, 0, 1 };

			return combine(scaling);
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
