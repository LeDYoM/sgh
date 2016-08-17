#include "nodetext.hpp"
#include "lib/core/convops.hpp"
#include <lib/core/window.hpp>
#include <lib/core/appcontroller.hpp>

#include <SFML/Graphics/Font.hpp>

namespace lib
{
	namespace draw
	{
		NodeText::NodeText(RenderGroup *const p_parent, const std::string &name)
			: RenderNode{ p_parent, name, PrimitiveType::Triangles }, characterSize(30)
		{
			ensureGeometryUpdate();
		}

		NodeText::~NodeText() {	}

		vector2df NodeText::findCharacterPos(u32)
		{
			// Make sure that we have a valid font
//			if (!text().empty())
				return vector2df{};

				/*
			// Adjust the index if it's out of range
			if (index > text().length())
				index = text().length();

			// Pre compute the variables needed by the algorithm
			float hspace = static_cast<float>(m_font->getGlyph(L' ', characterSize, bold).advance);
			float vspace = static_cast<float>(m_font->getLineSpacing(characterSize));

			// Compute the position
			vector2df _position;
			u32 prevChar = 0;
			for (auto i = 0u; i < index; ++i)
			{
				u32 curChar = text()[i];

				// Apply the kerning offset
				_position.x += static_cast<float>(m_font->getKerning(prevChar, curChar, characterSize));
				prevChar = curChar;

				// Handle special characters
				switch (curChar)
				{
				case ' ':  _position.x += hspace;                  continue;
				case '\t': _position.x += hspace * 4;              continue;
				case '\n': _position.y += vspace; _position.x = 0; continue;
				}

				// For regular characters, add the advance offset of the glyph
				_position.x += static_cast<float>(m_font->getGlyph(curChar, characterSize, bold).advance);
			}

			// Transform the position to global coordinates
			_position = transformation().transformPoint(position());

			return _position;
			*/
		}

		void NodeText::update()
		{
			RenderNode::update();
			ensureGeometryUpdate();
		}

		void NodeText::ensureGeometryUpdate()
		{
			/*
			// Do nothing, if geometry has not changed
			if (!m_geometryNeedUpdate)
				return;

			// Mark geometry as updated
			m_geometryNeedUpdate = false;

			// Clear the previous geometry
			m_vertices.clear();
			m_bounds = Rectf32();

			// No font: nothing to draw
			if (fontId().empty)
				return;

			// No text: nothing to draw
			if (text().empty())
				return;

			// Compute the location of the strike through dynamically
			// We use the center point of the lowercase 'x' glyph as the reference
			// We reuse the underline thickness as the thickness of the strike through as well
			Rectf32 xBounds = convert(m_font->getGlyph(L'x', characterSize, bold).bounds);
			f32 strikeThroughOffset = xBounds.top + xBounds.height / 2.f;

			// Pre-compute the variables needed by the algorithm
			f32 hspace = static_cast<f32>(m_font->getGlyph(L' ', characterSize, bold).advance);
			f32 vspace = static_cast<f32>(m_font->getLineSpacing(characterSize));
			f32 x = 0.f;
			f32 y = static_cast<f32>(characterSize());

			// Create one quad for each character
			f32 minX = static_cast<f32>(characterSize());
			f32 minY = minX;
			f32 maxX = 0.f;
			f32 maxY = 0.f;
			u32 prevChar = 0;
			for (u32 i = 0u; i < text().size(); ++i)
			{
				u32 curChar = text()[i];

				// Apply the kerning offset
				x += static_cast<float>(m_font->getKerning(prevChar, curChar, characterSize()));
				prevChar = curChar;

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
				const sf::Glyph& glyph = m_font->getGlyph(curChar, characterSize, bold);

				f32 left = glyph.bounds.left;
				f32 top = glyph.bounds.top;
				f32 right = glyph.bounds.left + glyph.bounds.width;
				f32 bottom = glyph.bounds.top + glyph.bounds.height;

				f32 u1 = static_cast<f32>(glyph.textureRect.left);
				f32 v1 = static_cast<f32>(glyph.textureRect.top);
				f32 u2 = static_cast<f32>(glyph.textureRect.left + glyph.textureRect.width);
				f32 v2 = static_cast<f32>(glyph.textureRect.top + glyph.textureRect.height);

				// Add a quad for the current character
				m_vertices.append(Vertex(vector2df(x + left, y + top), color(), vector2df(u1, v1)));
				m_vertices.append(Vertex(vector2df(x + right, y + top), color(), vector2df(u2, v1)));
				m_vertices.append(Vertex(vector2df(x + left, y + bottom), color(), vector2df(u1, v2)));
				m_vertices.append(Vertex(vector2df(x + left, y + bottom), color(), vector2df(u1, v2)));
				m_vertices.append(Vertex(vector2df(x + right, y + top), color(), vector2df(u2, v1)));
				m_vertices.append(Vertex(vector2df(x + right, y + bottom), color(), vector2df(u2, v2)));

				// Update the current bounds
				minX = std::min(minX, x + left);
				maxX = std::max(maxX, x + right);
				minY = std::min(minY, y + top);
				maxY = std::max(maxY, y + bottom);

				// Advance to the next character
				x += glyph.advance;
			}

			// Update the bounding rectangle
			m_bounds.left = minX;
			m_bounds.top = minY;
			m_bounds.width = maxX - minX;
			m_bounds.height = maxY - minY;
			*/
		}
	}
}
