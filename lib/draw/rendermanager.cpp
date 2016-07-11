#include "rendermanager.hpp"
#include "transformation.hpp"
#include <lib/core/log.hpp>
#include "renderstates.hpp"
#include "rendernode.hpp"
#include "camera.hpp"
#include <lib/drivers/render/rendertarget.hpp>
#include <lib/core/appcontroller.hpp>
#include <lib/core/driver.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
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
			m_renderTarget->setView(m_camera->view(), m_camera->getViewport());
		}

		void RenderManager::finishFrame()
		{

		}

		void RenderManager::preRenderNode(const sptr<RenderNode> &node, const RenderStates &rStates) const
		{
			m_renderTarget->draw(node->vertexArray(), rStates);
		}

		void RenderManager::preRenderNode(const sptr<RenderNode> &node)
		{
			m_renderList.push_back(node.get());
		}
	}
}
