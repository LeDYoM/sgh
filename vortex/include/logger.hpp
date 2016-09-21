#ifndef VTX_LOGGER_INCLUDE_HPP
#define VTX_LOGGER_INCLUDE_HPP

#include "comp_config.hpp"
#include "common_def.hpp"
#include "singleton.hpp"

namespace vtx
{
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
		Log &debug();
		Log &info();
		Log &warning();
		Log &error();
	protected:
		Logger();
		~Logger();
		friend class Singleton<Logger>;
		friend class Vortex;

		DECLARE_PRIVATE_MPRIVATE_PIMPL(Logger)

	};
}

#endif
