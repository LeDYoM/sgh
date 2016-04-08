#include "data.hpp"
#include "log.hpp"

#include <fstream>
#include "strutils.hpp"

namespace lib
{
	class DataValue::DataValuePrivate
	{
	public:

		DataValuePrivate(const DataType dtype=DataType::T_Empty)
			: m_dtype{ dtype }
		{
			switch (m_dtype)
			{
			case DataType::T_f64:
			case DataType::T_s32:
			case DataType::T_Empty:
				break;
			case DataType::T_string:
				break;
			case DataType::T_Tree:
				break;
			default:
				break;
			}
		}

		DataValuePrivate::DataValuePrivate(s32 value_)
			: DataValuePrivate(DataType::T_s32)
		{
			s32_ = value_;
		}

		DataValuePrivate::DataValuePrivate(f64 value_)
			: DataValuePrivate(DataType::T_f64)
		{
			f64_ = value_;
		}

		DataValuePrivate::DataValuePrivate(const str &value_)
			: DataValuePrivate(DataType::T_string)
		{
			ptr_ = new str(value_);
		}


		DataValuePrivate::DataValuePrivate(const DataMap &value_)
			: DataValuePrivate(DataType::T_Tree)
		{
			ptr_ = new DataMap(value_);
		}

		DataValuePrivate::DataValuePrivate(const DataValuePrivate &value_)
			: DataValuePrivate(value_.m_dtype)
		{
			switch (m_dtype)
			{
			case DataType::T_Empty:
				break;
			case DataType::T_s32:
				s32_ = value_.s32_;
				break;
			case DataType::T_f64:
				f64_ = value_.f64_;
				break;
			case DataType::T_string:
				ptr_ = new str(*(reinterpret_cast<str*>(value_.ptr_)));
				break;
			case DataType::T_Tree:
				ptr_ = new DataMap(*(reinterpret_cast<DataMap*>(value_.ptr_)));
				break;
			default:
				break;
			}
		}

		~DataValuePrivate()
		{
			switch (m_dtype)
			{
			case DataType::T_s32:
			case DataType::T_f64:
			case DataType::T_Empty:
				break;
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

		union
		{
			s32 s32_;
			f64 f64_;
			void *ptr_;
		};
		DataType m_dtype{ DataType::T_Empty };
	};

	DataValue::DataValue()
		: m_private{nullptr}
	{
	}

	DataValue::DataValue(s32 value_)
		: m_private{ new DataValue::DataValuePrivate(value_) }
	{
	}

	DataValue::DataValue(f64 value_)
		: m_private{ new DataValue::DataValuePrivate(value_) }
	{
	}

	DataValue::DataValue(const str &value_)
		: m_private{ new DataValue::DataValuePrivate(value_) }
	{
	}

	DataValue::DataValue(const DataMap &value_)
		: m_private{ new DataValue::DataValuePrivate(value_) }
	{
	}

	DataValue::DataValue(const DataValue &other)
		: m_private{ new DataValue::DataValuePrivate(*other.m_private) }
	{

	}

	DataValue::DataValue(DataValue &&other)
		: m_private{ std::move(other.m_private) }
	{
		other.m_private = nullptr;
	}

	DataValue::~DataValue()
	{
		if (m_private)
			delete m_private;
	}

	DataValue & DataValue::operator=(s32 value_)
	{
		if (m_private)
			delete m_private;

		m_private = new DataValuePrivate(value_);
		return *this;
	}

	DataValue & DataValue::operator=(f64 value_)
	{
		if (m_private)
			delete m_private;

		m_private = new DataValuePrivate(value_);
		return *this;
	}

	DataValue &DataValue::operator=(const str &value_)
	{
		if (m_private)
			delete m_private;

		m_private = new DataValuePrivate(value_);
		return *this;
	}

	DataValue & DataValue::operator=(const DataMap &value_)
	{
		if (m_private)
			delete m_private;

		m_private = new DataValuePrivate(value_);
		return *this;
	}

	DataValue &DataValue::operator=(const DataValue &other)
	{
		if (m_private)
			delete m_private;

		m_private = new DataValuePrivate(*(other.m_private));
		return *this;
	}

	DataValue &DataValue::operator=(DataValue &&other)
	{
		if (m_private)
			delete m_private;

		m_private = std::move(other.m_private);
		other.m_private = nullptr;
		return *this;
	}

	const s32 DataValue::gets32() const
	{
		if (m_private->m_dtype == DataType::T_s32)
			return m_private->s32_;
		else if (m_private->m_dtype == DataType::T_f64)
			return static_cast<s32>(m_private->f64_);
		else
			return s32();
	}

	const f64 DataValue::getf64() const
	{
		if (m_private->m_dtype == DataType::T_s32)
			return static_cast<f64>(m_private->s32_);
		else if (m_private->m_dtype == DataType::T_f64)
			return m_private->f64_;
		else
			return f64();
	}

	const str DataValue::getString() const                                 
	{
		if (m_private->m_dtype == DataType::T_s32)
			return std::to_string(gets32()).c_str();
		else if (m_private->m_dtype == DataType::T_f64)
			return std::to_string(getf64()).c_str();
		else if (m_private->m_dtype == DataType::T_string)
			return *(reinterpret_cast<str*>(m_private->ptr_));
		else
			return "";
	}

	const DataMap *DataValue::getMap() const
	{
		if (m_private->m_dtype == DataType::T_Tree)
			return reinterpret_cast<DataMap*>(m_private->ptr_);
		else
			return nullptr;
	}

	DataMap *DataValue::getMap()
	{
		if (m_private->m_dtype == DataType::T_Tree)
			return reinterpret_cast<DataMap*>(m_private->ptr_);
		else
			return nullptr;
	}

	const str DataValue::toString() const
	{
		if (m_private->m_dtype == DataType::T_Empty)
			return "T_Empty: ()";
		else if (m_private->m_dtype == DataType::T_s32)
			return "T_s32: " + getString();
		else if (m_private->m_dtype == DataType::T_f64)
			return "T_f64: " + getString();
		else if (m_private->m_dtype == DataType::T_string)
			return "T_string: " + getString();
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
