#include "transformable.hpp"
#include <cmath>

namespace lib
{
	namespace draw
	{
		Transformable::Transformable() :
			//origin{ {0, 0} }, 
			position{ {0, 0} }, rotation{ {0.0f} }, scale{ vector2df{ 1, 1 } },
			m_transformation{ Transformation{} } {}

		Transformable::~Transformable()
		{
		}

		void Transformable::move(const vector2df &offset)
		{
			position = (position.get() + offset);
		}

		const Transformation &Transformable::transformation()
		{
			// Recompute the combined transformation if needed
			if (transformationNeedUpdate())
			{
				f32 angle = -rotation * 3.141592654f / 180.f;
				f32 cosine = static_cast<f32>(std::cos(angle));
				f32 sine = static_cast<f32>(std::sin(angle));
				f32 sxc = scale->x * cosine;
				f32 syc = scale->y * cosine;
				f32 sxs = scale->x * sine;
				f32 sys = scale->y * sine;
//				f32 tx = -origin->x * sxc - origin->y * sys + position->x;
//				f32 ty = origin->x * sxs - origin->y * syc + position->y;

//				f32 tx = position->x;
//				f32 ty = position->y;

				m_transformation = Transformation{ sxc, sys, position->x,
					-sxs, syc, position->y,
					0.f, 0.f, 1.f };

				resetTransformationNeedUpdate();
				m_transformationFrameUpdated = true;
			}

			return m_transformation;
		}

		bool Transformable::transformationNeedUpdate()
		{
			return position.changed() || scale.changed() || rotation.changed();
		}

		void Transformable::resetTransformationNeedUpdate()
		{
			position.resetChanged();
			scale.resetChanged();
			rotation.resetChanged();
		}

	}
}
