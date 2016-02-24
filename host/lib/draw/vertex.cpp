#include "vertex.hpp"

namespace lib
{
	namespace draw
	{
		Vertex::Vertex() 
			: position{ 0, 0 }, color{ 255, 255, 255 }, texCoords{ 0, 0 } {}

		Vertex::Vertex(const vector2df &thePosition)
			: Vertex{ thePosition, { 255, 255, 255 }, { 0, 0 } } {}

		Vertex::Vertex(const vector2df &thePosition, const Color& theColor)
			: Vertex{ thePosition, { theColor }, { 0, 0 } } {}

		Vertex::Vertex(const vector2df &thePosition, const vector2df &theTexCoords)
			: Vertex{ thePosition, { 255, 255, 255 }, { theTexCoords } } {}

		Vertex::Vertex(const vector2df &thePosition, const Color& theColor, const vector2df &theTexCoords)
			: position{ thePosition }, color{ theColor }, texCoords{ theTexCoords } {}
	}
}
