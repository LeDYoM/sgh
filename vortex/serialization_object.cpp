#include "include/serialization_object.hpp"

#include "common_def_priv.hpp"

#include <map>
#include <fstream>
#include <memory>

namespace vtx
{
	PRIVATE_STRUCT_DEFINITION(SerializationObject)
	{
		std::shared_ptr<std::ostream> output{ nullptr };
		PRIVATE_STRUCT_NAME(SerializationObject)() {}
		PRIVATE_STRUCT_NAME(SerializationObject)(PRIVATE_STRUCT_NAME(SerializationObject) && rhs) noexcept
		{
			std::swap(output, rhs.output);
		}

		~SerializationObjectPrivate ()
		{
			if (output)
			{
				output->flush();
				output.reset();
			}
		}
	};

	static SerializationFormat _serializationFormat{ SerializationFormat::VSO };

	void SerializationObject::addValue(const Str &name, const Str &value)
	{
		switch (_serializationFormat)
		{
		case SerializationFormat::VSO:
		case SerializationFormat::VML:
		case SerializationFormat::VBF:
		default:
		{
			(*m_private->output) << '"' << name.c_str() << "\": \"" << value.c_str() << "\"\n";
		}
		break;
		}
	}

	void SerializationObject::addValue(const Str &name , const s32 value)
	{
		switch (_serializationFormat)
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

	SerializationFormat SerializationObject::serializationFormat() noexcept
	{
		return _serializationFormat;
	}

	void SerializationObject::setSerializationFormat(const SerializationFormat serializationFormat) noexcept
	{
		_serializationFormat = serializationFormat;
	}

	SerializationObject vtx::SerializationObject::createFromFile(const Str &fileName)
	{
		auto outputFile(std::make_shared<std::ofstream>());
		outputFile->open(fileName.c_str());
		SerializationObject temp;
		temp.m_private->output = outputFile;
		return std::move(temp);
	}

	SerializationObject::SerializationObject()
		: m_private{ new PRIVATE_STRUCT_NAME(SerializationObject) }
	{
	}

	SerializationObject::SerializationObject(SerializationObject &&)
	{
	}

	SerializationObject::~SerializationObject()
	{
		DELETE_PRIVATE_MPRIVATE_PIMPL(SerializationObject);
	}
}
