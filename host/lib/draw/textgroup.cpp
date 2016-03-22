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
			TextGroupPrivate()
			{
				LOG_CONSTRUCT_NOPARAMS;
			}

			~TextGroupPrivate()
			{
				LOG_DESTRUCT_NOPARAMS;
			}
		};

		TextGroup::TextGroup(const str &name)
			: RenderGroup{ name }
			, m_private{ new TextGroupPrivate() }
		{
			LOG_CONSTRUCT_NOPARAMS;
		}

		TextGroup::~TextGroup()
		{
			m_private = nullptr;
			LOG_DESTRUCT_NOPARAMS;
		}

		void TextGroup::setFont(const sptr<core::Resource> font)
		{
			m_private->m_font = font;
			updateFont();
			updatePositions();
		}

		void TextGroup::setAlignment(const Alignment alignment)
		{
			m_private->m_alignment = alignment;
		}

		void TextGroup::addText(const str &caption)
		{
			sptr<NodeText> node{ RenderGroup::createText(name() + "_" + caption) };
			node->setString(caption);
			updateFontOne(node);
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

		void TextGroup::updateFontOne(sptr<NodeText> node)
		{
			__ASSERT(node, "Node is null");
			node->setFont(*(m_private->m_font->getAsFont()));
		}

		void TextGroup::updateFont()
		{
			for (auto &node : _renderNodes)
			{
				sptr<NodeText> temp = std::dynamic_pointer_cast<NodeText>(node);
				if (temp)
				{
					updateFontOne(temp);
				}
			}
		}
	}
}
