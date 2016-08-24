#ifndef LOGGER_INCLUDE_HPP
#define LOGGER_INCLUDE_HPP

#include "loggerexport.hpp"

#ifdef USE_STDSTRING
	#include <string>
#endif

namespace logger
{
	class LoggerPrivate;
	enum LogSeverity : unsigned char
	{
		None		=	0,
		Critical	=	1,
		Error		=	2,
		Warning		=	3,
		Info		=	4,
		Debug		=	5,
		All			=	6

	};
	class Logger
	{
	public:
		Logger();
		~Logger();

		LOGGER_API void setLoggerSeverity(const LogSeverity);
		LOGGER_API void log(const LogSeverity, const char *);

#ifdef USE_STDSTRING
		LOGGER_API void log(const LogSeverity, const std::string&);
#endif

	private:
		LoggerPrivate *m_private;
	};

	LOGGER_API Logger *createLogger();
	LOGGER_API Logger *logger();
	LOGGER_API void destroyLogger();
}

#define LOG_DEBUG(msg)		logger::logger()->log(logger::LogSeverity::Debug,msg);
#define LOG_INFO(msg)		logger::logger()->log(logger::LogSeverity::Info,msg);
#define LOG_WARNING(msg)	logger::logger()->log(logger::LogSeverity::Warning,msg);
#define LOG_ERROR(msg)		logger::logger()->log(logger::LogSeverity::Error,msg);
#define LOG_CRITCAL(msg)	logger::logger()->log(logger::LogSeverity::Critical,msg);

#ifdef USE_STDSTRING
	#define LOG_DEBUG_STR(x) { std::ostringstream os_; os_ << params << std::endl; logger::logger()->log(logger::LogSeverity::Debug,os_.str()); }
	#define LOG_INFO_STR(x) { std::ostringstream os_; os_ << params << std::endl; logger::logger()->log(logger::LogSeverity::Info,os_.str()); }
	#define LOG_WARNING_STR(x) { std::ostringstream os_; os_ << params << std::endl; logger::logger()->log(logger::LogSeverity::Warning,os_.str()); }
	#define LOG_ERROR_STR(x) { std::ostringstream os_; os_ << params << std::endl; logger::logger()->log(logger::LogSeverity::Error,os_.str()); }
	#define LOG_CRITICAL_STR(x) { std::ostringstream os_; os_ << params << std::endl; logger::logger()->log(logger::LogSeverity::Critical,os_.str()); }
#endif

#endif
