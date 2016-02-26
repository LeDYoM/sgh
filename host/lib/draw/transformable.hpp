#ifndef LIB_TRANSFORMABLE_HPP
#define LIB_TRANSFORMABLE_HPP

#include "transformation.hpp"
#include <lib/include/types.hpp>


namespace lib
{
	namespace draw
	{
		class Transformable
		{
		public:
			Transformable();
			virtual ~Transformable();

			void setPosition(const vector2df& position);
			void setRotation(f32 angle);
			void setScale(const vector2df &factors);
			void setOrigin(const vector2df &origin);
			const vector2df &getPosition() const;
			f32 getRotation() const;
			const vector2df &getScale() const;
			const vector2df &getOrigin() const;
			void move(const vector2df &offset);
			void rotate(f32 angle);
			void scale(const vector2df &factor);
			const Transformation &getTransform();
			const Transformation &getInverseTransform();

		private:
			vector2df m_origin;
			vector2df m_position;
			f32 m_rotation;
			vector2df m_scale;
			Transformation m_transformation;
			bool m_transformationNeedUpdate;
			Transformation m_inverseTransformation;
			bool m_inverseTransformationNeedUpdate;
		};
	}
}

#endif
