#include "include/serialization_buffer.hpp"
#include "include/assert.hpp"
#include "common_def_priv.hpp"

#include <map>
#include <string>

namespace vtx
{
	using TypeAndValue = std::pair<int, std::string>;

	PRIVATE_STRUCT_DEFINITION(SerializationBuffer)
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
		SerializationObject & SerializationBuffer::operator<<(const char * const)
		{
			// TODO: insert return statement here
		}
	};

	SerializationObject & SerializationBuffer::operator<<(const s32 n)
	{
		m_private->addProperty(TypeAndValue(SerializationPropertyTypes::Ts32, std::to_string(n)));
		return *this;
	}

	SerializationObject & SerializationObject::addProperty(const char * const name, const char * const str)
	{
		m_private->addProperty(name, TypeAndValue(SerializationPropertyTypes::Tstr, str));
		return *this;
	}
}
