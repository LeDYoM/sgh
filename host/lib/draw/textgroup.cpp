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
		};

		TextGroup::TextGroup(const str &name)
			: RenderGroup{ name }, m_private{ uptr<TextGroupPrivate>(new TextGroupPrivate) }
		{
		}

		TextGroup::~TextGroup()
		{
			m_private.release();
		}

		void TextGroup::setFont(const sptr<core::Resource> font)
		{
			m_private->m_font = font;
			updateFont();
			updatePositions();
		}

		void TextGroup::addText(const str &caption)
		{
			RenderGroup::createText(name() + "_" + caption)->setString(caption);
			updatePositions();
		}

		const sptr<core::Resource> TextGroup::font() const
		{
			return m_private->m_font;
		}

		void TextGroup::updatePositions()
		{
			const Rectf32 &parentView{ parentScene()->currentView() };
			const vector2df viewCenter{ parentView.center() };

			for (auto &node : _renderNodes)
			{
				sptr<NodeText> temp = std::dynamic_pointer_cast<NodeText>(node);
				if (temp)
				{
					temp->setPositionX(viewCenter.x, m_private->m_alignment);
				}
			}
		}

		void TextGroup::updateFont()
		{
			for (auto &node : _renderNodes)
			{
				sptr<NodeText> temp = std::dynamic_pointer_cast<NodeText>(node);
				if (temp)
				{
					temp->setFont(*(m_private->m_font->getAsFont()));
				}
			}
		}
	}
}
