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
		virtual void Init() {}
	private:
		friend class AppController;
		core::AppController *m_appController;

		void PrivateInit(core::AppController *const appController_)
		{
			m_appController = appController_;
			Init();
		}
	};
}
#endif
