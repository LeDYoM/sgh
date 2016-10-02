#include "include/serialization.hpp"
#include "include/assert.hpp"
#include "common_def_priv.hpp"

#include <map>
#include <string>

namespace vtx
{
	using TypeAndValue = std::pair<int, std::string>;

	PRIVATE_STRUCT_DEFINITION(SerializationObject)
	{
		bool m_WainingForPropertyName{ true };

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

	SerializationObject & operator<<(SerializationObject & so, const s32)
	{
		//LOGIC_ERROR_IF_NOT(so.m_private->m_WainingForPropertyName
		return so;
	}
	SerializationObject & operator<<(SerializationObject & so, const f32)
	{
		return so;
	}
	SerializationObject & operator<<(SerializationObject & so, const char * const)
	{
		return so;
	}
	SerializationObject & operator<<(SerializationObject & so, ISerializable & obj)
	{
		return obj.serialize(so);
	}
	enum SerializationPropertyTypes : int
	{
		Ts32=0,
		Tf32,
		Tstr,
	};

	SerializationObject & SerializationObject::addProperty(const char * const name, const f32 n)
	{
		m_private->addProperty(name, TypeAndValue(SerializationPropertyTypes::Tf32,std::to_string(n)));
		return *this;
	}

	SerializationObject & SerializationObject::addProperty(const char * const name, const s32 n)
	{
		m_private->addProperty(name, TypeAndValue(SerializationPropertyTypes::Ts32, std::to_string(n)));
		return *this;
	}

	SerializationObject & SerializationObject::addProperty(const char * const name, const char * const str)
	{
		m_private->addProperty(name, TypeAndValue(SerializationPropertyTypes::Tstr, str));
		return *this;
	}
}
