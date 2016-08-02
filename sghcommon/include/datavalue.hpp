#ifndef LIB_DATAVALUE_HPP__
#define LIB_DATAVALUE_HPP__

#include <lib/include/types.hpp>
#include <lib/include/compconfig.hpp>

namespace lib
{
	class DataMap;

	enum class LIB_API DataType : u8
	{
		T_Empty,
		T_bool,
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
		explicit inline DataValue(const bool value_) : m_dtype{ DataType::T_bool }, s8_{ value_ } {}
		explicit inline DataValue(const s8 value_) : m_dtype{ DataType::T_s8 }, s8_{ value_ } {}
		explicit inline DataValue(const u8 value_) : m_dtype{ DataType::T_u8 }, u8_{ value_ } {}
		explicit inline DataValue(const s16 value_) : m_dtype{ DataType::T_s16 }, s16_{ value_ } {}
		explicit inline DataValue(const u16 value_) : m_dtype{ DataType::T_u16 }, u16_{ value_ } {}
		explicit inline DataValue(const s32 value_) : m_dtype{ DataType::T_s32 }, s32_{ value_ } {}
		explicit inline DataValue(const u32 value_) : m_dtype{ DataType::T_u32 }, u32_{ value_ } {}
		explicit inline DataValue(const f64 value_) : m_dtype{ DataType::T_f64 }, f64_{ value_ } {}
		explicit inline DataValue(const str &value_) : m_dtype{ DataType::T_string }, ptr_{ new str(value_) } {}
		explicit DataValue(const DataMap &value_);
		explicit DataValue(const DataValue &value_);

		inline DataValue(DataValue &&other)
		{
			std::swap(m_dtype, other.m_dtype);
			f64_ = other.f64_;
		}

		inline DataValue &operator=(const DataValue &rh)
		{
			DataValue temp{ rh };
			std::swap(*this, temp);
			return *this;
		}
		
		~DataValue();

		bool operator==(const bool value_) const;
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

		const bool getbool() const;
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
		template <> inline const bool get() const { return getbool(); }
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
			bool bool_;
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
