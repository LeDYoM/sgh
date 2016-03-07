#ifndef LIB_FILE_HPP
#define LIB_FILE_HPP

#include <lib/include/types.hpp>
#include "appservice.hpp"
#include <string>
#include <stack>

namespace lib
{
	namespace core
	{
		struct Exception
		{
			int Line;
			std::string File;
			std::string Code;
			std::string SubCode;
			std::string Reason;
			bool Internal;
			Exception(int line, const std::string &file, const std::string &code, const std::string &subCode, const std::string &reason, const bool internal)
				: Line{ line }, File( file ), Code( code ), SubCode( subCode ), Reason( reason ), Internal{ internal } {}
		};
		class ExceptionManager : public AppService
		{
		public:
			ExceptionManager();
			virtual ~ExceptionManager();

			void addException(Exception &&exception);
		private:
			std::stack<Exception> m_exceptions;
		};

	}
}

#define EXCEPTION_INTERNAL(c,sc,r)	lib::core::Exception{__LINE__,__FILE__,c,sc,r,true}

#endif
