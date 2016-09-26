#include "include/vapplication.hpp"
#include "include/logger.hpp"

#include "common_def_priv.hpp"

#include <memory>

namespace vtx
{
	PRIVATE_STRUCT_DEFINITION(VApplication)
	{
	};

	VApplication::VApplication() : m_private{ new PRIVATE_STRUCT_NAME(VApplication) }
	{
	}

	VApplication::~VApplication()
	{
	}

	/*
	void VApplication::onStart()
	{
	}
	*/
	void VApplication::onFinish()
	{
	}

	bool VApplication::onUpdate()
	{
		return true;
	}
}
