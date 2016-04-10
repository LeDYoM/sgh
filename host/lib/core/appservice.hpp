#ifndef __LIB_APP_SERVICE_HPP__
#define __LIB_APP_SERVICE_HPP__

namespace lib
{
	namespace core
	{
		class AppController;
	}

	class AppService
	{
	public:
		AppService &operator=(const AppService &rh) = delete;
		core::AppController *const appController() { return m_appController; }
		virtual void Setup() {}
		virtual void Init() {}
		virtual void Close() {}
	private:
		friend class core::AppController;
		core::AppController *m_appController{ nullptr };

		void PrivateSetup(core::AppController *const appController_)
		{
			m_appController = appController_;
			Setup();
		}
	};
}
#endif
