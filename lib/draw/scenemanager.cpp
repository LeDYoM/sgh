#include "scenemanager.hpp"
#include "scene.hpp"
#include <lib/core/log.hpp>
#include <lib/core/window.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/appcontroller.hpp>
#include <lib/core/events/inputevent.hpp>

namespace lib
{
	namespace draw
	{

		SceneManager::SceneManager()
		{
			LOG_DESTRUCT_NOPARAMS;
		}

		SceneManager::~SceneManager()
		{
			for (auto scene : _scenes)
			{
				scene->deinit();
			}
			_scenes.clear();
			LOG_DESTRUCT_NOPARAMS;
		}

		void SceneManager::Init()
		{
			AppService::Init();
			m_renderStates = sptr<RenderStates>(new RenderStates);
		}

		void SceneManager::addScene(sptr<Scene> newScene)
		{
			__ASSERT(newScene, "Cannot add a null scene");
			_scenes.push_back(newScene);
			newScene->setProvider(this);
			newScene->init();
		}
	
		void SceneManager::setScene(const std::string &name)
		{
			sptr<Scene> scene = getSceneByName(name);
			
			if (scene) {
				if (b_lock) {
					_nextScene = scene;
					LOG_DEBUG("Deferred Change scene to " << name);
				}
				else {
					b_lock = true;
					setScene(scene);
					b_lock = false;
				}
			}
			else {
				LOG_ERROR("Scene " << name << " not found in SceneManager");
			}
		}
		
		void SceneManager::addScenes(const std::vector<sptr<Scene>>&& sceneVector)
		{
			for (auto scene : sceneVector) {
				addScene(scene);
			}
		}

		void SceneManager::setScene(sptr<Scene> scene)
		{
			__ASSERT(scene, "Cannot change to a nullptr Scene");
			if (_currentScene) {
				_currentScene->privateOnExitScene();
			}
			else {
				LOG_DEBUG("Set first scene");
			}
			_currentScene = scene;
			_currentScene->privateOnEnterScene();
		}

		sptr<Scene> SceneManager::getSceneByName(const std::string &name) const
		{
			for (auto scene : _scenes) {
				if (scene->name() == name) {
					return scene;
				}
			}
			return nullptr;
		}

		void SceneManager::update()
		{
			if (!_currentScene) {
				if (_scenes.size() > 0) {
					setScene(_scenes[0]);
				}
			}
			else if (_nextScene) {
				setScene(_nextScene);
				_nextScene = nullptr;
			}
			else {
				if (_currentScene) {
					_currentScene->update();
				}
			}

			m_renderStates->nextFrame();
			m_renderStates->currentTarget = service<core::Window>()->renderTarget();
			_currentScene->draw();
			m_renderStates->currentTarget = nullptr;
		}

		void SceneManager::exitProgram()
		{
//			p_parentWindow->exitProgram();
		}

		sptr<RenderStates> SceneManager::frameRenderStates() const
		{
			return m_renderStates;
		}

	}
}
