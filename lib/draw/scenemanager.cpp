#include "scenemanager.hpp"
#include "scene.hpp"
#include "renderstates.hpp"
#include <lib/drivers/render/rendertarget.hpp>
#include <lib/core/log.hpp>
#include <lib/core/window.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/appcontroller.hpp>
#include <lib/core/input.hpp>
#include "rendernode.hpp"
#include "rendermanager.hpp"

namespace lib
{
	namespace draw
	{

		SceneManager::SceneManager()
		{
			LOG_CONSTRUCT_NOPARAMS;
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
//			m_renderStates = sptr<RenderStates>(new RenderStates);
		}

		void SceneManager::addScene(sptr<Scene> newScene)
		{
			__ASSERT(newScene, "Cannot add a null scene");
			_scenes.push_back(newScene);
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

			__ASSERT(m_renderStates.size() == 0, "Render states still on the stack");
			m_renderStates.emplace(RenderStates{});
			Transformation t;
			auto _renderManager( service<RenderManager>() );
			_renderManager->startFrame(service<core::Window>()->windowRenderTarget(), _currentScene->camera());

			visit(_currentScene,false,t);
			m_renderStates.pop();
			__ASSERT(m_renderStates.size() == 0, "Render states still on the stack");
		}

		void SceneManager::visit(const sptr<SceneNode>& node, bool forceFrameUpdate, Transformation &parentTransformation)
		{
			if (node->isActive()) {
				service<Input>()->updateNode(node);
				if (node->isVisible()) {
					node->updateAnimations();

					const RenderStates &top{ m_renderStates.top() };
					RenderStates rStates{ top.blendMode, top.transform, top.texture, top.shader };

					rStates.transform *= node->transformation();

					if (auto renderableNode = as<RenderNode>(node)) {
						rStates.texture = renderableNode->texture();
					}

					m_renderStates.push(rStates);
					node->update();
					forceFrameUpdate |= node->frameTransformationNeedsUpdate();

					if (forceFrameUpdate) {
						node->updateTransformationForFrameIfNecessary(parentTransformation,forceFrameUpdate);
						parentTransformation = node->globalTransformation();
					}

					if (auto drawableNode = as<RenderNode>(node)) {
						if (drawableNode->vertexArray().size() > 0) {
							service<RenderManager>()->preRenderNode(drawableNode, rStates);
						}
					} else if (auto renderGroupNode = as<RenderGroup>(node)) {
						for (auto node_ : renderGroupNode->renderNodes()) {
							visit(node_,forceFrameUpdate,parentTransformation);
						}
					}

					m_renderStates.pop();
				}
			}
		}

		void SceneManager::exitProgram()
		{
//			p_parentWindow->exitProgram();
		}

		const RenderStates &SceneManager::frameRenderStates() const
		{
			return m_renderStates.top();
		}
	}
}
