#ifndef LIB_TRANSFORMABLE_HPP
#define LIB_TRANSFORMABLE_HPP

#include "transformation.hpp"
#include <lib/include/types.hpp>
#include <lib/include/properties.hpp>

namespace lib
{
	namespace draw
	{
		class LIB_API Transformable
		{
		public:
			explicit Transformable();
			Transformable(const Transformable &rh);
			Transformable& operator=(const Transformable &rh);
			Transformable(Transformable &&rh);
			Transformable& operator=(Transformable &&rh);

			NotifableProperty<vector2df> position;
			NotifableProperty<vector2df> scale;
			NotifableProperty<f32> rotation;

			LinkedNotifableProperty transformationNeedUpdate;
			void move(const vector2df &offset);
			const Transformation &transformation();

			virtual void update();
			bool updateTransformationForFrameIfNecessary(const Transformation &other, const bool force);
			const Transformation &globalTransformation() const;

		private:
			void updateTransformIfNecessary();

			Transformation m_frameTransformation;
			NotifableProperty<Transformation> m_transformation;
			bool m_frameTransformationNeedsUpdate{ true };
		};
	}
}

#endif
