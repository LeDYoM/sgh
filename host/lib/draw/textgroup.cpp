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
			sptr<core::Resource> m_font{ nullptr };
			NodeText::Alignment m_alignment{ NodeText::Alignment::Left };
			u32 m_characterSize{ 1 };
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
			update();
		}

		void TextGroup::setCharacterSize(u32 size)
		{
			m_private->m_characterSize = size;
			update();
		}

		void TextGroup::setAlignment(const NodeText::Alignment alignment)
		{
			m_private->m_alignment = alignment;
		}

		void TextGroup::addText(const str &caption)
		{
			sptr<NodeText> node{ RenderGroup::createText(name() + "_" + caption) };
			node->setString(caption);
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
				sptr<NodeText> node_ = std::dynamic_pointer_cast<NodeText>(node);
				if (node_)
				{
					node_->setFont(*(m_private->m_font->getAsFont()));
					node_->setCharacterSize(m_private->m_characterSize);
					node_->setPosition({ viewCenter.x, static_cast<f32>(count*(m_private->m_characterSize)) });
					node_->setAlignment(m_private->m_alignment);
					++count;
				}
			}
		}
	}
}
