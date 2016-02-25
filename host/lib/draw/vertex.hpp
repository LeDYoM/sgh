#ifndef LIB_DRAW_VERTEX_HPP
#define LIB_DRAW_VERTEX_HPP

#include <lib/include/types.hpp>
#include <lib/include/color.hpp>

namespace lib
{
	namespace draw
	{
		class Vertex
		{
		public:
			Vertex();
			Vertex(const vector2df &thePosition);
			Vertex(const vector2df &thePosition, const Color &theColor);
			Vertex(const vector2df &thePosition, const vector2df &theTexCoords);
			Vertex(const vector2df &thePosition, const Color &theColor, const vector2df &theTexCoords);

			vector2df position;
			Color color;
			vector2df texCoords;
		};
	}
}

#endif
