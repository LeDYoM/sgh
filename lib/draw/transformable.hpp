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
			explicit Transformable() : position{}, rotation{}, scale{ vector2df{ 1, 1 } }, m_transformation{}
			{
				transformationNeedUpdate = { &position, &scale, &rotation };
			}

			Transformable(const Transformable &rh)
				: position{ rh.position }, rotation{ rh.rotation }, scale{ rh.scale }, 
				m_transformation{ rh.m_transformation }, transformationNeedUpdate { &position, &scale, &rotation } {}

			Transformable& operator=(const Transformable &rh)
			{
				position = rh.position;
				rotation = rh.rotation;
				scale = rh.scale;
				m_transformation = rh.m_transformation;
				transformationNeedUpdate = { &position, &scale, &rotation };
			}

			Transformable(Transformable &&rh)
				: position{ std::move(rh.position) }, rotation{ std::move(rh.rotation) }, scale{ std::move(rh.scale) },
				m_transformation{ std::move(rh.m_transformation) }, transformationNeedUpdate{ &position, &scale, &rotation } {}

			Transformable& operator=(Transformable &&rh)
			{
				position = std::move(rh.position);
				rotation = std::move(rh.rotation);
				scale = std::move(rh.scale);
				m_transformation = std::move(rh.m_transformation);
				transformationNeedUpdate = { &position, &scale, &rotation };
			}

			NotifableProperty<vector2df> position;
			NotifableProperty<vector2df> scale;
			NotifableProperty<f32> rotation;

			LinkedNotifableProperty transformationNeedUpdate;

			void move(const vector2df &offset) { position = (position() + offset); }

			const Transformation &transformation()
			{
				updateTransformIfNecessary();
				return m_transformation();
			}

			virtual void update() { updateTransformIfNecessary(); }

			bool updateTransformationForFrameIfNecessary(const Transformation &other, const bool force)
			{
				if (m_frameTransformationNeedsUpdate || force) {
					m_frameTransformationNeedsUpdate = false;
					m_frameTransformation = other * m_transformation();
					return true;
				}
				return false;
			}

			const Transformation &globalTransformation() const { return m_frameTransformation; }

		private:
			void updateTransformIfNecessary()
			{
				// Recompute the combined transformation if needed
				if (transformationNeedUpdate)
				{
					f32 angle = -rotation() * 3.141592654f / 180.f;
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

					transformationNeedUpdate.resetChanged();
					m_frameTransformationNeedsUpdate = true;
				}
			}

			Transformation m_frameTransformation;
			NotifableProperty<Transformation> m_transformation;
			bool m_frameTransformationNeedsUpdate{ true };
		};
	}
}

#endif
