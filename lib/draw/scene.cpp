#include "scene.hpp"
#include "scenemanager.hpp"
#include "rendernode.hpp"
#include <lib/core/log.hpp>
#include <lib/core/window.hpp>
#include <lib/core/appcontroller.hpp>
#include <lib/core/utilprovider.hpp>
#include "camera.hpp"

namespace lib
{
	namespace draw
	{
		Scene::Scene(PIAppContext piAppContext, const std::string &_name)
			: RenderGroup{ nullptr, _name }, m_camera{ new Camera{} }
		{
			setProvider(core::toController(piAppContext));
			LOG_CONSTRUCT("Name: " + name());
		}

		Scene::~Scene()
		{
			LOG_DESTRUCT("Name: " + name());
		}

		bool Scene::init()
		{
			LOG_DEBUG("Initializing scene " << name());
			if (RenderGroup::init())
			{
				auto sceneSize = getDefaultSizeView();
				m_camera->view().setSize(sceneSize);
//				updateView();
				/*
				m_eventClient = service<SceneManager>()->eventClient()->newEventClient();
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
				*/
				return true;
			}

			return false;
		}

		bool Scene::deinit()
		{
			LOG_DEBUG("Deinitializing scene " << name());
			return true;
		}

		/*
		void Scene::privateOnEnterScene()
		{
			LOG_DEBUG("Entered in scene " << name());
			auto sceneSize = getDefaultSizeView();
			m_camera->view().setSize(sceneSize);
			//			m_view.setCenter(sceneSize.x / 2, sceneSize.y / 2);
//			updateView();

//			LOG_DEBUG("Scene camera set to: center: " << m_camera.target().center().x << "," << m_camera.target().center().y << " and size: " << m_camera.target().width << "," << m_camera.target().height);

			clock.restart();
			onEnterScene();
		}

		*/
		lib::vector2df Scene::pointViewToCurrentView(const vector2df &point, const vector2df &size) const
		{
			return{ (m_camera->view().size().x * point.x) / size.x, (m_camera->view().size().y * point.y) / size.y };
		}

		void Scene::onKeyPressed(const Key &key)
		{
			LOG_DEBUG("Key pressed: " << int{ key.kCode });
		}

		void Scene::onKeyReleased(const Key &key)
		{
			LOG_DEBUG("Key released: " << int{ key.kCode });
		}

		void Scene::setNextScene(const str &name)
		{
			service<SceneManager>()->setScene(name);
		}

		sptr<UtilProvider> Scene::utilProvider() const
		{
			return service<lib::UtilProvider>();
		}

		void Scene::exitProgram()
		{
			service<SceneManager>()->exitProgram();
		}
	}
}
