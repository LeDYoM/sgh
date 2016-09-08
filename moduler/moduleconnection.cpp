#include "moduleconnection.hpp"
#include "modulehandle.hpp"
#include <algorithm>

namespace moduler
{
	namespace pcontainer
	{
		template <typename Container, typename Content>
		std::pair<bool,typename Container::const_iterator> find(const Container &container, const Content *const element)
		{
			const auto iterator(std::find_if(container.cbegin(), container.cend(), [element](const Content *node) {
				return *node == *element;
			}));
			return{ iterator != container.cend(),iterator };
		}

		template <typename Container, typename Content>
		bool add_if_not_exists(const Container &container, const Content *const &&element)
		{
			const auto result(find(container, element));
			if (!result.first) {
				container.emplace_back(element);
				return true;
			}
			return false;
		}

	}

	ModuleConnection::~ModuleConnection()
	{
	}

	bool ModuleConnection::hasModule(const ModuleHandle *const requiredModule) const
	{
		return pcontainer::find(m_dest, requiredModule).first;
	}

	bool ModuleConnection::addRequiredModule(ModuleHandle * requiredModule)
	{
		return pcontainer::add_if_not_exists(m_dest, std::move(requiredModule));
	}
}
