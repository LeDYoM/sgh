#ifndef LIB_TRANSFORMABLE_HPP
#define LIB_TRANSFORMABLE_HPP

#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Transform.hpp>

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

			void setPosition(float x, float y);
			void setPosition(const Vector2f& position);
			void setRotation(float angle);

			void setScale(float factorX, float factorY);
			void setScale(const Vector2f& factors);
			void setOrigin(float x, float y);
			void setOrigin(const Vector2f& origin);
			const Vector2f& getPosition() const;
			float getRotation() const;
			const Vector2f& getScale() const;
			const Vector2f& getOrigin() const;
			void move(float offsetX, float offsetY);
			void move(const Vector2f& offset);
			void rotate(float angle);
			void scale(float factorX, float factorY);
			void scale(const Vector2f& factor);
			const Transform& getTransform() const;

			const Transform& getInverseTransform() const;

		private:

			Vector2f          m_origin;                     ///< Origin of translation/rotation/scaling of the object
			Vector2f          m_position;                   ///< Position of the object in the 2D world
			float             m_rotation;                   ///< Orientation of the object, in degrees
			Vector2f          m_scale;                      ///< Scale of the object
			mutable Transform m_transform;                  ///< Combined transformation of the object
			mutable bool      m_transformNeedUpdate;        ///< Does the transform need to be recomputed?
			mutable Transform m_inverseTransform;           ///< Combined transformation of the object
			mutable bool      m_inverseTransformNeedUpdate; ///< Does the transform need to be recomputed?
		};
	}
}

#endif
