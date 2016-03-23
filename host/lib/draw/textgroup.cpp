#include "textgroup.hpp"
#include "nodetext.hpp"
#include "scene.hpp"
#include <lib/core/resource.hpp>
#include <lib/core/log.hpp>
#include <SFML/Graphics/Font.hpp>

namespace lib
{
	namespace draw
	{
		struct TextGroup::TextGroupPrivate
		{
			sptr<core::Resource> m_font{ nullptr };
			Alignment m_alignment{ Alignment::Left };
			u32 m_characterSize{ 1 };
			draw::Color m_color;
		};

		TextGroup::TextGroup(const str &name)
			: RenderGroup{ name }, m_private{ sptr<TextGroupPrivate>(new TextGroupPrivate) }
		{
		}

		TextGroup::~TextGroup()
		{
			m_private = nullptr;
		}

		bool TextGroup::init()
		{
			return RenderGroup::init();
		}

		void TextGroup::setFont(const sptr<core::Resource> font)
		{
			m_private->m_font = font;
			update();
		}

		void TextGroup::setAlignment(const Alignment alignment)
		{

		}

		void TextGroup::addText(const str &caption)
		{
			RenderGroup::createText(name() + "_" + caption)->setString(caption);
			update();
		}

		void TextGroup::setCharacterSize(const u32 chSize)
		{
			m_private->m_characterSize = chSize;
			update();
		}

		void TextGroup::setColor(const draw::Color & color)
		{
			m_private->m_color = color;
			update();
		}

		const sptr<core::Resource> TextGroup::font() const
		{
			return m_private->m_font;
		}

		void TextGroup::update()
		{
			const Rectf32 &parentView{ parentScene()->currentView() };
			const vector2df viewCenter{ parentView.center() };
			u32 count{ 0 };
			for (auto &node : _renderNodes)
			{
				sptr<NodeText> temp = std::dynamic_pointer_cast<NodeText>(node);
				if (temp)
				{
					temp->setFont(*(m_private->m_font->getAsFont()));
					temp->setCharacterSize(m_private->m_characterSize);
					temp->setColor(m_private->m_color);
					temp->setPositionX(viewCenter.x, m_private->m_alignment);
					temp->setPositionY(count*m_private->m_characterSize);
					++count;
				}
			}
		}
	}
}
