#include "scene.hpp"
#include "scenemanager.hpp"
#include "RenderNode.hpp"
#include <lib/core/log.hpp>
#include <lib/core/window.hpp>
#include <lib/core/appcontroller.hpp>
#include <lib/core/resourcemanager.hpp>
#include "camera.hpp"

namespace lib
{
	namespace draw
	{
		Scene::Scene(const std::string &_name) : RenderGroup{ _name, nullptr }
		{
			LOG_CONSTRUCT("Name: " + name());
			sceneHandle = new SceneHandle;
		}

		Scene::~Scene()
		{
			LOG_DESTRUCT("Name: " + name());
			delete sceneHandle;
		}

		void SceneHandle::updateView()
		{
			p_scnManager->appController()->parentWindow()->updateCamera(m_camera);
		}

		const vector2df SceneHandle::getCoordinatesToCenter(const Rectf32 &coordinates) const
		{
			return{ m_camera.target().center().x - (coordinates.width / 2.0f), m_camera.target().center().y - (coordinates.height / 2.0f) };
		}

		void Scene::privateOnInit()
		{
			LOG_DEBUG("Initializing scene " << name());
			auto sceneSize = getDefaultSizeView();
			sceneHandle->m_camera.setSize(sceneSize);
			sceneHandle->updateView();
			onInit();
		}

		void Scene::privateOnDeinit()
		{
			LOG_DEBUG("Deinitializing scene " << name());
			onDeinit();
		}

		void Scene::privateOnEnterScene()
		{
			LOG_DEBUG("Entered in scene " << name());
			auto sceneSize = getDefaultSizeView();
			sceneHandle->m_camera.setSize(sceneSize);
			//			m_view.setCenter(sceneSize.x / 2, sceneSize.y / 2);
			sceneHandle->updateView();

			LOG_DEBUG("Scene camera set to: center: " << sceneHandle->m_camera.target().center().x << "," << sceneHandle->m_camera.target().center().y << " and size: " << sceneHandle->m_camera.target().width << "," << sceneHandle->m_camera.target().height);

			clock.restart();
			onEnterScene();
		}

		lib::vector2df SceneHandle::pointViewToCurrentView(const vector2df &point, const vector2df &size) const
		{
			return{ (m_camera.target().width * point.x) / size.x, (camera().target().height * point.y) / size.y };
		}

		void Scene::privateOnExitScene()
		{
			onExitScene();
			LOG_DEBUG("Exited from scene " << name());
		}

		void Scene::onKeyPressed(input::Key key)
		{
			LOG_DEBUG("Key pressed: " << int{ key.kCode });
		}

		void Scene::onKeyReleased(input::Key key)
		{
			LOG_DEBUG("Key released: " << int{ key.kCode });
		}

		void Scene::setNextScene(const std::string &name)
		{
			__ASSERT(sceneHandle->p_scnManager, "Null SceneManager on Scene");
			sceneHandle->p_scnManager->setScene(name);
		}

		uptr<core::ResourceManager> const &SceneHandle::resourceManager()
		{
			return p_scnManager->appController()->resourceManager();
		}

		uptr<util::UtilProvider> const & SceneHandle::utilProvider()
		{
			return p_scnManager->appController()->utilProvider();
		}

		void Scene::exitProgram()
		{
			sceneHandle->p_scnManager->exitProgram();
		}
	}
}
