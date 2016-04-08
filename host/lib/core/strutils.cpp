#include "strutils.hpp"
#include <cctype>
#include <algorithm>

namespace lib
{
	bool starts_with(const std::string &str, const std::string &what)
	{
		return str.find_first_of(what) == 0;
	}

	bool ends_with(const std::string &str, const std::string &what)
	{
		return str.find_last_of(what) + what.size() == str.size();
	}

	void ltrim(std::string &str)
	{
		while (!str.empty() && std::isspace(str[0]))
			str = str.substr(1);
	}

	void rtrim(std::string &str)
	{
		while (!str.empty() && std::isspace(str[str.size() - 1]))
			str = str.substr(0, str.size() - 2);
	}

	void trim(std::string &str)
	{
		ltrim(str);
		rtrim(str);
	}

	void leftFrom(std::string &str, const std::string &what)
	{
		auto pos = str.find_first_of(what);
		if (pos != std::string::npos)
		{
			str = str.substr(0, pos);
		}
	}

	void rightFrom(std::string &str, const std::string &what)
	{
		auto pos = str.find_first_of(what);
		if (pos != std::string::npos)
		{
			str = str.substr(pos+what.size());
		}
	}

	bool contains(const std::string &str, const std::string &what)
	{
		return str.find_first_of(what) != std::string::npos;
	}

	bool is_uint(const std::string &str)
	{
		return !str.empty() && str.find_first_not_of("0123456789") == std::string::npos;
	}

	bool is_int(const std::string &str)
	{
		return !str.empty() && str.find_first_not_of("-0123456789") == std::string::npos;
	}

	bool is_number(const std::string &str)
	{
		return !str.empty() && str.find_first_not_of(".-0123456789") == std::string::npos;
	}

}
