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
			NotifableProperty<f32> rotation;
			const Transformation &transformation();
			virtual void update();
			const bool frameTransformationNeedsUpdate() const { return m_frameTransformationNeedsUpdate; }
			void updateTransformationForFrameIfNecessary(const Transformation &other, const bool force);
			const Transformation &globalTransformation() const { return m_frameTransformation; }
		private:
			void updateTransformIfNecessary();
			bool transformationNeedUpdate();
			void resetTransformationNeedUpdate();

			Transformation m_frameTransformation;
			NotifableProperty<Transformation> m_transformation;
			bool m_frameTransformationNeedsUpdate{ true };
		};
	}
}

#endif
