#include "globalrendernode.hpp"
#include <lib/core/window.hpp>
#include <lib/core/log.hpp>

namespace lib
{
	namespace draw
	{
		GlobalRenderNode::GlobalRenderNode(RenderNode *generatedFrom)
		{
			LOG_CONSTRUCT_NOPARAMS;
		}

		GlobalRenderNode::~GlobalRenderNode()
		{
		}
	}
}
