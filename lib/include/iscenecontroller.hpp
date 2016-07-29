#ifndef LIB_ISCENECONTROLLER_HPP
#define LIB_ISCENECONTROLLER_HPP

namespace lib
{
	namespace draw
	{
		class Scene;

		class ISceneController
		{
		public:
			ISceneController() {}
			virtual ~ISceneController() {}

			inline Scene *scene() const { return m_attachedScene; }

			virtual void onEnterScene() = 0;
			virtual void onExitScene() = 0;

		private:
			Scene *m_attachedScene;
		};
	}
}
#endif
