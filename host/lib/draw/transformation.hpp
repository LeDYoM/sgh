#ifndef LIB_TRANSFORMATION_HPP
#define LIB_TRANSFORMATION_HPP

#include <lib/include/types.hpp>
#include <lib/include/rect.hpp>
#include <array>

namespace lib
{
	namespace draw
	{
		class Transformation
		{
		public:
			using TransformationDataType = std::array<f32, 16>;

			Transformation();
			Transformation(f32 a00, f32 a01, f32 a02,
				f32 a10, f32 a11, f32 a12,
				f32 a20, f32 a21, f32 a22);

			const TransformationDataType &getMatrix() const;
			Transformation getInverse() const;
			vector2df transformPoint(float x, float y) const;
			vector2df transformPoint(const vector2df &point) const;
			Rectf32 transformRect(const Rectf32 &rectangle) const;
			Transformation &combine(const Transformation &transform);
			Transformation &translate(f32 x, f32 y);
			Transformation &translate(const vector2df &offset);
			Transformation &rotate(f32 angle);
			Transformation &rotate(f32 angle, f32 centerX, f32 centerY);
			Transformation &rotate(f32 angle, const vector2df &center);
			Transformation &scale(f32 scaleX, f32 scaleY);
			Transformation &scale(f32 scaleX, f32 scaleY, f32 centerX, f32 centerY);
			Transformation &scale(const vector2df &factors);
			Transformation &scale(const vector2df &factors, const vector2df &center);
			Transformation operator*(const Transformation &right);
			Transformation &operator*=(const Transformation &right);
			vector2df operator*(const vector2df &right);
		private:
			TransformationDataType  m_matrix;
		};

	}
}

#endif
