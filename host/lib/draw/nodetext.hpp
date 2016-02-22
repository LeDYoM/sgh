#ifndef _LIB_NODETEXT_HPP__
#define _LIB_NODETEXT_HPP__

#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>
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
			vector2df findCharacterPos(u32 index) const;
			Rectf32 getLocalBounds() const;
			Rectf32 getGlobalBounds() const;
		private:
			virtual u32 draw(lib::core::Window *window, RenderStates &states) override;
			void ensureGeometryUpdate() const;

			std::string m_string;
			const sf::Font* m_font;
			u32 m_characterSize;
			u32 m_style;
			Color m_color;
			mutable VertexArray m_vertices;
			mutable Rectf32 m_bounds;
			mutable bool m_geometryNeedUpdate;
		};
	}
}

#endif
