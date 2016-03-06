#ifndef __LIB_CONFIGURATION_HPP__
#define __LIB_CONFIGURATION_HPP__

#include <lib/include/types.hpp>
#include "appservice.hpp"
#include <string>

namespace lib
{
	namespace core
	{
		class Config : public AppService
		{
		public:
			Config();
			virtual ~Config() {}

		private:
			void loadFile(const std::string &file);
			const std::string currentFile;
		};
	}
}

#endif
