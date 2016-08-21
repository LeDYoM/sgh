#ifndef LOGGER_INCLUDE_HPP
#define LOGGER_INCLUDE_HPP

#include "loggerexport.hpp"

namespace logger
{
	class LoggerPrivate;
	class Logger
	{
	public:
		Logger();
		~Logger();

		LOGGER_API void debug(const char *);
		LOGGER_API void info(const char *);
		LOGGER_API void warning(const char *);
		LOGGER_API void error(const char *);
	private:
		LoggerPrivate *m_private;
	};

	LOGGER_API Logger *createLogger();
	LOGGER_API Logger *logger();
	LOGGER_API void destroyLogger();

}

#define LOG_DEBUG(msg)		logger::logger()->debug(msg);
#define LOG_INFO(msg)		logger::logger()->info(msg);
#define LOG_WARNING(msg)	logger::logger()->warning(msg);
#define LOG_ERROR(msg)		logger::logger()->error(msg);

#endif
