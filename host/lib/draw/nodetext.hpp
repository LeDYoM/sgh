#ifndef _LIB_NODETEXT_HPP__
#define _LIB_NODETEXT_HPP__

#include <SFML/Graphics/Font.hpp>
#include "vertexarray.hpp"
#include <string>
#include <vector>

#include "renderizable.hpp"

namespace lib
{
	namespace draw
	{
		class NodeText : public lib::draw::Renderizable
		{
		public:
			enum Style
			{
				Regular = 0,
				Bold = 1 << 0,
				Italic = 1 << 1,
				Underlined = 1 << 2,
				StrikeThrough = 1 << 3
			};

			NodeText(const std::string &name);
			NodeText(const std::string &name, const sf::String& string, const sf::Font& font, u32 characterSize = 30);
			virtual ~NodeText();
			void setString(const std::string &string);
			void setFont(const sf::Font& font);
			void setCharacterSize(u32 size);
			void setStyle(u32 style);
			void setColor(const Color& color);
			const std::string &getString() const;
			const sf::Font* getFont() const;
			u32 getCharacterSize() const;
			u32 getStyle() const;
			const Color& getColor() const;
			vector2df findCharacterPos(u32 index);
			Rectf32 getLocalBounds() override;
			Rectf32 getGlobalBounds() override;
		private:
			virtual u32 draw(RenderStates &states) override;
			void ensureGeometryUpdate();

			std::string m_string;
			const sf::Font* m_font;
			u32 m_characterSize;
			u32 m_style;
			Color m_color;
			VertexArray m_vertices;
			Rectf32 m_bounds;
			bool m_geometryNeedUpdate;
		};
	}
}

#endif
