#ifndef EXTYPES_STRMAP_HPP
#define EXTYPES_STRMAP_HPP

#include "str.hpp"
#include <vector>
#include <functional>

namespace ext
{
	class StrMap
	{
	public:
		using Index = str;
		using Value = str;

		StrMap();
		~StrMap();
		StrMap(int argc, char *argv[], int start=1);
		StrMap(const StrMap &);
		StrMap &operator=(const StrMap &);
		StrMap(StrMap &&);
		StrMap &operator=(StrMap &&);
		explicit StrMap(const std::vector<str> &dataVector, const str &separator = "=");

		bool exists(const Index &index) const;
		bool add(const Index &index, const Value &value);
		bool update(const Index &index, const Value &value);
		bool addLine(const Value &value, const str &separator);
		StrMap subMap(const Index &) const;

		void for_each(std::function<void(std::pair<const Index &, const Value&>)> precdicate) const;
	private:
		struct StringMapPrivate *m_private;
	};
}


#endif
