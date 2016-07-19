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
		inline explicit DataValue() : m_dtype{ DataType::T_Empty }, f64_{ 0 } {}
		inline DataValue(const s8 value_) : m_dtype{ DataType::T_s8 }, s8_{ value_ } {}
		inline DataValue(const u8 value_) : m_dtype{ DataType::T_u8 }, u8_{ value_ } {}
		inline DataValue(const s16 value_) : m_dtype{ DataType::T_s16 }, s16_{ value_ } {}
		inline DataValue(const u16 value_) : m_dtype{ DataType::T_u16 }, u16_{ value_ } {}
		inline DataValue(const s32 value_) : m_dtype{ DataType::T_s32 }, s32_{ value_ } {}
		inline DataValue(const u32 value_) : m_dtype{ DataType::T_u32 }, u32_{ value_ } {}
		inline DataValue(const f64 value_) : m_dtype{ DataType::T_f64 }, f64_{ value_ } {}
		inline DataValue(const str &value_) : m_dtype{ DataType::T_string }, ptr_{ new str(value_) } {}
		inline DataValue(const DataMap &value_) : m_dtype{ DataType::T_Tree }, ptr_{ new DataMap(value_) } {}

		inline DataValue(const DataValue &value_) : m_dtype{ value_.m_dtype }
		{
			switch (m_dtype)
			{
				case DataType::T_s8:
				case DataType::T_u8:
				case DataType::T_s16:
				case DataType::T_u16:
				case DataType::T_s32:
				case DataType::T_u32:
				case DataType::T_f64:
					f64_ = value_.f64_;
					break;
				case DataType::T_string:
					ptr_ = new str(value_.getString());
					break;
				case DataType::T_Tree:
					ptr_ = new DataMap(*value_.getMap());
					break;
				case DataType::T_Empty:
				default:
					break;
			}
		}

		inline DataValue(DataValue &&other) : m_dtype{ std::move(other.m_dtype) }, f64_{ std::move(other.f64_) } {}
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

		inline const bool iss8() const { return m_dtype == DataType::T_s8; }
		inline const bool isu8() const { return m_dtype == DataType::T_s8; }
		inline const bool iss16() const { return m_dtype == DataType::T_s16; }
		inline const bool isu16() const { return m_dtype == DataType::T_u16; }
		inline const bool iss32() const { return m_dtype == DataType::T_s32; }
		inline const bool isu32() const { return m_dtype == DataType::T_u32; }
		inline const bool isf64() const { return m_dtype == DataType::T_f64; }
		inline const bool isstring() const { return m_dtype == DataType::T_string; }
		inline const bool ismap() const { return m_dtype == DataType::T_Tree; }

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
