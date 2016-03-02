#ifndef LIB_DATAP_DATAOBJECT_HPP
#define LIB_DATAP_DATAOBJECT_HPP

#include <string>
#include <vector>
#include <lib/include/types.hpp>

namespace lib
{
	namespace datap
	{
		class DataObjectLeaf;
		class DataObjectTree;
		class DataObject
		{
		public:
			static sptr<DataObject> getNew(const std::string &name)
			{
				return sptr<DataObject>(new DataObject(name));
			}
			void setName(const std::string &name) { m_name = name; }
		protected:
			DataObject(const std::string &name) : m_name{ name } {}
		private:
			std::string m_name;
		};

		class DataObjectTree : public DataObject
		{
		public:
			static sptr<DataObjectTree> getNewTree(const std::string &name)
			{
				return sptr<DataObjectTree>(new DataObjectTree(name));
			}

			DataObjectTree(const std::string &name) : DataObject(name) {}
		private:
			std::vector<sptr<DataObject>> m_objects;
		};

		class DataObjectLeaf : public DataObject
		{
		public:
			static sptr<DataObjectLeaf> getNewLeaf(const std::string &name, const std::string &value)
			{
				return sptr<DataObjectLeaf>(new DataObjectLeaf(name, value));
			}

			DataObjectLeaf(const std::string &name, const std::string &value) : DataObject(name), m_value{ value } {}
		private:
			std::string m_value;
		};
	}
}

#endif

