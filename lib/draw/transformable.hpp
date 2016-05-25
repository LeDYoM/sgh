#ifndef LIB_TRANSFORMABLE_HPP
#define LIB_TRANSFORMABLE_HPP

#include "transformation.hpp"
#include <lib/include/types.hpp>
#include <lib/include/properties.hpp>

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
			void setOrigin(const vector2df &origin);
			const vector2df &position() const;
			f32 rotation() const;
			const vector2df &origin() const;
			void move(const vector2df &offset);
			void rotate(f32 angle);
			NotifableProperty<vector2df> scale;
			const Transformation &transformation();
			const Transformation &inverseTransform();

		private:
			vector2df m_origin;
			vector2df m_position;
			f32 m_rotation;
			Transformation m_transformation;
			bool m_transformationNeedUpdate;
			Transformation m_inverseTransformation;
			bool m_inverseTransformationNeedUpdate;
		};
	}
}

#endif
