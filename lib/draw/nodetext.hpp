#ifndef _LIB_NODETEXT_HPP__
#define _LIB_NODETEXT_HPP__

#include "rendernode.hpp"
#include <lib/include/properties.hpp>

namespace lib
{
	namespace draw
	{
		enum class Alignment : u8
		{
			Left = 0,
			Center = 1,
			Right = 2
		};

		class NodeText : public RenderNode
		{
		public:
			NodeText(RenderGroup *const p_parent, const std::string &name);
			virtual ~NodeText();

			Property<str> fontId;
			Property<str> text;
			Property<Alignment> alignment;
			Property<u32> characterSize;
			vector2df findCharacterPos(u32 index);
		private:
			virtual void update() override;
			virtual void ensureGeometryUpdate() override;
		};
	}
}

#endif
