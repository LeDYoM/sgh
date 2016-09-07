#include "modulecontext.hpp"

namespace moduler
{
	using namespace std;

	IModule *ModuleContext::requireModule(const char *moduleName)
	{
		const auto iterator_{ m_modulesConnections.find(moduleName) };

		if (iterator_ == m_modulesConnections.end()) {
			// There is still no connection established

		}
		return nullptr;
	}
}
