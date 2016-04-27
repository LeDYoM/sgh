#ifndef LIB_NODE_HPP__
#define LIB_NODE_HPP__

#include <lib/core/obj.hpp>
#include "hasname.hpp"
#include "iparentable.hpp"

namespace lib
{
	namespace draw
	{
		class RenderGroup;
		class Node : public IParentable<RenderGroup>, public core::HasName, public virtual Object
		{
		public:
			Node(const str &name);
			virtual bool init();
			virtual ~Node();

			inline void setActive(bool nv) { m_active = nv; }
			inline const bool isActive() const { return m_active; }

			inline void setVisible(bool nv) { m_visible = nv; }
			inline const bool isVisible() const { return m_visible; }

		private:
			bool m_active{ true };
			bool m_visible{ true };
		
		};
	
	}
}

#endif
