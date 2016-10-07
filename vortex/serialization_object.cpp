#include "include/serialization_object.hpp"

#include "common_def_priv.hpp"

#include <map>
#include <fstream>
#include <memory>

namespace vtx
{
	PRIVATE_STRUCT_DEFINITION(SerializationObject)
	{
		std::ofstream *output{ nullptr };
		PRIVATE_STRUCT_NAME(SerializationObject)() {}
		PRIVATE_STRUCT_NAME(SerializationObject)(PRIVATE_STRUCT_NAME(SerializationObject) && rhs) noexcept
		{
			std::swap(output, rhs.output);
		}

		void close()
		{
			output->flush();
			output->close();
			delete output;
			output = nullptr;
		}

		~SerializationObjectPrivate()
		{
			if (output) {
				close();
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

	SerializationObject::SerializationObject()
		: m_private{ new PRIVATE_STRUCT_NAME(SerializationObject) }
	{
	}

	constexpr SerializationObject::SerializationObject(SerializationObject &&rh) noexcept
		: m_private {rh.m_private}
	{
	}

	SerializationObject & vtx::SerializationObject::operator=(SerializationObject &&rh) noexcept
	{
		std::swap(m_private, rh.m_private);
		return *this;
	}

	void SerializationObject::openFile(const Str &fileName)
	{
		m_private->output = new std::ofstream;
		m_private->output->open(fileName.c_str());
	}

	SerializationObject::~SerializationObject()
	{
		DELETE_PRIVATE_MPRIVATE_PIMPL(SerializationObject);
	}
}
