#ifndef VTX_LOGGER_INCLUDE_HPP
#define VTX_LOGGER_INCLUDE_HPP

#include "comp_config.hpp"
#include "singleton.hpp"

namespace vtx
{
	class VORTEX_API Logger : public Singleton<Logger>
	{
	protected:
		Logger();
		~Logger();
		friend class Singleton<Logger>;
		friend class Vortex;
	};
}

#endif
