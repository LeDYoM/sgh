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
			explicit DataPath(const str &dp, const char separator = '/')
				: m_separator{ separator }
			{
				setPath(dp);
			}

			void setPath(const str &newdp)
			{
				m_nodes.clear();
				std::string m_ndpcpy(newdp);
				bool exit{ false };

				do
				{
					auto sz(m_ndpcpy.find_first_not_of(m_separator));
					m_nodes.push_back(m_ndpcpy.substr(0, sz));
					m_ndpcpy = m_ndpcpy.substr(sz);

				} while (!m_ndpcpy.empty());
			}

			inline auto size() -> decltype(3)
			{
			}

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

	void Configuration::setDefaults(const DataMap &&defaults)
	{
		m_defaults = std::move(defaults);
	}

	DataValue &Configuration::get(const str &cPath)
	{

	}

}
