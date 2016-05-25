#include "transformable.hpp"
#include <cmath>

namespace lib
{
	namespace draw
	{
		Transformable::Transformable() :
			m_origin{ 0, 0 }, m_position{ 0, 0 }, m_rotation{ 0 }, scale{ vector2df{ 1, 1 } },
			m_transformation{}, m_transformationNeedUpdate{ true }, m_inverseTransformation{}, m_inverseTransformationNeedUpdate{ true } {}

		Transformable::~Transformable()
		{
		}

		void Transformable::setPosition(const vector2df &position)
		{
			m_position = position;
			m_transformationNeedUpdate = true;
			m_inverseTransformationNeedUpdate = true;
		}

		void Transformable::setRotation(f32 angle)
		{
			m_rotation = (fmod(angle, 360.f));
			if (m_rotation < 0)
				m_rotation += 360.f;

			m_transformationNeedUpdate = true;
			m_inverseTransformationNeedUpdate = true;
		}

		void Transformable::setOrigin(const vector2df &origin)
		{
			m_origin = origin;
			m_transformationNeedUpdate = true;
			m_inverseTransformationNeedUpdate = true;
		}

		const vector2df &Transformable::position() const
		{
			return m_position;
		}

		f32 Transformable::rotation() const
		{
			return m_rotation;
		}

		const vector2df &Transformable::origin() const
		{
			return m_origin;
		}

		void Transformable::move(const vector2df &offset)
		{
			setPosition(position()+offset);
		}

		void Transformable::rotate(f32 angle)
		{
			setRotation(m_rotation + angle);
		}

		const Transformation &Transformable::transformation()
		{
			// Recompute the combined transformation if needed
			if (m_transformationNeedUpdate)
			{
				float angle = -m_rotation * 3.141592654f / 180.f;
				float cosine = static_cast<float>(std::cos(angle));
				float sine = static_cast<float>(std::sin(angle));
				float sxc = scale->x * cosine;
				float syc = scale->y * cosine;
				float sxs = scale->x * sine;
				float sys = scale->y * sine;
				float tx = -m_origin.x * sxc - m_origin.y * sys + m_position.x;
				float ty = m_origin.x * sxs - m_origin.y * syc + m_position.y;

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
