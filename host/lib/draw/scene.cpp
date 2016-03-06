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
			LOG_CONSTRUCT("Name: " << name());
		}

		Scene::~Scene()
		{
			LOG_DESTRUCT("Name: " << name());
		}

		void Scene::updateView()
		{
			p_scnManager->appController()->parentWindow()->updateCamera(m_camera);
		}

		const vector2df Scene::getCoordinatesToCenter(const Rectf32 &coordinates) const
		{
			return{ m_camera.target().center().x - (coordinates.width / 2.0f), m_camera.target().center().y - (coordinates.height / 2.0f) };
		}

		void Scene::privateOnInit()
		{
			LOG_DEBUG("Initializing scene " << name());
			auto sceneSize = getDefaultSizeView();
			m_camera.setSize(sceneSize);
			updateView();
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
			m_camera.setSize(sceneSize);
			//			m_view.setCenter(sceneSize.x / 2, sceneSize.y / 2);
			updateView();

			LOG_DEBUG("Scene camera set to: center: " << m_camera.target().center().x << "," << m_camera.target().center().y << " and size: " << m_camera.target().width << "," << m_camera.target().height);

			clock.restart();
			onEnterScene();
		}

		lib::vector2df Scene::pointViewToCurrentView(const vector2df &point, const vector2df &size) const
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
			__ASSERT(p_scnManager, "Null SceneManager on Scene");
			p_scnManager->setScene(name);
		}

		uptr<core::ResourceManager> const &Scene::resourceManager()
		{
			return p_scnManager->appController()->resourceManager();
		}

		uptr<util::UtilProvider> const & Scene::utilProvider()
		{
			return p_scnManager->appController()->utilProvider();
		}

		void Scene::exitProgram()
		{
			p_scnManager->exitProgram();
		}
	}
}
