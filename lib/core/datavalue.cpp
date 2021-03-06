#include "datavalue.hpp"
#include "datamap.hpp"
#include "log.hpp"

#include "strutils.hpp"

#define SW_CONV_BOOL(T) case DataType::T_bool:	\
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

	DataValue::DataValue(const DataMap &value_)
		: m_dtype{ DataType::T_Tree }, ptr_{ new DataMap(value_) } {}

	DataValue::DataValue(const DataValue &value_) : m_dtype{ value_.m_dtype }
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
		return false;
	}

	const s8 DataValue::gets8() const
	{
		switch (m_dtype)
		{
			SW_CONV_BOOL(s8);
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
			SW_CONV_BOOL(u8);
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
			SW_CONV_BOOL(u8);
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
			SW_CONV_BOOL(u8);
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
			SW_CONV_BOOL(s32);
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
			SW_CONV_BOOL(u32);
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
			SW_CONV_BOOL(f64);
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

	std::ostream &operator<<(std::ostream &output, const DataValue &this_)
	{
		switch (this_.m_dtype)
		{
		case (DataType::T_Empty):
				output << "T_Empty: ()";
			break;
		case DataType::T_s8:
			output << "T_s8: " << this_.s8_;
			break;
		case DataType::T_u8:
			output << "T_u8: " << this_.u8_;
			break;
		case DataType::T_s16:
			output << "T_s16: " << this_.s16_;
			break;
		case DataType::T_u16:
			output << "T_u16: " << this_.u16_;
			break;
		case DataType::T_s32:
			output << "T_s32: " << this_.s32_;
			break;
		case DataType::T_u32:
			output << "T_u32: " << this_.u32_;
			break;
		case DataType::T_f64:
			output << "T_f64: " << this_.f64_;
			break;
		case DataType::T_string:
			output << "T_string: " << this_.getString();
			break;
		case DataType::T_Tree:
			output << "T_TreeNode: \n";// << std::to_string((u32)(this_.ptr_));
			for (const auto&element : *(this_.getMap()))
			{
				output << element.first << ":\n" << element.second;
			}
			break;
		default:
			output << "T_Unknown: (?)";
		}
		return output;
	}

	DataValue fromString_helper(const str &str_)
	{
		if (is_int(str_)) {
			return DataValue{ std::stoi(str_) };
		} 
		else if (is_number(str_)) {
			return DataValue{ std::stod(str_) };
		}
		else if (is_bool(str_)) {
			return DataValue{ to_bool(str_) };
		}
		else {
			return DataValue{ str_ };
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
					current[currentSection] = DataValue{ fromStringVector(data, ++count) };
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
