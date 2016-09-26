#include "include/memleakdetector.hpp"

#if defined _MSC_VER && defined USE_LEAKDETECTOR

#include "crtdbg.h"
#include <windows.h>

static int crtDebugMemAllocHook(int allocType, void *userData, size_t size, int blockType, long requestIndex, const unsigned char *fileName, int lineIndex){

	lineIndex;
	fileName;
	blockType;
	blockType;
	size;
	userData;
	allocType;

	if (requestIndex == 149) //break;

		return true;

	return true;
}

#endif

void installMemLeakDetector()
{
#if defined _MSC_VER && defined USE_LEAKDETECTOR
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetAllocHook(crtDebugMemAllocHook);
#endif
}

void finishMemLeakDetector()
{
#if defined _MSC_VER && defined USE_LEAKDETECTOR
//	_CrtDumpMemoryLeaks();
#endif
}
