#ifndef LIB_DATAP_DATAOBJECT_HPP
#define LIB_DATAP_DATAOBJECT_HPP

#include <string>
#include <vector>

namespace lib
{
	namespace datap
	{
		class DataObject
		{
		public:
			DataObject(const std::string &name) : m_name{ name } {}
			void setName(const std::string &name) { m_name = name; }
		private:
			std::string m_name;
		};

		class DataObjectTree : public DataObject
		{
			using DataObject::DataObject;
		private:

		};
	}
}

#endif

