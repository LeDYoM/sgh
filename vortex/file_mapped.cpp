#include "include/file_mapped.hpp"
#include "include/serialization_object.hpp"

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
		SerializationObject serializationObject{ SerializationObject::createFromFile(m_fileName) };
	}

	void FileMapped::endSave()
	{
	}
}
