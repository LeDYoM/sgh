#ifndef __LIB_ELLIPSESHAPE_HPP__
#define __LIB_ELLIPSESHAPE_HPP__

#include <lib/include/types.hpp>
#include <SFML/Graphics.hpp>
#include "renderizable.hpp"

namespace lib
{
	namespace draw
	{
		class NodeShape : public Renderizable
		{
		public:
			enum class NodeMode : u8
			{
				Shape = 0,
				Sprite = 1,
			} _mode{ NodeMode::Shape };
			explicit NodeShape(const std::string &name, const vector2df& size, const u32 pointCount=4,const NodeMode mode=NodeMode::Shape);
			virtual ~NodeShape();
			void setSize(const lib::vector2df &size);
			void setSize(const float size);
			const lib::vector2df &getSize() const;
			u32 getPointCount() const;
			void setPointCount(lib::u32 numPoints);
			virtual lib::vector2df getPoint(lib::u32 index) const;
			void setTexture(const sf::Texture *texture, bool resetSize=true, bool resetRect = false);

			void setTextureRect(const Rects32& rect);
			virtual void setColor(const lib::draw::Color& color) override;
			const sf::Texture* getTexture() const;
			const Rects32& getTextureRect() const;
			const Color& getFillColor() const;
			const Color& getOutlineColor() const;
			float getOutlineThickness() const;
			Rectf32 getLocalBounds() const override;
			Rectf32 getGlobalBounds() const override;

		protected:
			void update();
			void setTexture_(const sf::Texture* texture, bool resetRect = false);
			virtual u32 draw(lib::core::Window *window, lib::draw::RenderStates &states) override;
			void updateFillColors();
			void updateTexCoords();

		private:
			const sf::Texture* m_texture;
			lib::vector2df _size;
			lib::u32 m_pointCount;
			Rects32 m_textureRect;
			lib::draw::Color m_fillColor;
			VertexArray m_vertices;
			Rectf32 m_bounds;
		};
	}
}

#endif
