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
		T_s8,
		T_u8,
		T_s16,
		T_u16,
		T_s32,
		T_u32,
		T_f64,
		T_string,
		T_Tree
	};

	class LIB_API DataValue
	{
	public:
		explicit DataValue();
		DataValue(const s8 value_);
		DataValue(const u8 value_);
		DataValue(const s16 value_);
		DataValue(const u16 value_);
		DataValue(const s32 value_);
		DataValue(const u32 value_);
		DataValue(const f64 value_);
		DataValue(const str &value_);
		DataValue(const DataMap &value_);
		DataValue(const DataValue &other);
		DataValue(DataValue &&other);
		virtual ~DataValue();

		bool operator==(const s8 value_) const;
		bool operator==(const u8 value_) const;
		bool operator==(const s16 value_) const;
		bool operator==(const u16 value_) const;
		bool operator==(const s32 value_) const;
		bool operator==(const u32 value_) const;
		bool operator==(const f64 value_) const;
		bool operator==(const str &value_) const;
		bool operator==(const DataMap &value_) const;
		bool operator==(const DataValue &other) const;
		DataValue &operator=(DataValue &&other);

		const s8 gets8() const;
		const u8 getu8() const;
		const s16 gets16() const;
		const u16 getu16() const;
		const s32 gets32() const;
		const u32 getu32() const;
		const f64 getf64() const;
		const str getString() const;
		const DataMap *getMap() const;
		DataMap *getMap();
		const str toString() const;

		static DataMap fromStringVector(const std::vector<str> &data, u32 &count);

	private:
		union
		{
			s8 s8_;
			u8 u8_;
			s16 s16_;
			u16 u16_;
			s32 s32_;
			u32 u32_;
			f64 f64_;
			void *ptr_;
		};
		DataType m_dtype{ DataType::T_Empty };
	};
}

#endif
