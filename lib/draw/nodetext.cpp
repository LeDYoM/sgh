#include "nodetext.hpp"
#include "lib/core/convops.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <lib/core/window.hpp>
#include <lib/core/rendertarget.hpp>
#include "scenemanager.hpp"
#include "../core/appcontroller.hpp"

namespace lib
{
	namespace draw
	{
		NodeText::NodeText(const std::string &name)
			: RenderNode{ name, PrimitiveType::Triangles }, m_string(), m_font(nullptr), m_characterSize(30), m_style(Regular)
		{
			ensureGeometryUpdate();
		}

		NodeText::NodeText(const std::string &name, const sf::String& string, const sf::Font& font, unsigned int characterSize) :
			RenderNode{ name, PrimitiveType::Triangles }, m_string(string), m_font(&font), m_characterSize(characterSize), m_style(Regular)
		{
		}

		NodeText::~NodeText() {	}

		void NodeText::setString(const std::string &string)
		{
			if (m_string != string)
			{
				m_string = string;
				m_geometryNeedUpdate = true;
			}
		}

		void NodeText::setFont(const sf::Font &font)
		{
			if (m_font != &font)
			{
				m_font = &font;
				m_geometryNeedUpdate = true;
			}
		}

		void NodeText::setCharacterSize(u32 size)
		{
			if (m_characterSize != size)
			{
				m_characterSize = size;
				m_geometryNeedUpdate = true;
			}
		}

		void NodeText::setStyle(u32 style)
		{
			if (m_style != style)
			{
				m_style = style;
				m_geometryNeedUpdate = true;
			}
		}

		const std::string &NodeText::getString() const
		{
			return m_string;
		}

		const sf::Font *NodeText::getFont() const
		{
			return m_font;
		}

		u32 NodeText::getCharacterSize() const
		{
			return m_characterSize;
		}

		u32 NodeText::getStyle() const
		{
			return m_style;
		}

		vector2df NodeText::findCharacterPos(u32 index)
		{
			// Make sure that we have a valid font
			if (!m_font)
				return lib::vector2df();

			// Adjust the index if it's out of range
			if (index > m_string.length())
				index = m_string.length();

			// Pre compute the variables needed by the algorithm
			bool  bold = (m_style & Bold) != 0;
			float hspace = static_cast<float>(m_font->getGlyph(L' ', m_characterSize, bold).advance);
			float vspace = static_cast<float>(m_font->getLineSpacing(m_characterSize));

			// Compute the position
			vector2df position;
			u32 prevChar = 0;
			for (auto i = 0u; i < index; ++i)
			{
				u32 curChar = m_string[i];

				// Apply the kerning offset
				position.x += static_cast<float>(m_font->getKerning(prevChar, curChar, m_characterSize));
				prevChar = curChar;

				// Handle special characters
				switch (curChar)
				{
				case ' ':  position.x += hspace;                 continue;
				case '\t': position.x += hspace * 4;             continue;
				case '\n': position.y += vspace; position.x = 0; continue;
				}

				// For regular characters, add the advance offset of the glyph
				position.x += static_cast<float>(m_font->getGlyph(curChar, m_characterSize, bold).advance);
			}

			// Transform the position to global coordinates
			position = transformation().transformPoint(position);

			return position;
		}

		const sf::Texture *NodeText::texture() const
		{
			return &(m_font->getTexture(m_characterSize));
		}

		u32 NodeText::draw()
		{
			if (m_font)
			{
				ensureGeometryUpdate();
//				RenderStates states{ top.blendMode,top.transform*transformableNode->transformation(),top.texture,top.shader };
//				auto oldTransformation = states.transform;
//				states.transform *= transformation();
//				states.texture = &m_font->getTexture(m_characterSize);
//				states.currentTarget->draw(m_vertices, states);
//				states.transform = oldTransformation;
				return 1;
			}
			return 0;
		}

