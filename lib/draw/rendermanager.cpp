#include "rendermanager.hpp"
#include <lib/core/log.hpp>
#include "renderstates.hpp"
#include "rendernode.hpp"
#include <lib/core/rendertarget.hpp>

namespace lib
{
	namespace draw
	{

		RenderManager::RenderManager()
		{
			LOG_CONSTRUCT_NOPARAMS;
		}

		RenderManager::~RenderManager()
		{
			LOG_DESTRUCT_NOPARAMS;
		}

		void RenderManager::Init()
		{
			AppService::Init();
		}

		void RenderManager::startFrame()
		{

		}

		void RenderManager::finishFrame()
		{

		}

		void RenderManager::preRenderNode(const sptr<RenderNode> &node, const RenderStates &rStates)
		{

			rStates.currentTarget->draw(node->vertexArray(), rStates);
		}

		void RenderManager::preRenderNode(const sptr<RenderNode> &node)
		{
			m_renderList.push_back(node.get());
//			rStates.currentTarget->draw(node->vertexArray(), rStates);
		}

		void RenderManager::renderAll()
		{
			for (auto node : m_renderList)
			{
				renderTarget.get()->draw(node->vertexArray());
			}
		}

	}
}
