#ifndef LIB_DRAW_VIEW_HPP
#define LIB_DRAW_VIEW_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Vector2.hpp>

#include <lib/include/rect.hpp>

using namespace sf;
namespace lib
{
	namespace draw
	{
		class View
		{
		public:

			View();

			explicit View(const FloatRect& rectangle);
			View(const Vector2f& center, const Vector2f& size);
			void setCenter(float x, float y);
			void setCenter(const Vector2f& center);
			void setSize(float width, float height);
			void setSize(const Vector2f& size);
			void setRotation(float angle);
			void setViewport(const FloatRect& viewport);
			void reset(const FloatRect& rectangle);
			const Vector2f& getCenter() const;
			const Vector2f& getSize() const;
			float getRotation() const;
			const FloatRect& getViewport() const;
			void move(float offsetX, float offsetY);
			void move(const Vector2f& offset);
			void rotate(float angle);
			void zoom(float factor);
			const Transform& getTransform() const;
			const Transform& getInverseTransform() const;

		private:
			Vector2f          m_center;
			Vector2f          m_size;
			float             m_rotation;
			FloatRect         m_viewport;
			mutable Transform m_transform;
			mutable Transform m_inverseTransform;
			mutable bool      m_transformUpdated;
			mutable bool      m_invTransformUpdated;
		};
	}
}

#endif
