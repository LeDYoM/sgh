#include "include/logger.hpp"
#include <string>

#if defined(_MSC_VER) || defined(__BORLANDC__)
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif

namespace logger
{
	static Logger *loggerInstance{ nullptr };

	class LoggerPrivate
	{
	public:
		LoggerPrivate() {}
		~LoggerPrivate() {}
		LogSeverity m_currentSeverity{ LogSeverity::None };
		void toLog(const char *message) {
			OutputDebugString(message);
			OutputDebugString("\n");
		}
	};

	Logger::Logger()
	{
		m_private = new LoggerPrivate;
	}

	Logger::~Logger()
	{
		delete m_private;
	}

	void Logger::setLoggerSeverity(const LogSeverity severity)
	{
		m_private->m_currentSeverity = severity;
	}

	void Logger::log(const LogSeverity severity, const char *message)
	{
		if (severity <= m_private->m_currentSeverity)
			m_private->toLog(message);
	}

	void Logger::log(const LogSeverity severity, const std::string &message)
	{
		if (severity <= m_private->m_currentSeverity)
			m_private->toLog(message.c_str());
	}

	Logger *createLogger()
	{
		if (!loggerInstance)
		{
			loggerInstance = new Logger;
			loggerInstance->log(LogSeverity::Debug, "Logger created");
		}

		return loggerInstance;
	}

	Logger *logger()
	{
		return loggerInstance;
	}

	void destroyLogger()
	{
		if (loggerInstance)
		{
			loggerInstance->log(LogSeverity::Debug, "Destroying logger");
			delete loggerInstance;
			loggerInstance = nullptr;
		}
	}
}
