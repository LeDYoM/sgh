#include "data.hpp"
#include "log.hpp"

//#include <fstream>
#include "strutils.hpp"

#define SW_CONV_BL(T) case DataType::T_bool:	\
						return static_cast<T>(bool_);

#define SW_CONV_S8(T) case DataType::T_s8:	\
						return static_cast<T>(s8_);

#define SW_CONV_U8(T) case DataType::T_u8:	\
						return static_cast<T>(u8_);

#define SW_CONV_S16(T) case DataType::T_s16:	\
						return static_cast<T>(s16_);

#define SW_CONV_U16(T) case DataType::T_u16:	\
						return static_cast<T>(u16_);

#define SW_CONV_S32(T) case DataType::T_s32:	\
						return static_cast<T>(s32_);

#define SW_CONV_U32(T) case DataType::T_u32:	\
						return static_cast<T>(u32_);

#define SW_CONV_F64(T) case DataType::T_f64:	\
						return static_cast<T>(f64_);


namespace lib
{
	DataValue::DataValue()
		: m_dtype{ DataType::T_Empty }
	{
	}

	DataValue::DataValue(const bool value_)
		: m_dtype{ DataType::T_bool }, bool_{ value_ } {}

	DataValue::DataValue(const s8 value_)
		: m_dtype{ DataType::T_s8 }, s8_{ value_ } {}

	DataValue::DataValue(const u8 value_)
		: m_dtype{ DataType::T_u8 }, u8_{ value_ } {}

	DataValue::DataValue(const s16 value_)
		: m_dtype{ DataType::T_s16 }, s16_{ value_ } {}

	DataValue::DataValue(const u16 value_)
		: m_dtype{ DataType::T_u16 }, u16_{ value_ } {}

	DataValue::DataValue(const s32 value_)
		: m_dtype{ DataType::T_s32 }, s32_{ value_ } {}

	DataValue::DataValue(const u32 value_)
		: m_dtype{ DataType::T_u32 }, u32_{ value_ } {}

	DataValue::DataValue(const f64 value_)
		: m_dtype{ DataType::T_f64 }, f64_{ value_ } {}

	DataValue::DataValue(const str &value_)
		: m_dtype{ DataType::T_string }, ptr_{ new str(value_) } {}

	DataValue::DataValue(const DataMap &value_)
		: m_dtype{ DataType::T_Tree }, ptr_{ new DataMap(value_) } {}

	DataValue::DataValue(const DataValue &value_)
		: m_dtype{ value_.m_dtype }
	{
		switch (m_dtype)
		{
		case DataType::T_Empty:
			break;
		case DataType::T_bool:
			bool_ = value_.bool_;
			break;
		case DataType::T_s8:
			s8_ = value_.s8_;
			break;
		case DataType::T_u8:
			u8_ = value_.u8_;
			break;
		case DataType::T_s16:
			s16_ = value_.s16_;
			break;
		case DataType::T_u16:
			u16_ = value_.u16_;
			break;
		case DataType::T_s32:
			s32_ = value_.s32_;
			break;
		case DataType::T_u32:
			u32_ = value_.u32_;
			break;
		case DataType::T_f64:
			f64_ = value_.f64_;
			break;
		case DataType::T_string:
			ptr_ = new str(value_.getString());
			break;
		case DataType::T_Tree:
			ptr_ = new DataMap(*value_.getMap());
			break;
		default:
			break;
		}
	}

	DataValue::~DataValue()
	{
		switch (m_dtype)
		{
		case DataType::T_string:
			delete reinterpret_cast<std::string*>(ptr_);
			break;
		case DataType::T_Tree:
			delete reinterpret_cast<DataMap*>(ptr_);
			break;
		default:
			break;
		}
	}

	DataValue::DataValue(DataValue &&other)
		: m_dtype{ other.m_dtype }
	{
		f64_ = std::move(other.f64_);
		other.m_dtype = DataType::T_Empty;
		other.f64_ = 0;
	}

	DataValue &DataValue::operator=(DataValue &&other)
	{
		m_dtype = other.m_dtype;
		f64_ = other.f64_;
		other.m_dtype = DataType::T_Empty;
		other.f64_ = 0;
		return *this;
	}

