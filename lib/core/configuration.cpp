#include "configuration.hpp"
#include "appcontroller.hpp"
#include "filesystem.hpp"
#include "file.hpp"
#include "log.hpp"

namespace lib
{
	namespace
	{
		class DataPath
		{
		public:
			typedef std::vector<std::string>::size_type size_type;

			explicit DataPath(const str &dp, const char separator = '/')
				: m_separator{ separator }
			{
				setPath(dp);
			}

			void setPath(const str &newdp)
			{
				m_nodes.clear();
				std::string m_ndpcpy(newdp);

				do {
					auto sz(m_ndpcpy.find_first_of(m_separator));
					m_nodes.push_back(m_ndpcpy.substr(0, sz));
					m_ndpcpy = m_ndpcpy.substr((sz==std::string::npos)?(m_ndpcpy.size()):(sz+1));
				} while (!m_ndpcpy.empty());
			}

			inline size_type size() const
			{
				return m_nodes.size();
			}

			inline const std::string &operator[](const size_type index) const { return m_nodes[index]; }

		private:
			std::vector<std::string> m_nodes;
			char m_separator;
		};
	}
	Configuration::Configuration()
	{
	}

	Configuration::~Configuration()
	{
	}

	DataMap &Configuration::configuration()
	{
		return m_rootNode;
	}

	void Configuration::Init()
	{
		auto file(service<FileSystem>()->getFile("config.cfg"));
		std::vector<str> data{ file->asText() };
		u32 count{ 0 };
		m_rootNode = std::move(DataValue::fromStringVector(data, count) );
	}

	DataValue Configuration::get(const str &cPath, const DataValue &defaultv) const
	{
		u32 index{ 0 };
		DataPath dPath{ cPath };
		const DataMap *current{ &m_rootNode };

		while (index<dPath.size()) {
			auto p(current->find(dPath[index]));
			if (p != current->end()) {
				if (index == (dPath.size() - 1)) {
					return p->second;
				}
				if (!(p->second.ismap())) {
					return defaultv;
				}
				else {
					current = p->second.getMap();
				}
			}
			else {
				return defaultv;
			}
			++index;
		}
		return defaultv;
	}

	s32 Configuration::gets32(const str &cPath, const s32 defaultv) const
	{
		return static_cast<s32>(get(cPath, DataValue{ defaultv }).gets32());
	}

}
