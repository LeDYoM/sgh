#ifndef __LIB_MENUDESCRIPTOR_HPP__
#define __LIB_MENUDESCRIPTOR_HPP__

#include <string>
#include <lib/include/types.hpp>

namespace lib
{
	namespace menu
	{
		class OptionDescriptor
		{
		public:
			explicit OptionDescriptor(const std::string &text, bool createSubString=false,u32 startValueIndex=0,
				const std::vector<std::string> &subOptionsLabels=std::vector<std::string>())
				: _text(text), _createSubString{ createSubString }, _startValueIndex{ startValueIndex },
				_subOptionsLabels( subOptionsLabels ) {}

			std::string _text;
			bool _createSubString;
			u32 _startValueIndex;
			std::vector<std::string> _subOptionsLabels;
		};

		class CursorDescriptor
		{
		public:
			explicit CursorDescriptor(const u32 nVertex, const vector2df &size, const lib::scn::draw::Color &color)
				: _nVertex{ nVertex }, _size{ size }, _color{ color } {}

			u32 _nVertex;
			vector2df _size;
			lib::scn::draw::Color _color;
		};
	}
}

#endif