	bool DataValue::operator==(const bool value_) const
	{
		if (m_dtype != DataType::T_bool)
			return false;

		return bool_ == value_;
	}

	bool DataValue::operator==(const s8 value_) const
	{
		if (m_dtype != DataType::T_s8)
			return false;

		return s8_ == value_;
	}

	bool DataValue::operator==(const u8 value_) const
	{
		if (m_dtype != DataType::T_u8)
			return false;

		return u8_ == value_;
	}

	bool DataValue::operator==(const s16 value_) const
	{
		if (m_dtype != DataType::T_s16)
			return false;

		return s16_ == value_;
	}

	bool DataValue::operator==(const u16 value_) const
	{
		if (m_dtype != DataType::T_u16)
			return false;

		return u16_ == value_;
	}

	bool DataValue::operator==(const s32 value_) const
	{
		if (m_dtype != DataType::T_s32)
			return false;

		return s32_ == value_;
	}

	bool DataValue::operator==(const u32 value_) const
	{
		if (m_dtype != DataType::T_u32)
			return false;

		return u32_ == value_;
	}

	bool DataValue::operator==(const f64 value_) const
	{
		if (m_dtype != DataType::T_f64)
			return false;

		return f64_ == value_;
	}

	bool DataValue::operator==(const DataMap &value_) const
	{
		value_;
		if (m_dtype != DataType::T_Tree)
			return false;

		// TO DO: FIX ME
//		return getMap() == value_;
		return false;
	}

	bool DataValue::operator==(const str &value_) const
	{
		if (m_dtype != DataType::T_string)
			return false;

		return getString() == value_;
	}

	bool DataValue::operator==(const DataValue &value_) const
	{
		if (m_dtype != value_.m_dtype)
			return false;

		return f64_ == value_.f64_;
	}

	const bool DataValue::getbool() const
	{
		switch (m_dtype)
		{
			SW_CONV_BL(bool);
			SW_CONV_S8(bool);
			SW_CONV_U8(bool);
			SW_CONV_S16(bool);
			SW_CONV_U16(bool);
			SW_CONV_S32(bool);
			SW_CONV_U32(bool);
			SW_CONV_F64(bool);
		default:
			return false;
		}
	}

	const s8 DataValue::gets8() const
	{
		switch (m_dtype)
		{
			SW_CONV_BL(s8);
			SW_CONV_S8(s8);
			SW_CONV_U8(s8);
			SW_CONV_S16(s8);
			SW_CONV_U16(s8);
			SW_CONV_S32(s8);
			SW_CONV_U32(s8);
			SW_CONV_F64(s8);
		default:
			return s8();
		}
	}

	const u8 DataValue::getu8() const
	{
		switch (m_dtype)
		{
			SW_CONV_BL(u8);
			SW_CONV_S8(u8);
			SW_CONV_U8(u8);
			SW_CONV_S16(u8);
			SW_CONV_U16(u8);
			SW_CONV_S32(u8);
			SW_CONV_U32(u8);
			SW_CONV_F64(u8);
		default:
			return u8();
		}
	}

	const s16 DataValue::gets16() const
	{
		switch (m_dtype)
		{
			SW_CONV_BL(s16);
			SW_CONV_S8(s16);
			SW_CONV_U8(s16);
			SW_CONV_S16(s16);
			SW_CONV_U16(s16);
			SW_CONV_S32(s16);
			SW_CONV_U32(s16);
			SW_CONV_F64(s16);
		default:
			return s16();
		}
	}

	const u16 DataValue::getu16() const
	{
		switch (m_dtype)
		{
			SW_CONV_BL(u16);
			SW_CONV_S8(u16);
			SW_CONV_U8(u16);
			SW_CONV_S16(u16);
			SW_CONV_U16(u16);
			SW_CONV_S32(u16);
			SW_CONV_U32(u16);
			SW_CONV_F64(u16);
		default:
			return u16();
		}
	}

	const s32 DataValue::gets32() const
	{
		switch (m_dtype)
		{
			SW_CONV_BL(s32);
			SW_CONV_S8(s32);
			SW_CONV_U8(s32);
			SW_CONV_S16(s32);
			SW_CONV_U16(s32);
			SW_CONV_S32(s32);
			SW_CONV_U32(s32);
			SW_CONV_F64(s32);
		default:
			return s32();
		}
	}

