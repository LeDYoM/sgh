#ifndef LIB_DRAW_RENDERSTATES_HPP
#define LIB_DRAW_RENDERSTATES_HPP

#include <lib/include/types.hpp>

namespace lib
{
	namespace draw
	{
		class RenderStates;
	}
	namespace core
	{
		class SystemState
		{
		public:
			SystemState();
			SystemState&operator=(const SystemState&) = delete;

			sptr<draw::RenderStates> renderStates() const { return m_renderStates; }
		private:
			sptr<draw::RenderStates> m_renderStates;
		};
	}
}

#endif
