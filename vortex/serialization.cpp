#include "include/serialization.hpp"

#include "common_def_priv.hpp"

#include <map>
#include <string>

namespace vtx
{
	using TypeAndValue = std::pair<int, std::string>;

	PRIVATE_STRUCT_DEFINITION(SerializationObject)
	{
		std::map<std::string, TypeAndValue> m_properties;

		void addProperty(const std::string&name, TypeAndValue &&value)
		{
			m_properties[name] = std::move(value);
		}

		void addProperty(const std::string&name, const TypeAndValue &value)
		{
			addProperty(name, std::move(value));
		}
	};

	enum SerializationPropertyTypes : int
	{
		Types32=0,
		Typef32
	};

	SerializationObject & SerializationObject::addProperty(const char * const name, const s32 n)
	{
		m_private->addProperty(name, TypeAndValue(SerializationPropertyTypes::Types32,std::to_string(n)));
		return *this;
	}

	SerializationObject & SerializationObject::addProperty(const char * const name, const f32 n)
	{
		m_private->addProperty(name, TypeAndValue(SerializationPropertyTypes::Typef32, std::to_string(n)));
		return *this;
	}
}
