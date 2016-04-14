#ifndef __LIB_INAMEDDRAWABLE_HPP__
#define __LIB_INAMEDDRAWABLE_HPP__

#include <lib/include/types.hpp>
#include <lib/core/obj.hpp>
#include "hasname.hpp"
#include "idrawable.hpp"

namespace lib
{
	namespace draw
	{
		class Node : public core::HasName, public IDrawable, public Object
		{
		public:
			Node(const str &name) : HasName(name), IDrawable{}, Object{} {}
			virtual ~Node() {}
		};
	}
}

#endif
