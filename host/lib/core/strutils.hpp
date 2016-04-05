#ifndef LIB_STRUTILS_HPP
#define LIB_STRUTILS_HPP

#include <string>

namespace lib
{
	bool starts_with(const std::string &str, const std::string &what);
	void ltrim(std::string &str);
	void rtrim(std::string &str);
	void trim(std::string &str);
	void leftFrom(std::string &str, const std::string &what);
	void rightFrom(std::string &str, const std::string &what);
	bool contains(const std::string &str, const std::string &what);
}

#endif
