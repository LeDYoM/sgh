#ifndef __LIB_INAMEDDRAWABLE_HPP__
#define __LIB_INAMEDDRAWABLE_HPP__

#include <lib/include/types.hpp>
#include "hasname.hpp"
#include "idrawable.hpp"

namespace lib
{
	namespace draw
	{
		class Node : public core::HasName, public IDrawable
		{
		public:
			Node(const str &name) : HasName(name), IDrawable{} {}
			virtual ~Node() {}
		};
	}
}

#endif
