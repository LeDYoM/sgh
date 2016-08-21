#include "include/str.hpp"
#include <cctype>
#include <algorithm>
#include <iterator>

namespace ext
{
	bool str::starts_with(const std::string & what) const
	{
		return find_first_of(what) == 0;
	}

	bool str::ends_with(const std::string & what) const
	{
		return find_last_of(what) + what.size() == size();
	}

	str &str::ltrim()
	{
		while (!empty() && std::isspace(at(0)))
			erase(0, 1);

		return *this;
	}

	str &str::rtrim()
	{
		while (!empty() && std::isspace(at(size() - 1)))
			erase(size() - 2,1);

		return *this;
	}

	str &str::trim()
	{
		return ltrim().rtrim();
	}

	str &str::leftFrom(const std::string & what)
	{
		auto pos = find_first_of(what);
		if (pos != std::string::npos) {
			erase(pos);
		}
		return *this;
	}

	str &str::rightFrom(const std::string & what)
	{
		auto pos = find_first_of(what);
		if (pos != std::string::npos) {
			erase(0,pos + what.size());
		}
		return *this;
	}

	bool str::contains(const std::string & what) const
	{
		return find_first_of(what) != std::string::npos;
	}

	bool str::is_uint() const
	{
		return !empty() && find_first_not_of("0123456789") == std::string::npos;
	}

	bool str::is_int() const
	{
		return !empty() && find_first_not_of("-0123456789") == std::string::npos;
	}

	bool str::is_number() const
	{
		return !empty() && find_first_not_of(".-0123456789") == std::string::npos;
	}

	bool str::is_bool() const
	{
		std::string cpy;
		std::transform(begin(), end(), std::back_inserter(cpy), ::tolower);

		return (cpy == "true" || cpy == "false");
	}

	bool ext::str::to_bool() const
	{
		std::string cpy;
		std::transform(begin(), end(), cpy.begin(), ::tolower);

		return (cpy == "true");
	}

	std::vector<std::string> str::split(const char separator) const
	{
		std::string m_ndpcpy(c_str());
		std::vector<std::string> result;

		do {
			auto sz(m_ndpcpy.find_first_of(separator));
			result.emplace_back(std::move(m_ndpcpy.substr(0, sz)));
			m_ndpcpy = m_ndpcpy.substr((sz == std::string::npos) ? (m_ndpcpy.size()) : (sz + 1));
		} while (!m_ndpcpy.empty());

		return std::move(result);
	}
}
