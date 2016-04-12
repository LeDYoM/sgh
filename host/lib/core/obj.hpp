#ifndef LIB_OBJECT_HPP
#define LIB_OBJECT_HPP

#include "appservice.hpp"

namespace lib
{
	class Object
	{
	public:
		Object();
		Object(Object *other);
		Object(AppService *provider);

		AppService *setProvider(AppService *other);
		AppService *setProvider(Object *obj);
		virtual ~Object();

		template <class T> sptr<T> service() const
		{
			return m_provider->service<T>();
		}

	private:
		AppService *m_provider;

	};
}
#endif
