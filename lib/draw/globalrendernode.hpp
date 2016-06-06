#ifndef LIB_DRAW_GLOBALRENDERNODE_HPP
#define LIB_DRAW_GLOBALRENDERNODE_HPP

#include "scenenode.hpp"
#include <lib/include/types.hpp>
#include <lib/include/color.hpp>
#include <lib/include/properties.hpp>
#include "vertexarray.hpp"

namespace sf
{
	class Texture;
	class Shader;
	struct BlendMode;
}

namespace lib
{
	namespace draw
	{
		class GlobalRenderNode
		{
		public:
			explicit GlobalRenderNode();
			virtual ~GlobalRenderNode();

			sf::Texture *texture{ nullptr };
			sf::Shader *shader{ nullptr };
			sf::BlendMode *blendMode{ nullptr };
			VertexArray vertices{  };


		};
	}
}

#endif
