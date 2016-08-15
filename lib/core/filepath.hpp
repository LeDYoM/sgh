#ifndef LIB_FILEPATH_HPP
#define LIB_FILEPATH_HPP

#include <lib/include/types.hpp>

namespace lib
{
	namespace core
	{
		class FilePath
		{
		public:
			using size_type = str::size_type;

			FilePath() = delete;
			FilePath(const FilePath&) = default;
			FilePath(FilePath&&) = default;

			FilePath &operator=(const FilePath&) = default;
			FilePath &operator=(FilePath&&) = default;

			FilePath(const str&, const s8 = '/');
			~FilePath() = default;

			void setPath(const str &newdp);
			const str fileName() const;
			const str fileNameExtension() const;
			inline bool empty() const { return m_data.empty(); }

			const str c_str() const;
		private:
			std::vector<str> m_data;
			const s8 m_separator;
		};
	}
}

#endif
