#include "scene.hpp"
#include "scenemanager.hpp"
#include "RenderNode.hpp"
#include <lib/core/log.hpp>
#include <lib/core/window.hpp>
#include <lib/core/appcontroller.hpp>
#include <lib/core/resourcemanager.hpp>
#include "camera.hpp"
#include <lib/core/events/eventclient.hpp>

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
			m_eventClient = sceneHandle->p_scnManager->eventClient()->newEventClient();
			m_eventClient->setReceiver([this](lib::core::events::EventClient::ReceivedEvent event_)
			{
				auto evKey = lib::core::events::getEventAs<core::events::KeyEvent>(event_);
				switch (evKey->action())
				{
				case core::events::KeyEvent::Action::KeyPressed:
					this->onPrivateKeyPressed(evKey->key());
					break;
				case core::events::KeyEvent::Action::KeyReleased:
					this->onPrivateKeyReleased(evKey->key());
					break;
				default:
					LOG_WARNING("Unknown Action on event key");
					break;
				}
			});

			m_eventClient->setActive(false);

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

			sceneHandle->clock.restart();
			m_eventClient->setActive(true);
			onEnterScene();
		}

		lib::vector2df SceneHandle::pointViewToCurrentView(const vector2df &point, const vector2df &size) const
		{
			return{ (m_camera.target().width * point.x) / size.x, (camera().target().height * point.y) / size.y };
		}

		void Scene::privateOnExitScene()
		{
			m_eventClient->setActive(false);
			onExitScene();
			LOG_DEBUG("Exited from scene " << name());
		}

		void Scene::onPrivateKeyPressed(input::Key key)
		{
			LOG_DEBUG("Key pressed: " << int{ key.kCode });
			onKeyPressed(key);
		}

		void Scene::onPrivateKeyReleased(input::Key key)
		{
			LOG_DEBUG("Key released: " << int{ key.kCode });
			onKeyReleased(key);
		}

		sptr<core::events::EventClient> Scene::eventClient() const
		{
			return m_eventClient;
		}

		void SceneHandle::setNextScene(const std::string &name)
		{
			__ASSERT(p_scnManager, "Null SceneManager on Scene");
			p_scnManager->setScene(name);
		}

		uptr<core::ResourceManager> const &SceneHandle::resourceManager()
		{
			return p_scnManager->appController()->resourceManager();
		}

		uptr<util::UtilProvider> const & SceneHandle::utilProvider()
		{
			return p_scnManager->appController()->utilProvider();
		}

		void SceneHandle::exitProgram()
		{
			p_scnManager->exitProgram();
		}
	}
}
