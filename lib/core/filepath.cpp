#include "filepath.hpp"

namespace lib
{
	namespace core
	{
		FilePath::FilePath(const str&fileName, const s8 separator)
			: m_separator{ separator }
		{
			setPath(fileName);
		}

		void FilePath::setPath(const str &newdp)
		{
			m_data.clear();
			str m_ndpcpy{ newdp };

			do {
				auto sz(m_ndpcpy.find_first_of(m_separator));
				m_data.push_back(m_ndpcpy.substr(0, sz));
				m_ndpcpy = m_ndpcpy.substr((sz == str::npos) ? (m_ndpcpy.size()) : (sz + 1));
			} while (!m_ndpcpy.empty());
		}

		const str FilePath::fileName() const
		{
			return m_data.empty() ? "" : *(m_data.end() - 1);
		}

		const str FilePath::fileNameExtension() const
		{
			str fileName(fileName());
			if (!fileName.empty()) {
				size_t pos{ fileName.find(".") };

				return pos == str::npos || pos == fileName.size() - 1 ? "" : fileName.substr(pos + 1);
			}
			return "";
		}

		const str FilePath::c_str() const
		{
			str result;

			for (std::vector<str>::size_type i = 0; i < m_data.size(); ++i) {
				result += m_data[i];
				if (i > 1 && i < (m_data.size() - 1)) {
					result += m_separator;
				}
			}
			return result;
		}
	}
}

