#ifndef EXTYPES_STR_HPP
#define EXTYPES_STR_HPP

#include <string>
#include <vector>

namespace ext
{
	class str : public std::string
	{
	public:
		using std::string::string;

		bool starts_with(const std::string &what) const;
		bool ends_with(const std::string &what) const;
		str &ltrim();
		str &rtrim();
		str &trim();
		str &leftFrom(const std::string &what);
		str &rightFrom(const std::string &what);
		bool contains(const std::string &what) const;
		bool is_uint() const;
		bool is_int() const;
		bool is_number() const;
		bool is_bool() const;
		bool to_bool() const;
		std::vector<std::string> split(const char separator) const;

	};
}


#endif
