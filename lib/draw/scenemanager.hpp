#ifndef __LIB_SCENEMANAGER_HPP__
#define __LIB_SCENEMANAGER_HPP__

#include <vector>
#include <lib/include/types.hpp>
#include <lib/core/appservice.hpp>
#include "transformation.hpp"
#include "renderstates.hpp"
#include <stack>

namespace lib
{
	namespace draw
	{
		class Scene;
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

			void visit(const sptr<SceneNode> &node, bool forceFrameUpdate, Transformation &parentTransformation);
		private:
			void setScene(sptr<Scene> scene);

			sptr<Scene> getSceneByName(const std::string &name) const;
			std::vector<sptr<Scene>> _scenes;
			sptr<Scene> _currentScene{ nullptr };
			bool b_lock{ false };
			sptr<Scene> _nextScene{ nullptr };
		};
	}
}

#endif
