#ifndef LIB_OBJECT_HPP
#define LIB_OBJECT_HPP

#include "servicesmanager.hpp"

namespace lib
{
	namespace core
	{
		class AppController;
	}
	class Object
	{
	public:
		Object();
		Object(Object *other);
		Object(core::AppController *app);

		void setProvider(core::AppController *app);
		void setProvider(Object *obj);
		virtual ~Object();

		template <class T> sptr<T> service() const
		{
			return m_app->servicesManager()->service<T>();
		}

		core::AppController *appController() const { return m_app; }
	protected:
		core::AppController *m_app;

	};
}
#endif
