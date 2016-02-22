#ifndef LIB_TRANSFORMABLE_HPP
#define LIB_TRANSFORMABLE_HPP

#include <SFML/Graphics/Transform.hpp>
#include <lib/include/types.hpp>

using namespace sf;

namespace lib
{
	namespace draw
	{
		class Transformable
		{
		public:
			Transformable();
			virtual ~Transformable();

			void setPosition(f32 x, f32 y);
			void setPosition(const vector2df& position);
			void setRotation(f32 angle);

			void setScale(f32 factorX, f32 factorY);
			void setScale(const vector2df &factors);
			void setOrigin(f32 x, f32 y);
			void setOrigin(const vector2df &origin);
			const vector2df &getPosition() const;
			f32 getRotation() const;
			const vector2df &getScale() const;
			const vector2df &getOrigin() const;
			void move(f32 offsetX, f32 offsetY);
			void move(const vector2df &offset);
			void rotate(f32 angle);
			void scale(f32 factorX, f32 factorY);
			void scale(const vector2df &factor);
			const Transform &getTransform() const;
			const Transform &getInverseTransform() const;

		private:
			vector2df m_origin;
			vector2df m_position;
			f32 m_rotation;
			Vector2f m_scale;
			mutable Transform m_transform;
			mutable bool m_transformNeedUpdate;
			mutable Transform m_inverseTransform;
			mutable bool m_inverseTransformNeedUpdate;
		};
	}
}

#endif
