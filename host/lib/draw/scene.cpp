#include "scene.hpp"
#include "scenemanager.hpp"
#include "renderizable.hpp"
#include <lib/core/log.hpp>
#include <lib/core/window.hpp>
#include <lib/core/appcontroller.hpp>
#include <lib/core/resourcemanager.hpp>
#include "view.hpp"

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
			//			p_scnManager->appController->parentWindow()->setView(*p_view.get());
			p_scnManager->appController->parentWindow()->updateView(m_view);
			//			LOG_DEBUG("Scene view set to: center: " << p_view->getCenter().x << "," << p_view->getCenter().y << " and size: " << p_view->getSize().x << "," << p_view->getSize().y);
		}

		/*
		sf::View *const Scene::getView() const
		{
		return p_view.get();
		}
		*/
		const vector2df Scene::getCoordinatesToCenter(const Rectf32 &coordinates) const
		{
			return{ m_view.target().center().x - (coordinates.width / 2.0f), m_view.target().center().y - (coordinates.height / 2.0f) };
		}

		void Scene::privateOnInit()
		{
			LOG_DEBUG("Initializing scene " << name());
			//			p_view = uptr<sf::View>(new sf::View(p_scnManager->appController->parentWindow()->getView()));
			auto sceneSize = getDefaultSizeView();
			m_view.setSize(sceneSize);
			//			p_view->setSize(sceneSize.x, sceneSize.y);
			//		p_view->setCenter(sceneSize.x / 2, sceneSize.y / 2);
			updateView();

			//			LOG_DEBUG("Scene view set to: center: " << m_view.target().center().x << "," << m_view.target().center().y << " and size: " << m_view.target().width << "," << m_view.target().height);

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
			m_view.setSize(sceneSize);
			//			m_view.setCenter(sceneSize.x / 2, sceneSize.y / 2);
			updateView();

			LOG_DEBUG("Scene view set to: center: " << m_view.target().center().x << "," << m_view.target().center().y << " and size: " << m_view.target().width << "," << m_view.target().height);

			clock.restart();
			onEnterScene();
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
			return p_scnManager->appController->resourceManager();
		}

		void Scene::exitProgram()
		{
			p_scnManager->exitProgram();
		}
	}
}
