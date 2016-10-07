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

	void FileMapped::save() const
	{
		SerializationObject serializationObject{ SerializationObject::createFromFile(m_fileName) };
	}
}
