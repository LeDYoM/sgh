#ifndef LIB_TRANSFORMATION_HPP
#define LIB_TRANSFORMATION_HPP

#include <lib/include/types.hpp>
#include <lib/include/rect.hpp>

namespace lib
{
	namespace draw
	{
		class Transform
		{
		public:
			Transform();
			Transform(f32 a00, f32 a01, f32 a02,
				f32 a10, f32 a11, f32 a12,
				f32 a20, f32 a21, f32 a22);

			const f32* getMatrix() const;
			Transform getInverse() const;
			vector2df transformPoint(float x, float y) const;
			vector2df transformPoint(const vector2df &point) const;
			Rectf32 transformRect(const Rectf32 &rectangle) const;
			Transform &combine(const Transform &transform);
			Transform &translate(f32 x, f32 y);
			Transform &translate(const vector2df &offset);
			Transform &rotate(f32 angle);
			Transform &rotate(f32 angle, f32 centerX, f32 centerY);
			Transform &rotate(f32 angle, const vector2df &center);
			Transform &scale(f32 scaleX, f32 scaleY);
			Transform &scale(f32 scaleX, f32 scaleY, f32 centerX, f32 centerY);
			Transform &scale(const vector2df &factors);
			Transform &scale(const vector2df &factors, const vector2df &center);
			static const Transform Identity;
		private:
			f32 m_matrix[16]; ///< 4x4 matrix defining the transformation
		};

		Transform operator *(const Transform &left, const Transform &right);
		Transform &operator *=(Transform &left, const Transform &right);
		vector2df operator *(const Transform &left, const vector2df &right);
	}
}

#endif
