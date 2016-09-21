#include "include/logger.hpp"

#include "common_def_priv.hpp"

#include <sstream>
#include <iostream>

namespace vtx
{
	struct PRIVATE_STRUCT_NAME(Logger)
	{
		LogSeverity m_currentLogSeverity{ LogSeverity::None };
		std::ostringstream m_buffer;
	};

	Logger & Logger::operator<<(const LogSeverity lSeverity)
	{
		m_private->m_currentLogSeverity = lSeverity;
		m_private->m_buffer.clear();
		return *this;
	}

	Logger & Logger::operator<<(const char * const message)
	{
		m_private->m_buffer << message;
		return *this;
	}

	Logger & Logger::operator<<(int message)
	{
		m_private->m_buffer << message;
		return *this;
	}

	Logger & Logger::operator<<(const EndLine_t)
	{
		m_private->m_buffer << std::endl;
		std::cout << m_private->m_buffer.str();
		return *this;
	}

	Logger::LogSeverity & Logger::severity() noexcept { return m_private->m_currentLogSeverity; }
	const Logger::LogSeverity vtx::Logger::severity() const noexcept { return m_private->m_currentLogSeverity; }

	Logger::Logger() : m_private{ new PRIVATE_STRUCT_NAME(Logger) } {}

	Logger::~Logger()
	{
		DELETE_PRIVATE_MPRIVATE_PIMPL(Logger)
	}
}
