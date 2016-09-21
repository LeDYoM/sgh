#include "include/logger.hpp"

#include "common_def_priv.hpp"

#include <sstream>

namespace vtx
{
	struct PRIVATE_STRUCT_NAME(Logger)
	{
		Log m_debug;
		Log m_info;
		Log m_warning;
		Log m_error;
	};

	std::ostringstream m_buffer;


	Log & Log::operator<<(const char * const message)
	{
		m_buffer << message;
		return *this;
	}

	Log & Log::operator<<(int message)
	{
		m_buffer << message;
		return *this;
	}

	Log & Log::operator<<(const EndLine_t)
	{
		m_buffer << std::endl;
		return *this;
	}

	Log & Logger::debug()
	{
		return m_private->m_debug;
	}

	Log & Logger::info()
	{
		return m_private->m_info;
	}

	Log & Logger::warning()
	{
		return m_private->m_warning;
	}

	Log & Logger::error()
	{
		return m_private->m_error;
	}

	Logger::Logger() : m_private{ new PRIVATE_STRUCT_NAME(Logger) }
	{
	}


	Logger::~Logger()
	{
		DELETE_PRIVATE_MPRIVATE_PIMPL(Logger)
	}
}
