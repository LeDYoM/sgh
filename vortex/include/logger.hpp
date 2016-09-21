#ifndef VTX_LOGGER_INCLUDE_HPP
#define VTX_LOGGER_INCLUDE_HPP

#include "comp_config.hpp"
#include "common_def.hpp"
#include "singleton.hpp"

namespace vtx
{
	class ILogOutput
	{
	public:
		virtual void add(const char *const message) = 0;
	};
	class VORTEX_API Log
	{
	public:
		struct EndLine_t {};
		static constexpr const EndLine_t endLine() { return EndLine_t{}; }
		Log &operator<<(const char *const message);
		Log &operator<<(int message);
		Log &operator<<(const struct EndLine_t);

	private:
		Log() {}
		friend class Logger;
	};

	class VORTEX_API Logger : public Singleton<Logger>
	{
	public:

		inline static Logger*const createInstance() { return Singleton<Logger>::createInstance(); }
		inline static void destroyInstance() { Singleton<Logger>::destroyInstance(); }

		Log &debug() noexcept;
		Log &info() noexcept;
		Log &warning() noexcept;
		Log &error() noexcept;
	private:
		Logger();
		~Logger();
		friend class Singleton<Logger>;
		friend class Vortex;

		DECLARE_PRIVATE_MPRIVATE_PIMPL(Logger)

	};

	inline Log &ldebug() noexcept { return Logger::getInstance()->debug(); }
	inline Log &linfo() noexcept { return Logger::getInstance()->info(); }
	inline Log &lwarning() noexcept { return Logger::getInstance()->warning(); }
	inline Log &lerror() noexcept { return Logger::getInstance()->error(); }
}

#endif
