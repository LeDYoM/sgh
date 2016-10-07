#include "include/videooptions.hpp"

namespace vtx
{
	void VideoOptions::save()
	{
		startSave();
		so()->addObject("resolution", resolution);
		endSave();
	}
}
