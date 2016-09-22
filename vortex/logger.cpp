#include "include/logger.hpp"

#include "common_def_priv.hpp"

#include <sstream>
#include <iostream>
#include <vector>
#include <memory>

namespace vtx
{
	class LogOutputCOut : public ILogOutput
	{
		using ILogOutput::ILogOutput;

		virtual void add(const char *const data) override
		{
			std::cout << data;
		}
	};

	struct PRIVATE_STRUCT_NAME(Logger)
	{
		LogSeverity m_currentLogSeverity{ LogSeverity::None };
		std::ostringstream m_buffer;
		LogSeverity m_bufferSeverity{ LogSeverity::None };
		std::vector<std::unique_ptr<ILogOutput>> m_logOutputs;

		template <typename T>
		void storeLogChunk(const T&data)
		{
			if (m_currentLogSeverity <= m_bufferSeverity) {
				m_buffer << data;
			}
		}

	};

	Logger & Logger::operator<<(const LogSeverity lSeverity)
	{
		m_private->m_bufferSeverity = lSeverity;
		m_private->m_buffer.clear();
		return *this;
	}

	Logger & Logger::operator<<(const char * const message)
	{
		m_private->storeLogChunk(message);
		return *this;
	}

	Logger & Logger::operator<<(int message)
	{
		m_private->storeLogChunk(message);
		return *this;
	}

	Logger & Logger::operator<<(const EndLine_t)
	{
		m_private->m_buffer << std::endl;
		const auto message(m_private->m_buffer.str());
		for (const auto &logoutput : m_private->m_logOutputs) {
			logoutput->add(message.c_str());
		}
		return *this;
	}

	Logger::LogSeverity & Logger::severity() noexcept { return m_private->m_currentLogSeverity; }
	const Logger::LogSeverity vtx::Logger::severity() const noexcept { return m_private->m_currentLogSeverity; }

	Logger::Logger() : m_private{ new PRIVATE_STRUCT_NAME(Logger) } 
	{
		m_private->m_logOutputs.emplace_back(new LogOutputCOut{ true });
	}

	Logger::~Logger()
	{
		DELETE_PRIVATE_MPRIVATE_PIMPL(Logger)
	}
}
