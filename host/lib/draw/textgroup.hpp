#ifndef LIB_TTEXTGROUP_HPP
#define LIB_TTEXTGROUP_HPP

#include <lib/include/types.hpp>
#include "rendergroup.hpp"
#include <lib/draw/nodetext.hpp>

namespace lib
{
	namespace core
	{
		class Resource;
	}
	namespace draw
	{
		class TextGroup : public RenderGroup
		{
		public:
			TextGroup(const str &name);
			virtual ~TextGroup();

			void setFont(const sptr<core::Resource> font);
			void setCharacterSize(u32 size);
			void setAlignment(const NodeText::Alignment alignment);
			void addText(const str &caption);
			const sptr<core::Resource> font() const;
		private:
			void update();

			struct TextGroupPrivate;
			uptr<TextGroupPrivate> m_private{ nullptr };
		};
	}
}

#endif
