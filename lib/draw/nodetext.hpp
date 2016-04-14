#ifndef _LIB_NODETEXT_HPP__
#define _LIB_NODETEXT_HPP__

#include <SFML/Graphics/Font.hpp>
#include <string>
#include <vector>

#include "rendernode.hpp"

namespace lib
{
	namespace draw
	{
		class NodeText : public lib::draw::RenderNode
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
			const std::string &getString() const;
			const sf::Font* getFont() const;
			u32 getCharacterSize() const;
			u32 getStyle() const;
			vector2df findCharacterPos(u32 index);
		private:
			virtual u32 draw(RenderStates &states) override;
			virtual void ensureGeometryUpdate() override;

			std::string m_string;
			const sf::Font* m_font;
			u32 m_characterSize;
			u32 m_style;
		};
	}
}

#endif
