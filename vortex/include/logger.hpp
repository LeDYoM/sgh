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
		constexpr ILogOutput(const bool active_ = true) noexcept : m_active{ active_ } {}
		virtual void add(const char *const message) = 0;
		inline bool active() const noexcept { return m_active; }
		inline bool &active() noexcept { return m_active; }
	private:
		bool m_active{ false };
	};

	class VORTEX_API Logger : public Singleton<Logger>
	{
	public:

		struct EndLine_t {};

		enum class LogSeverity : int
		{
			Debug,
			Info,
			Warning,
			Error,
			None
		};
		inline static Logger*const createInstance() { return Singleton<Logger>::createInstance(); }
		inline static void destroyInstance() { Singleton<Logger>::destroyInstance(); }

		static constexpr const EndLine_t endLine() noexcept { return EndLine_t{}; }
		Logger &operator<<(const LogSeverity lSeverity);
		Logger &operator<<(const char *const message);
		Logger &operator<<(const int message);
		Logger &operator<<(const struct EndLine_t);

		LogSeverity &severity() noexcept;
		const LogSeverity severity() const noexcept;

	private:
		Logger();
		~Logger();
		friend class Singleton<Logger>;
		friend class Vortex;

		DECLARE_PRIVATE_MPRIVATE_PIMPL(Logger)
	};

	inline Logger &ldebug() { return *(Logger::getInstance()) << Logger::LogSeverity::Debug; }
	inline Logger &linfo() { return *(Logger::getInstance()) << Logger::LogSeverity::Info; }
	inline Logger &lwarning() { return *(Logger::getInstance()) << Logger::LogSeverity::Warning; }
	inline Logger &lerror() { return *(Logger::getInstance()) << Logger::LogSeverity::Error; }
	inline const Logger::EndLine_t endline() noexcept { return Logger::EndLine_t{}; }
}

#endif
