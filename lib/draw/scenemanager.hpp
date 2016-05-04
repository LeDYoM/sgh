#ifndef __LIB_SCENEMANAGER_HPP__
#define __LIB_SCENEMANAGER_HPP__

#include <vector>
#include <lib/include/types.hpp>
#include <lib/core/appservice.hpp>
#include <lib/include/key.hpp>
#include "renderstates.hpp"
#include <stack>

namespace lib
{
	namespace core
	{
		class Window;
	}
	namespace draw
	{
		class Scene;
		class RenderStates;
		class SceneNode;

		class SceneManager : public AppService
		{
		public:
			SceneManager();
			virtual ~SceneManager();

			static const str staticTypeName() { return "SceneManager"; }

			virtual void Init() override;

			void addScene(sptr<Scene> newScene);
			void setScene(const std::string &name);
			void update();

			void addScenes(const std::vector<sptr<Scene>> &&sceneVector);
			void exitProgram();

			const RenderStates &frameRenderStates() const;
			void visit(const sptr<SceneNode> &node);
		private:
			void setScene(sptr<Scene> scene);

			sptr<Scene> getSceneByName(const std::string &name) const;
			std::vector<sptr<Scene>> _scenes;
			sptr<Scene> _currentScene{ nullptr };
			bool b_lock{ false };
			sptr<Scene> _nextScene{ nullptr };
			typedef std::stack <RenderStates> StackVector;
			StackVector m_renderStates;
		};
	}
}

#endif
