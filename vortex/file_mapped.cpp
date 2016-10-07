#include "include/file_mapped.hpp"
#include "include/serialization_object.hpp"

#include <memory>

namespace vtx
{

	FileMapped::FileMapped()
	{
	}

	FileMapped::~FileMapped()
	{
	}

	void FileMapped::startSave()
	{
		m_serializationObject = new SerializationObject;
		m_serializationObject->openFile(m_fileName);
	}

	void FileMapped::endSave()
	{
		if (m_serializationObject)
		{
			delete m_serializationObject;
			m_serializationObject = nullptr;
		}
	}
}
