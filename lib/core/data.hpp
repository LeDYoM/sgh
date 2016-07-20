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
		explicit inline DataValue() : m_dtype{ DataType::T_Empty }, f64_{ 0 } {}
		explicit inline DataValue(const s8 value_) : m_dtype{ DataType::T_s8 }, s8_{ value_ } {}
		explicit inline DataValue(const u8 value_) : m_dtype{ DataType::T_u8 }, u8_{ value_ } {}
		explicit inline DataValue(const s16 value_) : m_dtype{ DataType::T_s16 }, s16_{ value_ } {}
		explicit inline DataValue(const u16 value_) : m_dtype{ DataType::T_u16 }, u16_{ value_ } {}
		explicit inline DataValue(const s32 value_) : m_dtype{ DataType::T_s32 }, s32_{ value_ } {}
		explicit inline DataValue(const u32 value_) : m_dtype{ DataType::T_u32 }, u32_{ value_ } {}
		explicit inline DataValue(const f64 value_) : m_dtype{ DataType::T_f64 }, f64_{ value_ } {}
		explicit inline DataValue(const str &value_) : m_dtype{ DataType::T_string }, ptr_{ new str(value_) } {}
		explicit inline DataValue(const DataMap &value_) : m_dtype{ DataType::T_Tree }, ptr_{ new DataMap(value_) } {}

		explicit inline DataValue(const DataValue &value_): m_dtype{ value_.m_dtype }
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

		inline DataValue(DataValue &&other)
		{
			std::swap(m_dtype, other.m_dtype);
			f64_ = other.f64_;
		}
		
		~DataValue();

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

		friend std::ostream &operator<<(std::ostream &output, const DataValue &this_);

		template <typename T> inline const T get() const;

		template <> inline const s8 get() const { return gets8(); }
		template <> inline const u8 get() const { return getu8(); }
		template <> inline const s16 get() const { return gets16(); }
		template <> inline const u16 get() const { return getu16(); }
		template <> inline const s32 get() const { return gets32(); }
		template <> inline const u32 get() const { return getu32(); }
		template <> inline const f64 get() const { return getf64(); }

		inline const bool iss8() const { return m_dtype == DataType::T_s8; }
		inline const bool isu8() const { return m_dtype == DataType::T_s8; }
		inline const bool iss16() const { return m_dtype == DataType::T_s16; }
		inline const bool isu16() const { return m_dtype == DataType::T_u16; }
		inline const bool iss32() const { return m_dtype == DataType::T_s32; }
		inline const bool isu32() const { return m_dtype == DataType::T_u32; }
		inline const bool isf64() const { return m_dtype == DataType::T_f64; }
		inline const bool isstring() const { return m_dtype == DataType::T_string; }
		inline const bool ismap() const { return m_dtype == DataType::T_Tree; }

		template <typename T>
		const bool is() const;

		template <> inline const bool is<s8>() const { return iss8(); }
		template <> inline const bool is<u8>() const { return isu8(); }
		template <> inline const bool is<s16>() const { return iss16(); }
		template <> inline const bool is<u16>() const { return isu16(); }
		template <> inline const bool is<s32>() const { return iss32(); }
		template <> inline const bool is<u32>() const { return isu32(); }
		template <> inline const bool is<f64>() const { return isf64(); }

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
