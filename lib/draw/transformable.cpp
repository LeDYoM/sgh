#include "transformable.hpp"
#include <cmath>

namespace lib
{
	namespace draw
	{
		Transformable::Transformable() :
			origin{ {0, 0} }, position{ {0, 0} }, rotation{ {0.0f} }, scale{ vector2df{ 1, 1 } },
			m_transformation{}, m_transformationNeedUpdate{ true }, m_inverseTransformation{}, m_inverseTransformationNeedUpdate{ true } {}

		Transformable::~Transformable()
		{
		}

		void Transformable::move(const vector2df &offset)
		{
//			position = (position + offset);
		}

		const Transformation &Transformable::transformation()
		{
			// Recompute the combined transformation if needed
			if (m_transformationNeedUpdate)
			{
				float angle = -rotation * 3.141592654f / 180.f;
				float cosine = static_cast<float>(std::cos(angle));
				float sine = static_cast<float>(std::sin(angle));
				float sxc = scale->x * cosine;
				float syc = scale->y * cosine;
				float sxs = scale->x * sine;
				float sys = scale->y * sine;
				float tx = -origin->x * sxc - origin->y * sys + position->x;
				float ty = origin->x * sxs - origin->y * syc + position->y;

				m_transformation= Transformation{ sxc, sys, tx,
					-sxs, syc, ty,
					0.f, 0.f, 1.f };
				m_transformationNeedUpdate = false;
			}

			return m_transformation;
		}

		const Transformation &Transformable::inverseTransform()
		{
			if (m_inverseTransformationNeedUpdate)
			{
				m_inverseTransformation= transformation().inverse();
				m_inverseTransformationNeedUpdate = false;
			}

			return m_inverseTransformation;
		}
	}
}
