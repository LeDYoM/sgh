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
	protected:
		Object();
		Object(Object *const other);
		Object(core::AppController *const app);
	public:
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

	class LIB_API ClientObject : public Object
	{
	public:
		ClientObject(ClientObject *const other) : Object( static_cast<Object*const>(other) ) {}
		virtual ~ClientObject() {}
	};

	class LIB_API SystemObject : public Object
	{
	public:
		SystemObject() : Object() {}
		SystemObject(core::AppController *const app) : Object( app ) {}
		virtual ~SystemObject() {}

		void setProvider(core::AppController *app);

	};

}
#endif
