#include "moduleconnection.hpp"
#include "modulehandle.hpp"
#include "modulerprivate.hpp"
#include <algorithm>

namespace moduler
{
	namespace pcontainer
	{
		template <typename Container, typename Content>
		std::pair<bool,typename Container::const_iterator> find(const Container &container, const Content *const element) noexcept
		{
			const auto iterator(std::find_if(container.cbegin(), container.cend(), [element](const Content *node) {
				return *node == *element;
			}));
			return{ iterator != container.cend(),iterator };
		}

		template <typename Container, typename Content>
		bool add_if_not_exists(Container &container, Content *const element)
		{
			const auto result(find(container, element));
			if (!result.first) {
				container.push_back(element);
				return true;
			}
			return false;
		}
	}

	ModuleConnection::~ModuleConnection()
	{
	}

	bool ModuleConnection::hasModule(const ModuleHandle *const requiredModule) const noexcept
	{
		return pcontainer::find(m_dest, requiredModule).first;
	}

	bool ModuleConnection::addRequiredModule(ModuleHandle * requiredModule)
	{
		if (!pcontainer::add_if_not_exists(m_dest, requiredModule)) {
			m_modulerPrivate->incrementModuleReferenceCounter(requiredModule);
			return true;
		}
		return false;
	}
}
