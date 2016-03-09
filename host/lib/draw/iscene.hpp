#ifndef LIB_ISCENECONTROLLER_HPP__
#define LIB_ISCENECONTROLLER_HPP__

#include "hasname.hpp"
#include <lib/core/compileconfig.hpp>
#include <lib/include/types.hpp>
#include <lib/include/key.hpp>
#include <lib/core/timer.hpp>
#include "rendergroup.hpp"
#include "camera.hpp"
#include <string>

namespace lib
{
	namespace draw
	{
		class IScene
		{
		public:
			IScene() {}
			virtual ~IScene() {}

			virtual void onInit() = 0;
			virtual void onDeinit() = 0;
			virtual void onEnterScene() = 0;
			virtual void onExitScene() = 0;

			virtual void update() = 0;

			virtual void onKeyPressed(input::Key key) = 0;
			virtual void onKeyReleased(input::Key key) = 0;

			virtual const vector2df getDefaultSizeView() = 0;
		};
	}
}

#endif
