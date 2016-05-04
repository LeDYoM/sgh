#ifndef LIB_TTEXTGROUP_HPP
#define LIB_TTEXTGROUP_HPP

#include <lib/include/types.hpp>
#include <lib/include/color.hpp>
#include "rendergroup.hpp"
#include "rendernode.hpp"

namespace lib
{
	class Resource;
	namespace draw
	{
		class TextGroup : public RenderGroup
		{
		public:
			TextGroup(const str &name);
			virtual ~TextGroup();

			virtual bool init() override;

			void setFont(const sptr<Resource> font);
			void setAlignment(const Alignment alignment);
			void addText(const str &caption);
			void setCharacterSize(const u32 chSize);
			void setColor(const draw::Color &color);

			const sptr<Resource> font() const;
		private:
			void update();

			struct TextGroupPrivate;
			sptr<TextGroupPrivate> m_private;
		};
	}
}

#endif
