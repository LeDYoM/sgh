#ifndef __LIB_ELLIPSESHAPE_HPP__
#define __LIB_ELLIPSESHAPE_HPP__

#include <lib/include/types.hpp>
#include "rendernode.hpp"

namespace lib
{
	namespace drivers
	{
		namespace render
		{
			class Texture;
		}
	}
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
			explicit NodeShape(RenderGroup *const p_parent, const std::string &name, const vector2df& size, const u32 pointCount=4,const NodeMode mode=NodeMode::Shape);
			virtual ~NodeShape();
			void setSize(const lib::vector2df &size);
			void setSize(const float size);
			const lib::vector2df &getSize() const;
			u32 getPointCount() const;
			void setPointCount(lib::u32 numPoints);
			virtual vector2df getPoint(const u32 index) const;
			void setTexture(const str &textureId, bool resetSize=true, bool resetRect = false);

			void setTextureRect(const Rects32& rect);
			const Rects32& getTextureRect() const;

		protected:
			virtual void ensureGeometryUpdate() override;
			void setTexture_(const Texture* texture, bool resetRect = false);
			virtual void update() override;
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
