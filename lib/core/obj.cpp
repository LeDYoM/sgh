#include "obj.hpp"
#include "appservice.hpp"

namespace lib
{
	Object::Object()
		: m_app{ nullptr } {}

	Object::Object(Object *other)
		: m_app{ other ? other->m_app : nullptr } { }

	Object::Object(core::AppController *app) 
		: m_app{ app } {}

	void Object::setProvider(core::AppController *app)
	{
		m_app = app;
	}

	Object::~Object()
	{
		m_app = nullptr;
	}

}