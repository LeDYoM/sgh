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
			const vector2df &position() const;
			void move(const vector2df &offset);
			NotifableProperty<vector2df> scale;
			NotifableProperty<vector2df> origin;
			NotifableProperty<f32> rotation;
			const Transformation &transformation();
			const Transformation &inverseTransform();

		private:
			vector2df m_position;
			Transformation m_transformation;
			bool m_transformationNeedUpdate;
			Transformation m_inverseTransformation;
			bool m_inverseTransformationNeedUpdate;
		};
	}
}

#endif
