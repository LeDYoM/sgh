#include "obj.hpp"

namespace lib
{
	Object::Object()
		: m_app{ nullptr } {}

	Object::Object(Object *const other)
		: m_app{ other ? other->m_app : nullptr } { }

	Object::Object(core::AppController *const app) 
		: m_app{ app } {}

	void SystemObject::setProvider(core::AppController *const app)
	{
		m_app = app;
	}

	Object::~Object()
	{
		m_app = nullptr;
	}

}