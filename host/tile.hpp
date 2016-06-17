#ifndef __TILE_HPP__
#define __TILE_HPP__

#include "gamebasetile.hpp"

namespace zoper
{
	class Tile : public GameBaseTile
	{
	public:
		explicit Tile(lib::draw::RenderGroup *const p_parent, lib::board::BoardTileData data, const lib::vector2df &size);
		Tile(const Tile &other) = delete;
		virtual ~Tile();

		static void resetTileCounter();
	private:
		static lib::u32 _tileCounter;
	};
}

#endif
