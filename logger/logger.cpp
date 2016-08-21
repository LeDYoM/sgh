#include "include/logger.hpp"
#include <string>

#if defined(_MSC_VER) || defined(__BORLANDC__)
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#endif

namespace logger
{
	static Logger *loggerInstance{ nullptr };

	class LoggerPrivate
	{
	public:
		LoggerPrivate() {}
		~LoggerPrivate() {}
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

	void Logger::debug(const char *message)
	{
		m_private->toLog(message);
	}

	void Logger::info(const char *message)
	{
		m_private->toLog(message);
	}

	void Logger::warning(const char *message)
	{
		m_private->toLog(message);
	}

	void Logger::error(const char *message)
	{
		m_private->toLog(message);
	}

	Logger *createLogger()
	{
		if (!loggerInstance)
		{
			loggerInstance = new Logger;
			loggerInstance->info("Logger created");
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
			loggerInstance->info("Destroying logger");
			delete loggerInstance;
			loggerInstance = nullptr;
		}
	}
}
