#ifndef LIB_DRIVERS_SFML_WWINDOW_IMPLEMENTATION_HPP
#define LIB_DRIVERS_SFML_WWINDOW_IMPLEMENTATION_HPP

#include <lib/drivers/window/wwindow.hpp>
#include <lib/drivers/render/rendertarget.hpp>
#include <lib/drivers/render/texture.hpp>
#include <lib/include/types.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <queue>

namespace lib
{
	namespace drivers
	{
		namespace window
		{
			class SFMLWindow : public IWWindow, public sf::RenderWindow
			{
				virtual bool create(const WindowCreationParams&) override;
				virtual bool resizePending() const override;
				virtual vector2du16 size() const override;
				virtual void setVerticalSync(bool enabled) override;
				virtual void setTitle(const str &title) override;
				virtual void clear() override;
				virtual void display() override;
				virtual sptr<render::RenderTarget> windowRenderTarget() const override;
				virtual sptr<render::Texture> newTexture() const override;
				virtual void collectEvents() override;
				virtual sptr<DataMap> nextEvent();
				virtual u32 pendingEvents();
			private:
				bool m_resizePending;
				std::queue<sptr<DataMap>> m_collectedEvents;
				sptr<render::RenderTarget> m_thisAsRenderTarget;
			};
		}
	}
}
#endif
