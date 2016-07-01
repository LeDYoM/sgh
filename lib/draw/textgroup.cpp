#include "textgroup.hpp"
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
			sptr<Resource> m_font{ nullptr };
			Alignment m_alignment{ Alignment::Left };
			u32 m_characterSize{ 1 };
			draw::Color m_color;
		};

		TextGroup::TextGroup(RenderGroup *const p_parent, const str &name)
			: RenderGroup{ p_parent, name }, m_private{ sptr<TextGroupPrivate>(new TextGroupPrivate) }
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

		void TextGroup::setFont(const sptr<Resource> font)
		{
			m_private->m_font = font;
			update();
		}

		void TextGroup::setAlignment(const Alignment alignment)
		{
			alignment;
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

		const sptr<Resource> TextGroup::font() const
		{
			return m_private->m_font;
		}

		void TextGroup::update()
		{
			const Rectf32 parentView;
			const vector2df viewCenter{ parentView.center() };
			u32 count{ 0 };
			for (auto &node : _renderNodes)
			{
				sptr<NodeText> temp = as<NodeText>(node);
				if (temp)
				{
					temp->setFont(*(m_private->m_font->getAsFont()));
					temp->setCharacterSize(m_private->m_characterSize);
					temp->color = m_private->m_color;
					temp->setAlignment(m_private->m_alignment);
					temp->position->x = viewCenter.x;
					temp->position->y = static_cast<f32>(count*m_private->m_characterSize);
					++count;
				}
			}
		}
	}
}
