#include "transformable.hpp"
#include <cmath>

namespace lib
{
	namespace draw
	{
		Transformable::Transformable() :
			m_origin{ 0, 0 }, m_position{ 0, 0 }, m_rotation{ 0 }, m_scale{ 1, 1 },
			m_transformation{}, m_transformationNeedUpdate{ true }, m_inverseTransformation{}, m_inverseTransformationNeedUpdate{ true } {}

		Transformable::~Transformable()
		{
		}

		void Transformable::setPosition(f32 x, f32 y)
		{
			m_position.x = x;
			m_position.y = y;
			m_transformationNeedUpdate = true;
			m_inverseTransformationNeedUpdate = true;
		}

		void Transformable::setPosition(const vector2df &position)
		{
			setPosition(position.x, position.y);
		}

		void Transformable::setRotation(f32 angle)
		{
			m_rotation = (fmod(angle, 360.f));
			if (m_rotation < 0)
				m_rotation += 360.f;

			m_transformationNeedUpdate = true;
			m_inverseTransformationNeedUpdate = true;
		}

		void Transformable::setScale(f32 factorX, f32 factorY)
		{
			m_scale.x = factorX;
			m_scale.y = factorY;
			m_transformationNeedUpdate = true;
			m_inverseTransformationNeedUpdate = true;
		}

		void Transformable::setScale(const vector2df &factors)
		{
			setScale(factors.x, factors.y);
		}

		void Transformable::setOrigin(f32 x, f32 y)
		{
			m_origin.x = x;
			m_origin.y = y;
			m_transformationNeedUpdate = true;
			m_inverseTransformationNeedUpdate = true;
		}

		void Transformable::setOrigin(const vector2df &origin)
		{
			setOrigin(origin.x, origin.y);
		}

		const vector2df &Transformable::getPosition() const
		{
			return m_position;
		}

		f32 Transformable::getRotation() const
		{
			return m_rotation;
		}

		const vector2df &Transformable::getScale() const
		{
			return m_scale;
		}

		const vector2df &Transformable::getOrigin() const
		{
			return m_origin;
		}

		void Transformable::move(f32 offsetX, f32 offsetY)
		{
			setPosition(m_position.x + offsetX, m_position.y + offsetY);
		}

		void Transformable::move(const vector2df &offset)
		{
			setPosition(m_position.x + offset.x, m_position.y + offset.y);
		}

		void Transformable::rotate(f32 angle)
		{
			setRotation(m_rotation + angle);
		}

		void Transformable::scale(f32 factorX, f32 factorY)
		{
			setScale(m_scale.x * factorX, m_scale.y * factorY);
		}

		void Transformable::scale(const vector2df &factor)
		{
			setScale(m_scale.x * factor.x, m_scale.y * factor.y);
		}

		const Transformation &Transformable::getTransform() const
		{
			// Recompute the combined transformation if needed
			if (m_transformationNeedUpdate)
			{
				float angle = -m_rotation * 3.141592654f / 180.f;
				float cosine = static_cast<float>(std::cos(angle));
				float sine = static_cast<float>(std::sin(angle));
				float sxc = m_scale.x * cosine;
				float syc = m_scale.y * cosine;
				float sxs = m_scale.x * sine;
				float sys = m_scale.y * sine;
				float tx = -m_origin.x * sxc - m_origin.y * sys + m_position.x;
				float ty = m_origin.x * sxs - m_origin.y * syc + m_position.y;

				m_transformation= Transformation{ sxc, sys, tx,
					-sxs, syc, ty,
					0.f, 0.f, 1.f };
				m_transformationNeedUpdate = false;
			}

			return m_transformation;
		}

		const Transformation &Transformable::getInverseTransform() const
		{
			if (m_inverseTransformationNeedUpdate)
			{
				m_inverseTransformation= getTransform().getInverse();
				m_inverseTransformationNeedUpdate = false;
			}

			return m_inverseTransformation;
		}
	}
}
