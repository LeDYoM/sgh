#ifndef __LIB_SCENEMANAGER_HPP__
#define __LIB_SCENEMANAGER_HPP__

#include <vector>
#include <lib/include/types.hpp>
#include <lib/core/appservice.hpp>
#include <lib/include/key.hpp>

namespace lib
{
	namespace core
	{
		class Window;
		namespace events
		{
			class EventClient;
		}
	}
	namespace draw
	{
		class ResourceManager;
		class Scene;

		class SceneManager : public AppService
		{
		public:
			using AppService::AppService;
			virtual ~SceneManager();

			virtual void Init() override;

			void addScene(sptr<Scene> newScene);
			void setScene(const std::string &name);
			void update();

			void addScenes(const std::vector<sptr<Scene>> &&sceneVector);
			void exitProgram();

			sptr<core::events::EventClient> eventClient() const;
		private:
			void setScene(sptr<Scene> scene);

			sptr<Scene> getSceneByName(const std::string &name) const;
			std::vector<sptr<Scene>> _scenes;
			sptr<Scene> _currentScene{ nullptr };
			bool b_lock{ false };
			sptr<Scene> _nextScene{ nullptr };
			sptr<core::events::EventClient> m_eventClient{ nullptr };
		};
	}
}

#endif
