#ifndef __LIB_APP_SERVICE_HPP__
#define __LIB_APP_SERVICE_HPP__

#include <string>
#include "obj.hpp"

namespace lib
{
	namespace core
	{
		class AppController;
	}

	class AppService : public Object
	{
	public:
		virtual void Setup() {}
		virtual void Init() {}
		virtual void Stop() {}

		virtual void processSystemEvent(const DataMap *) {}
	private:
		friend class core::AppController;
		friend class ServicesManager;

		void PrivateSetup(core::AppController *const appController_)
		{
			setProvider(appController_);
			Setup();
		}
	};
}
#endif
