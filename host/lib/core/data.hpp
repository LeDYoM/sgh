#ifndef LIB_DATA_HPP__
#define LIB_DATA_HPP__

#include <lib/include/types.hpp>
#include <lib/include/compconfig.hpp>
#include <map>
#include <vector>

namespace lib
{
	class DataValue;
	typedef LIB_API std::map<str, DataValue> DataMap;
	enum class LIB_API DataType : u8
	{
		T_Empty,
		T_s32,
		T_f64,
		T_string,
		T_Tree
	};

	class LIB_API DataValue
	{
	public:
		explicit DataValue();
		DataValue(s32 value_);
		DataValue(f64 value_);
		DataValue(const str &value_);
		explicit DataValue(const DataMap &value_);
		DataValue(const DataValue &other);
		DataValue(DataValue &&other);
		virtual ~DataValue();

		DataValue &operator=(s32 value_);
		DataValue &operator=(f64 value_);
		DataValue &operator=(const str &value_);
		DataValue &operator=(const DataMap &value_);
		DataValue &operator=(const DataValue &other);
		DataValue &operator=(DataValue &&other);

		const s32 gets32() const;
		const f64 getf64() const;
		const str getString() const;
		const DataMap *getMap() const;
		DataMap *getMap();
		const str toString() const;

		static DataValue fromStringVector(const std::vector<str> &data, u32 &count);

	private:
		class DataValuePrivate;
		DataValuePrivate *m_private;
	};
}

#endif
