#include "obj.hpp"
#include "appservice.hpp"

namespace lib
{
	Object::Object()
		: m_app{ nullptr }
	{

	}

	Object::Object(Object *other)
		: m_app{ other->m_app }
	{
	}

	Object::Object(core::AppController *app)
		: m_app{ app }
	{

	}

	void Object::setProvider(core::AppController *app)
	{
		m_app = app;
	}

	void Object::setProvider(Object *obj)
	{
		if (obj)
			setProvider(obj->m_app);
	}

	Object::~Object()
	{
		m_app = nullptr;
	}

}