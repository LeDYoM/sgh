#include "include/serialization_object.hpp"

#include "common_def_priv.hpp"

#include <map>
#include <fstream>

namespace vtx
{
	PRIVATE_STRUCT_DEFINITION(SerializationObject)
	{
		std::map<std::string, std::string> m_properties;
		std::ofstream output;
	};

	void SerializationObject::addValue(const Str &name, const Str &value)
	{
		auto &out(m_private->output);
		if (m_private->output.is_open())
		{
			switch (m_serializationFormat)
			{
			case SerializationFormat::VSO:
			case SerializationFormat::VML:
			case SerializationFormat::VBF:
			default:
			{
				out << '"' << name.c_str() << "\": \"" << value.c_str() << "\"\n";
			}
			break;
			}
		}
	}

	void SerializationObject::addValue(const Str &name , const s32 value)
	{
		auto &out(m_private->output);
		if (m_private->output.is_open())
		{
			switch (m_serializationFormat)
			{
			case SerializationFormat::VSO:
			case SerializationFormat::VML:
			case SerializationFormat::VBF:
			default:
			{
				out << '"' << name.c_str() << "\": \"" << Str(value).c_str() << "\"\n";
			}
			break;
			}
		}
	}

	SerializationObject::SerializationObject(const SerializationFormat serializationFormat, const Str & fileName)
		: m_private{ new PRIVATE_STRUCT_NAME(SerializationObject) }, m_serializationFormat{ serializationFormat }
	{
		m_private->output.open(fileName.c_str());
	}

	SerializationObject::~SerializationObject()
	{
		if (m_private->output.is_open())
			m_private->output.close();

		DELETE_PRIVATE_MPRIVATE_PIMPL(SerializationObject);
	}


}
