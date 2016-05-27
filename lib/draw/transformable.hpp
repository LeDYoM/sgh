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

			void move(const vector2df &offset);
			NotifableProperty<vector2df> position;
			NotifableProperty<vector2df> scale;
//			NotifableProperty<vector2df> origin;
			NotifableProperty<f32> rotation;
			const Transformation &transformation();
			const Transformation &inverseTransform();

		private:
			bool transformationNeedUpdate();
			void resetTransformationNeedUpdate();
			Transformation m_transformation;
			Transformation m_inverseTransformation;
		};
	}
}

#endif
