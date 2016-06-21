#ifndef __MENUSCENE_HPP__
#define __MENUSCENE_HPP__

#include "keymapping.hpp"
#include <lib/menu/menumanager.hpp>
#include <lib/menu/menustep.hpp>
#include <lib/include/types.hpp>
#include <vector>

namespace zoper
{
	class MenuScene : public lib::menu::MenuManager
	{
	public:
		MenuScene(lib::PIAppContext piAppContext);
		virtual ~MenuScene();

		// Inherited via Scene
		virtual bool init() override;
		virtual bool deinit() override;
		virtual void onEnterScene() override;
		virtual void onExitScene() override;

		virtual void update() override;

		virtual const lib::vector2df getDefaultSizeView() override;
	private:
		KeyMapping m_keyMapping;
		lib::sptr<lib::draw::NodeShape> _logo{ nullptr };
		lib::sptr<lib::draw::NodeShape> _background{ nullptr };
	};
}

#endif
