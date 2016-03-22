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
		Scene::Scene(const std::string &_name) : RenderGroup{ _name }
		{
			LOG_CONSTRUCT("Name: " + name());
		}

		Scene::~Scene()
		{
			LOG_DESTRUCT("Name: " + name());
		}

		void Scene::updateView()
		{
			m_scnManager->appController()->parentWindow()->updateCamera(m_camera);
		}

		const vector2df Scene::getCoordinatesToCenter(const Rectf32 &coordinates) const
		{
			return{ m_camera.target().center().x - (coordinates.width / 2.0f), m_camera.target().center().y - (coordinates.height / 2.0f) };
		}

		bool Scene::init()
		{
			LOG_DEBUG("Initializing scene " << name());
			if (RenderGroup::init())
			{
				auto sceneSize = getDefaultSizeView();
				m_camera.setSize(sceneSize);
				updateView();
				m_eventClient = m_scnManager->eventClient()->newEventClient();
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
				return true;
			}
			return false;
		}

		bool Scene::deinit()
		{
			LOG_DEBUG("Deinitializing scene " << name());
			return true;
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
			m_eventClient->setActive(true);
			onEnterScene();
		}

		lib::vector2df Scene::pointViewToCurrentView(const vector2df &point, const vector2df &size) const
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

		void Scene::setNextScene(const std::string &name)
		{
			__ASSERT(m_scnManager, "Null SceneManager on Scene");
			m_scnManager->setScene(name);
		}

		uptr<core::ResourceManager> const &Scene::resourceManager()
		{
			return m_scnManager->appController()->resourceManager();
		}

		uptr<util::UtilProvider> const & Scene::utilProvider()
		{
			return m_scnManager->appController()->utilProvider();
		}

		void Scene::exitProgram()
		{
			m_scnManager->exitProgram();
		}

		lib::draw::Scene *const Scene::parentScene()
		{
			return this;
		}
	}
}
