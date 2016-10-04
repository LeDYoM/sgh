#include "include/file_map.hpp"
#include "include/serialization_buffer.hpp"
#include "include/logger.hpp"

#include "common_def_priv.hpp"

namespace vtx
{
	PRIVATE_STRUCT_DEFINITION(FileMap)
	{
		Str m_associatedFileName;
		std::vector<ISerializable*> m_properties;

		PRIVATE_STRUCT_NAME(FileMap)(const Str&fileName) : m_associatedFileName(fileName) {}
	};

	FileMap::FileMap(const Str &fileName) : m_private { new PRIVATE_STRUCT_NAME(FileMap)(fileName) }
	{
	}

	FileMap::~FileMap()
	{
		DELETE_PRIVATE_MPRIVATE_PIMPL(FileMap);
	}

	void FileMap::addProperty(ISerializable * serializableProperty)
	{
//		m_private->m_properties.emplace_back(serializableProperty);
	}

	bool FileMap::write()
	{
		/*
		SerializationBuffer sBuffer;
		for (const auto* prop : m_private->m_properties) {
			sBuffer = prop->serialize(sBuffer);
		}
		return sBuffer.writeFile(m_private->m_associatedFileName);
		*/
	}
}
