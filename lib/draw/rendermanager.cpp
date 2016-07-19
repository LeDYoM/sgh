#include "rendermanager.hpp"

#include <lib/core/log.hpp>

#include "transformation.hpp"
#include "renderstates.hpp"
#include "rendernode.hpp"
#include "camera.hpp"

#include <lib/drivers/render/rendertarget.hpp>
#include <lib/core/appcontroller.hpp>
#include <lib/core/driver.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

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
			m_renderList.clear();
			LOG_DESTRUCT_NOPARAMS;
		}

		void RenderManager::Init()
		{
			AppService::Init();
		}

		void RenderManager::startFrame(sptr<drivers::render::RenderTarget> renderTarget, sptr<Camera> camera)
		{
			m_renderTarget = renderTarget;
			m_camera = camera;
		}

		void RenderManager::finishFrame()
		{
			lib::drivers::render::RenderTarget *renderTarget{ m_renderTarget.get() };
			renderTarget->setView(m_camera->view(), m_camera->getViewport());
			for (const RenderNode*node : m_renderList)
			{
				renderTarget->draw(node);
			}

			m_renderList.clear();
		}

		void RenderManager::preRenderNode(const sptr<RenderNode> &node)
		{
//			m_renderTarget->draw(node);
			m_renderList.push_back(node.get());
		}
	}
}
