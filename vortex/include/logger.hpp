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

	/**
	/* \class Logger
	** Class that manages logging functions. It is a singleton with public creation.
	**/
	class VORTEX_API Logger final : public Singleton<Logger>
	{
	public:

		struct EndLine_t {};			///< Type of the endline

		enum class LogSeverity
		{
			Debug,
			Info,
			Warning,
			Error,
			None
		};
		inline static Logger*const createInstance() { return Singleton<Logger>::createInstance(); }
		inline static void destroyInstance() { Singleton<Logger>::destroyInstance(); }

		static constexpr const EndLine_t endLine{};
		Logger &operator<<(const LogSeverity lSeverity) noexcept;
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
	constexpr static Logger::EndLine_t endline{};

	#define LDEBUG(x)	*(Logger::getInstance()) << Logger::LogSeverity::Debug << x << endline;
	#define LINFO(x)	*(Logger::getInstance()) << Logger::LogSeverity::Info << x << endline;
	#define LWARNING(x)	*(Logger::getInstance()) << Logger::LogSeverity::Warning << x << endline;
	#define LERROR(x)	*(Logger::getInstance()) << Logger::LogSeverity::Error << x << endline;
}

#endif