	const u32 DataValue::getu32() const
	{
		switch (m_dtype)
		{
			SW_CONV_BL(u32);
			SW_CONV_S8(u32);
			SW_CONV_U8(u32);
			SW_CONV_S16(u32);
			SW_CONV_U16(u32);
			SW_CONV_S32(u32);
			SW_CONV_U32(u32);
			SW_CONV_F64(u16);
		default:
			return u32();
		}
	}

	const f64 DataValue::getf64() const
	{
		switch (m_dtype)
		{
			SW_CONV_BL(f64);
			SW_CONV_S8(f64);
			SW_CONV_U8(f64);
			SW_CONV_S16(f64);
			SW_CONV_U16(f64);
			SW_CONV_S32(f64);
			SW_CONV_U32(f64);
			SW_CONV_F64(f64);
		default:
			return f64();
		}
	}

	const str DataValue::getString() const                                 
	{
		if (m_dtype == DataType::T_string)
			return *(reinterpret_cast<str*>(ptr_));
		else
			return "";
	}

	const DataMap *DataValue::getMap() const
	{
		if (m_dtype == DataType::T_Tree)
			return reinterpret_cast<DataMap*>(ptr_);
		else
			return nullptr;
	}

	DataMap *DataValue::getMap()
	{
		if (m_dtype == DataType::T_Tree)
			return reinterpret_cast<DataMap*>(ptr_);
		else
			return nullptr;
	}

	const str DataValue::toString() const
	{
		if (m_dtype == DataType::T_Empty)
			return "T_Empty: ()";
		else if (m_dtype == DataType::T_bool)
			return "T_bool: " + std::to_string(bool_);
		else if (m_dtype == DataType::T_s8)
			return "T_s8: " + std::to_string(s8_);
		else if (m_dtype == DataType::T_u8)
			return "T_u8: " + std::to_string(u8_);
		else if (m_dtype == DataType::T_s16)
			return "T_s16: " + std::to_string(s16_);
		else if (m_dtype == DataType::T_u16)
			return "T_u16: " + std::to_string(u16_);
		else if (m_dtype == DataType::T_s32)
			return "T_s32: " + std::to_string(s32_);
		else if (m_dtype == DataType::T_u32)
			return "T_u32: " + std::to_string(u32_);
		else if (m_dtype == DataType::T_f64)
			return "T_f64: " + std::to_string(f64_);
		else if (m_dtype == DataType::T_string)
			return "T_string: " + getString();
		else if (m_dtype == DataType::T_Tree)
			return "T_TreeNode: at " + std::to_string((u32)(ptr_));
		else
			return "T_Unknown: (?)";
	}

	DataValue fromString_helper(const str &str_)
	{
		if (is_int(str_))
		{
			return std::stoi(str_);
		}
		else if (is_number(str_))
		{
			return std::stod(str_);
		}
		else
		{
			return str_;
		}
	}

	std::pair<str, DataValue> fromString(const str &str_)
	{
		str left(str_);
		str right(str_);
		leftFrom(left, "=");
		trim(left);
		rightFrom(right, "=");
		trim(right);
		if (left.size() > 0 && right.size() > 0)
		{
			return{ left, fromString_helper(right) };
		}
		return{};
	}

	DataMap DataValue::fromStringVector(const std::vector<str> &data, u32 &count)
	{
		DataMap current;
		while (count < data.size())
		{
			if (data[count].size() > 0)
			{
				str str_(data[count]);
				trim(str_);

				if (starts_with(str_, "[") && ends_with(str_, "]"))
				{
					str currentSection(str_.substr(1, str_.size() - 2));
					if (starts_with(currentSection, "/"))
					{
						return current;
					}
					current[currentSection] = fromStringVector(data, ++count);
				}
				else
				{
					std::pair<std::string,DataValue> readValue{ fromString(str_) };
					if (!readValue.first.empty())
					{
						current[readValue.first] = std::move(readValue.second);
					}
				}
			}
			++count;
		}
		return current;
	}
}
