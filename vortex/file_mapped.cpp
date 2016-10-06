#include "include/file_mapped.hpp"
#include "include/serialization_object.hpp"

namespace vtx
{

	FileMapped::FileMapped(const Str & fileName)
		: m_serializationObject{SerializationFormat::VSO,fileName }
	{
	}

	FileMapped::~FileMapped()
	{
	}

	void FileMapped::serialize() const
	{
	}
}
