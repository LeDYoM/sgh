#include "exceptionmanager.hpp"

namespace lib
{
	namespace core
	{
		ExceptionManager::ExceptionManager()
		{
		}

		ExceptionManager::~ExceptionManager()
		{

		}

		void ExceptionManager::addException(Exception &&exception)
		{
			m_exceptions.push(exception);
		}

	}
}

