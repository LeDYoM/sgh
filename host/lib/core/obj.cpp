#include "obj.hpp"
#include "appservice.hpp"

namespace lib
{
	Object::Object()
		: m_provider{ nullptr }
	{

	}

	Object::Object(Object *other)
		: m_provider{ other->m_provider }
	{
	}

	Object::Object(AppService *provider)
		: m_provider{ provider }
	{

	}

	lib::AppService * Object::setProvider(AppService *other)
	{
		AppService *temp(m_provider);
		m_provider = other;
		return temp;
	}

	lib::AppService * Object::setProvider(Object *obj)
	{
		return setProvider(obj->m_provider);
	}

	Object::~Object()
	{
		m_provider = nullptr;
	}

}