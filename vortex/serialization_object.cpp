#include "include/serialization_object.hpp"

#include "common_def_priv.hpp"

#include <map>
#include <fstream>
#include <memory>

namespace vtx
{
	PRIVATE_STRUCT_DEFINITION(SerializationObject)
	{
		std::map<std::string, std::string> m_properties;
		std::shared_ptr<std::ostream> output{ nullptr };
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
		switch (m_serializationFormat)
		{
		case SerializationFormat::VSO:
		case SerializationFormat::VML:
		case SerializationFormat::VBF:
		default:
		{
			(*m_private->output) << '"' << name.c_str() << "\": \"" << Str(value).c_str() << "\"\n";
		}
		break;
		}
	}

	static SerializationFormat _serializationFormat{ SerializationFormat::VSO };

	SerializationFormat SerializationObject::serializationFormat() noexcept
	{
		return _serializationFormat;
	}

	void SerializationObject::setSerializationFormat(const SerializationFormat serializationFormat) noexcept
	{
		_serializationFormat = serializationFormat;
	}

	SerializationObject::SerializationObject()
		: m_private{ new PRIVATE_STRUCT_NAME(SerializationObject) }
	{
	}

	SerializationObject::~SerializationObject()
	{
		DELETE_PRIVATE_MPRIVATE_PIMPL(SerializationObject);
	}


	SerializationObject &&createFromFile(const Str &fileName)
	{
		auto outputFile(std::make_shared<std::ofstream>());
		outputFile->open(fileName.c_str());
		if (outputFile->is_open())
		{
			SerializationObject temp;
			temp.m_private->output = outputFile;
		}

	}

}
