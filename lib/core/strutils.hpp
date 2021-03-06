#ifndef LIB_STRUTILS_HPP
#define LIB_STRUTILS_HPP

#include <string>
#include <vector>

namespace lib
{
	bool starts_with(const std::string &str, const std::string &what);
	bool ends_with(const std::string &str, const std::string &what);
	void ltrim(std::string &str);
	void rtrim(std::string &str);
	void trim(std::string &str);
	void leftFrom(std::string &str, const std::string &what);
	void rightFrom(std::string &str, const std::string &what);
	bool contains(const std::string &str, const std::string &what);
	bool is_uint(const std::string &str);
	bool is_int(const std::string &str);
	bool is_number(const std::string &str);
	bool is_bool(const std::string &str);
	bool to_bool(const std::string &str);
	std::vector<std::string> split(const std::string &str, const char separator);
}

#endif
