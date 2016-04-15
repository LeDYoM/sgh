#ifndef __LIB_ELLIPSESHAPE_HPP__
#define __LIB_ELLIPSESHAPE_HPP__

#include <lib/include/types.hpp>
#include "rendernode.hpp"

namespace lib
{
	namespace draw
	{
		class NodeShape : public RenderNode
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
			const sf::Texture* getTexture() const;
			const Rects32& getTextureRect() const;

		protected:
			virtual void ensureGeometryUpdate() override;
			void setTexture_(const sf::Texture* texture, bool resetRect = false);
			virtual u32 draw() override;
			void updateTexCoords();

		private:
			const sf::Texture* m_texture;
			lib::vector2df _size;
			lib::u32 m_pointCount;
			Rects32 m_textureRect;
		};
	}
}

#endif
