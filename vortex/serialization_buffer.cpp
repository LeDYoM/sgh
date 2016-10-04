#include "include/serialization_buffer.hpp"
#include "include/serialization_object.hpp"
#include "include/assert.hpp"
#include "common_def_priv.hpp"

#include <map>
#include <string>
#include <fstream>

namespace vtx
{

	PRIVATE_STRUCT_DEFINITION(SerializationBuffer)
	{
		std::map<std::string, SerializationObject> m_properties;

		SerializationObject &addObject(const std::string&name, SerializationObject &&value)
		{
			return (*(m_properties.emplace(std::make_pair(name, std::move(value))).first)).second;
		}

		SerializationObject &addObject(const std::string&name, const SerializationObject &value)
		{
			return addObject(name, std::move(value));
		}
	};

	SerializationObject & SerializationBuffer::getNew(const char *const name)
	{
		return m_private->addObject(name,std::move(SerializationObject(this)));
	}

	bool SerializationBuffer::writeFile(const Str &fileName)
	{
		std::ofstream outputFile;

		outputFile.open(fileName.c_str());
		if (outputFile.is_open)
		{
			for (const auto& prop : m_private->m_properties)
			{
				outputFile << prop.first << "=" << prop.s
			}
		}
		return false;
	}

}
