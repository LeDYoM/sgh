#ifndef LIB_RENDERMANAGER_HPP__
#define LIB_RENDERMANAGER_HPP__

#include <lib/include/types.hpp>
#include <lib/core/appservice.hpp>
#include "renderstates.hpp"

namespace lib
{
	namespace draw
	{
		class RenderManager : public AppService
		{
		public:
			RenderManager();
			virtual ~RenderManager();

			static const str staticTypeName() { return "RenderManager"; }

			virtual void Init() override;
		};
	}
}

#endif
