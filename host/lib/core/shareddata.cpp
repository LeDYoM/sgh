#include "shareddata.hpp"
#include "appcontroller.hpp"
#include "filesystem.hpp"
#include "file.hpp"
#include "log.hpp"

namespace lib
{
	SharedData::SharedData()
	{
	}

	SharedData::~SharedData()
	{
	}


	DataMap &SharedData::sharedData()
	{
		return m_rootNode;
	}

	void SharedData::Init()
	{
		auto file(service<FileSystem>()->getFile("config.cfg"));
		std::vector<str> data{ file->asText() };
		u32 count{ 0 };
		m_rootNode = std::move(DataValue::fromStringVector(data, count) );
	}
}
