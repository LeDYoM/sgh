#include "data.hpp"
#include "log.hpp"

#include <fstream>
#include "strutils.hpp"

namespace lib
{
	DataValue::DataValue()
	{
	}

	DataValue::DataValue(s32 value_)
	{
		*this = value_;
	}

	DataValue::DataValue(f64 value_)
	{
		*this = value_;
	}

	DataValue::DataValue(const str &value_)
	{
		*this = value_;
	}

	DataValue::DataValue(const DataMap &value_)
	{
		*this = value_;
	}

	DataValue::~DataValue()
	{
	}

	template <class T>
	sptr<void> toData(const T&data_)
	{
		return sptr<void>(std::dynamic_pointer_cast<void>(sptr<T>(new T{ data_ })));
	}

	DataValue & DataValue::operator=(s32 value_)
	{
		value = toData(value_);
		dtype = DataType::T_s32;
	}

	DataValue & DataValue::operator=(f64 value_)
	{
		value = toData(value_);
		dtype = DataType::T_f64;
	}

	DataValue & DataValue::operator=(const str &value_)
	{
		value = toData(value_);
		dtype = DataType::T_string;
	}

	DataValue & DataValue::operator=(const DataMap &value_)
	{
		value = toData(value_);
		dtype = DataType::T_Tree;
	}

	const s32 DataValue::gets32() const
	{
		if (dtype == DataType::T_s32)
			return *(std::dynamic_pointer_cast<s32>(value));
		else if (dtype == DataType::T_f64)
			return *static_cast<s32>((std::dynamic_pointer_cast<f64>(value)));
		else
			return s32();
	}

	const f64 DataValue::getf64() const
	{
		if (dtype == DataType::T_s32)
			return *static_cast<f64>((std::dynamic_pointer_cast<f64>(value)));
		else if (dtype == DataType::T_f64)
			return *(std::dynamic_pointer_cast<f64>(value));
		else
			return f64();
	}

	const str DataValue::getString() const                                 
	{
		if (dtype == DataType::T_s32)
			return std::to_string(gets32()).c_str();
		else if (dtype == DataType::T_f64)
			return std::to_string(getf64()).c_str();
		else
			return *(std::dynamic_pointer_cast<str>(value));
	}

	sptr<DataMap> DataValue::getMap() const
	{
		if (dtype == DataType::T_Tree)
			return std::dynamic_pointer_cast<DataMap>(value);
		else
			return sptr<DataMap>();
	}

	const str DataValue::toString() const
	{
		if (dtype == DataType::T_Empty)
			return "T_Empty: ()";
		else if (dtype == DataType::T_s32)
			return "T_s32: " + std::to_string(gets32());
		else if (dtype == DataType::T_f64)
			return "T_f64: " + std::to_string(getf64());
		else if (dtype == DataType::T_string)
			return "T_string: " + *(std::dynamic_pointer_cast<str>(value));
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