		void NodeText::ensureGeometryUpdate()
		{
			// Do nothing, if geometry has not changed
			if (!m_geometryNeedUpdate)
				return;

			// Mark geometry as updated
			m_geometryNeedUpdate = false;

			// Clear the previous geometry
			m_vertices.clear();
			m_bounds = Rectf32();

			// No font: nothing to draw
			if (!m_font)
				return;

			// No text: nothing to draw
			if (m_string.empty())
				return;

			// Compute values related to the text style
			bool  bold = (m_style & Bold) != 0;
			bool  underlined = (m_style & Underlined) != 0;
			bool  strikeThrough = (m_style & StrikeThrough) != 0;
			f32 italic = (m_style & Italic) ? 0.208f : 0.f; // 12 degrees
			f32 underlineOffset = m_font->getUnderlinePosition(m_characterSize);
			f32 underlineThickness = m_font->getUnderlineThickness(m_characterSize);

			// Compute the location of the strike through dynamically
			// We use the center point of the lowercase 'x' glyph as the reference
			// We reuse the underline thickness as the thickness of the strike through as well
			Rectf32 xBounds = convert(m_font->getGlyph(L'x', m_characterSize, bold).bounds);
			f32 strikeThroughOffset = xBounds.top + xBounds.height / 2.f;

			// Pre-compute the variables needed by the algorithm
			f32 hspace = static_cast<f32>(m_font->getGlyph(L' ', m_characterSize, bold).advance);
			f32 vspace = static_cast<f32>(m_font->getLineSpacing(m_characterSize));
			f32 x = 0.f;
			f32 y = static_cast<f32>(m_characterSize);

			// Create one quad for each character
			f32 minX = static_cast<f32>(m_characterSize);
			f32 minY = static_cast<f32>(m_characterSize);
			f32 maxX = 0.f;
			f32 maxY = 0.f;
			u32 prevChar = 0;
			for (u32 i = 0u; i < m_string.length(); ++i)
			{
				u32 curChar = m_string[i];

				// Apply the kerning offset
				x += static_cast<float>(m_font->getKerning(prevChar, curChar, m_characterSize));
				prevChar = curChar;

				// If we're using the underlined style and there's a new line, draw a line
				if (underlined && (curChar == L'\n'))
				{
					float top = std::floor(y + underlineOffset - (underlineThickness / 2) + 0.5f);
					float bottom = top + std::floor(underlineThickness + 0.5f);

					m_vertices.append(Vertex(vector2df(0, top), m_color, vector2df(1, 1)));
					m_vertices.append(Vertex(vector2df(x, top), m_color, vector2df(1, 1)));
					m_vertices.append(Vertex(vector2df(0, bottom), m_color, vector2df(1, 1)));
					m_vertices.append(Vertex(vector2df(0, bottom), m_color, vector2df(1, 1)));
					m_vertices.append(Vertex(vector2df(x, top), m_color, vector2df(1, 1)));
					m_vertices.append(Vertex(vector2df(x, bottom), m_color, vector2df(1, 1)));
				}

				// If we're using the strike through style and there's a new line, draw a line across all characters
				if (strikeThrough && (curChar == L'\n'))
				{
					float top = std::floor(y + strikeThroughOffset - (underlineThickness / 2) + 0.5f);
					float bottom = top + std::floor(underlineThickness + 0.5f);

					m_vertices.append(Vertex(vector2df(0, top), m_color, vector2df(1, 1)));
					m_vertices.append(Vertex(vector2df(x, top), m_color, vector2df(1, 1)));
					m_vertices.append(Vertex(vector2df(0, bottom), m_color, vector2df(1, 1)));
					m_vertices.append(Vertex(vector2df(0, bottom), m_color, vector2df(1, 1)));
					m_vertices.append(Vertex(vector2df(x, top), m_color, vector2df(1, 1)));
					m_vertices.append(Vertex(vector2df(x, bottom), m_color, vector2df(1, 1)));
				}

				// Handle special characters
				if ((curChar == ' ') || (curChar == '\t') || (curChar == '\n'))
				{
					// Update the current bounds (min coordinates)
					minX = std::min(minX, x);
					minY = std::min(minY, y);

					switch (curChar)
					{
					case ' ':  x += hspace;        break;
					case '\t': x += hspace * 4;    break;
					case '\n': y += vspace; x = 0; break;
					}

					// Update the current bounds (max coordinates)
					maxX = std::max(maxX, x);
					maxY = std::max(maxY, y);

					// Next glyph, no need to create a quad for whitespace
					continue;
				}

				// Extract the current glyph's description
				const sf::Glyph& glyph = m_font->getGlyph(curChar, m_characterSize, bold);

				f32 left = glyph.bounds.left;
				f32 top = glyph.bounds.top;
				f32 right = glyph.bounds.left + glyph.bounds.width;
				f32 bottom = glyph.bounds.top + glyph.bounds.height;

				f32 u1 = static_cast<f32>(glyph.textureRect.left);
				f32 v1 = static_cast<f32>(glyph.textureRect.top);
				f32 u2 = static_cast<f32>(glyph.textureRect.left + glyph.textureRect.width);
				f32 v2 = static_cast<f32>(glyph.textureRect.top + glyph.textureRect.height);

				// Add a quad for the current character
				m_vertices.append(Vertex(vector2df(x + left - italic * top, y + top), m_color, vector2df(u1, v1)));
				m_vertices.append(Vertex(vector2df(x + right - italic * top, y + top), m_color, vector2df(u2, v1)));
				m_vertices.append(Vertex(vector2df(x + left - italic * bottom, y + bottom), m_color, vector2df(u1, v2)));
				m_vertices.append(Vertex(vector2df(x + left - italic * bottom, y + bottom), m_color, vector2df(u1, v2)));
				m_vertices.append(Vertex(vector2df(x + right - italic * top, y + top), m_color, vector2df(u2, v1)));
				m_vertices.append(Vertex(vector2df(x + right - italic * bottom, y + bottom), m_color, vector2df(u2, v2)));

				// Update the current bounds
				minX = std::min(minX, x + left - italic * bottom);
				maxX = std::max(maxX, x + right - italic * top);
				minY = std::min(minY, y + top);
				maxY = std::max(maxY, y + bottom);

				// Advance to the next character
				x += glyph.advance;
			}

			// If we're using the underlined style, add the last line
			if (underlined)
			{
				f32 top = std::floor(y + underlineOffset - (underlineThickness / 2) + 0.5f);
				f32 bottom = top + std::floor(underlineThickness + 0.5f);

				m_vertices.append(Vertex(vector2df(0, top), m_color, vector2df(1, 1)));
				m_vertices.append(Vertex(vector2df(x, top), m_color, vector2df(1, 1)));
				m_vertices.append(Vertex(vector2df(0, bottom), m_color, vector2df(1, 1)));
				m_vertices.append(Vertex(vector2df(0, bottom), m_color, vector2df(1, 1)));
				m_vertices.append(Vertex(vector2df(x, top), m_color, vector2df(1, 1)));
				m_vertices.append(Vertex(vector2df(x, bottom), m_color, vector2df(1, 1)));
			}

			// If we're using the strike through style, add the last line across all characters
			if (strikeThrough)
			{
				f32 top = std::floor(y + strikeThroughOffset - (underlineThickness / 2) + 0.5f);
				f32 bottom = top + std::floor(underlineThickness + 0.5f);

				m_vertices.append(Vertex(vector2df(0, top), m_color, vector2df(1, 1)));
				m_vertices.append(Vertex(vector2df(x, top), m_color, vector2df(1, 1)));
				m_vertices.append(Vertex(vector2df(0, bottom), m_color, vector2df(1, 1)));
				m_vertices.append(Vertex(vector2df(0, bottom), m_color, vector2df(1, 1)));
				m_vertices.append(Vertex(vector2df(x, top), m_color, vector2df(1, 1)));
				m_vertices.append(Vertex(vector2df(x, bottom), m_color, vector2df(1, 1)));
			}

			// Update the bounding rectangle
			m_bounds.left = minX;
			m_bounds.top = minY;
			m_bounds.width = maxX - minX;
			m_bounds.height = maxY - minY;
		}
	}
}
