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
			using std::string;

			switch (m_dtype)
			{
			case DataType::T_f64:
			case DataType::T_s32:
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
			*(reinterpret_cast<std::string*>(ptr_)) = value_;
		}


		DataValuePrivate::DataValuePrivate(const DataMap &value_)
			: DataValuePrivate(DataType::T_string)
		{
			*(reinterpret_cast<DataMap*>(ptr_)) = value_;
		}

		~DataValuePrivate()
		{
			using std::string;

			switch (m_dtype)
			{
			case DataType::T_f64:
			case DataType::T_s32:
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
		: m_private{new DataValue::DataValuePrivate}
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
	{
		*this = value_;
	}

	DataValue::~DataValue()
	{
		if (m_private)
			delete m_private;
	}
	/*
	template <class T>
	sptr<int> toData(const T&data_)
	{
		return sptr<int>(std::dynamic_pointer_cast<T>(sptr<T>(new T{ data_ })));
	}

	template <class T>
	sptr<T> fromData(sptr<int> data_)
	{
		return std::dynamic_pointer_cast<T>(data_);
	}
*/
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

	DataValue & DataValue::operator=(const str &value_)
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
			return s32();
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

	void DataValue::loadFile(const std::string &file)
	{
		LOG_DEBUG("Trying to read file "+file);
		std::ifstream f(file);

		if (f.is_open())
		{
			while (f)
			{
				std::string line;
				f >> line;
				trim(line);
				if (line.size() > 0)
				{
					auto left(line);
					auto right(line);

					leftFrom(left, "=");
					trim(left);
					rightFrom(right, "=");
					trim(right);
					if (left.size() > 0 && right.size() > 0)
					{
						DataValue val;
						if (right[0] == '"')
						{
							val = right.substr(1);
						}
						else if (contains(right, "."))
						{
							val = std::stod(right);
						}
						else
						{
							val = std::stoi(right);
						}
						LOG_DEBUG("Adding key" << left << " with value " << val.toString());
					}
				}
			}
		}
	}
}
