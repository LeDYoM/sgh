#ifndef __LIB_INAMEDDRAWABLE_HPP__
#define __LIB_INAMEDDRAWABLE_HPP__

#include <lib/core/obj.hpp>
#include "hasname.hpp"
#include "idrawable.hpp"
#include "iparentable.hpp"

namespace lib
{
	namespace draw
	{
		class RenderGroup;
		class Node : public IParentable<RenderGroup>, public core::HasName, public IDrawable, public Object
		{
		public:
			Node(const str &name);
			virtual bool init();
			virtual ~Node();
		};
	}
}

#endif
