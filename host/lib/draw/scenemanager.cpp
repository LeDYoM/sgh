#include "scenemanager.hpp"
#include "scene.hpp"
#include <lib/core/log.hpp>
#include <lib/core/window.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/appcontroller.hpp>
#include <lib/core/eventmanager.hpp>
#include <lib/core/events/eventreceiver.hpp>
#include <lib/core/events/inputevent.hpp>

namespace lib
{
	namespace draw
	{
		SceneManager::SceneManager(core::AppController *const appController) : AppService{ appController }
		{
			LOG_CONSTRUCT_NOPARAMS;
			m_eventReceiver = appController->eventManager()->newEventReceiver();
			m_eventReceiver->setReceiver([this](lib::core::events::EventReceiver::ReceivedEvent event_)
			{
				auto evKey = lib::core::events::getEventAs<core::events::KeyEvent>(event_);
				switch (evKey->action())
				{
				case core::events::KeyEvent::Action::KeyPressed:
					this->onKeyPressed(evKey->key());
					break;
				case core::events::KeyEvent::Action::KeyReleased:
					this->onKeyReleased(evKey->key());
					break;
				default:
					LOG_WARNING("Unknown Action on event key");
					break;
				}
			});
		}

		SceneManager::~SceneManager()
		{
			for (auto scene : _scenes)
			{
				scene->privateOnDeinit();
			}
			_scenes.clear();
			LOG_DESTRUCT_NOPARAMS;
		}

		void SceneManager::addScene(sptr<Scene> newScene)
		{
			__ASSERT(newScene, "Cannot add a null scene");
			newScene->p_scnManager = this;
			_scenes.push_back(newScene);
			newScene->privateOnInit();
		}
	
		void SceneManager::setScene(const std::string &name)
		{
			sptr<Scene> scene = getSceneByName(name);
			
			if (scene)
			{
				if (b_lock)
				{
					_nextScene = scene;
					LOG_DEBUG("Deferred Change scene to " << name);
				}
				else
				{
					b_lock = true;
					setScene(scene);
					b_lock = false;
				}
			}
			else
			{
				LOG_ERROR("Scene " << name << " not found in SceneManager");
			}
		}
		
		void SceneManager::addScenes(const std::vector<sptr<Scene>>&& sceneVector)
		{
			for (auto scene : sceneVector)
			{
				addScene(scene);
			}
		}

		void SceneManager::onKeyPressed(lib::input::Key key)
		{
			__ASSERT(_currentScene, "No active scene when pressing a key");
			_currentScene->onKeyPressed(key);
		}

		void SceneManager::onKeyReleased(lib::input::Key key)
		{
			__ASSERT(_currentScene, "No active scene when releasing a key");
			_currentScene->onKeyReleased(key);
		}

		void SceneManager::setScene(sptr<Scene> scene)
		{
			__ASSERT(scene, "Cannot change to a nullptr Scene");
			if (_currentScene)
			{
				_currentScene->privateOnExitScene();
			}
			else
			{
				LOG_DEBUG("Set first scene");
			}
			_currentScene = scene;
			_currentScene->privateOnEnterScene();
		}

		sptr<Scene> SceneManager::getSceneByName(const std::string &name) const
		{
			for (auto scene : _scenes)
			{
				if (scene->name() == name)
				{
					return scene;
				}
			}
			return nullptr;
		}

		void SceneManager::update()
		{
			if (!_currentScene)
			{
				if (_scenes.size() > 0)
				{
					setScene(_scenes[0]);
				}
			}
			else if (_nextScene)
			{
				setScene(_nextScene);
				_nextScene = nullptr;
			}
			else
			{
				if (_currentScene)
				{
					_currentScene->update();
				}
			}

			lib::draw::RenderStates states;
			_currentScene->draw(appController->parentWindow().get(), states);
		}

		void SceneManager::exitProgram()
		{
//			p_parentWindow->exitProgram();
		}

	}
}
