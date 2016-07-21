#ifndef LIB_OBJECT_HPP
#define LIB_OBJECT_HPP

#include "compileconfig.hpp"
#include "servicesmanager.hpp"

namespace lib
{
	namespace core
	{
		class AppController;
	}
	class LIB_API Object
	{
	public:
		Object();
		Object(Object *other);
		Object(core::AppController *app);

		void setProvider(core::AppController *app);
		virtual ~Object();

		template <class T> sptr<T> service() const
		{
			return m_app->servicesManager()->service<T>();
		}

		template <class T, class S> static sptr<T> as(sptr<S> node) { return std::dynamic_pointer_cast<T>(node); }

		core::AppController *appController() const { return m_app; }
	protected:
		core::AppController *m_app;

	};
}
#endif
