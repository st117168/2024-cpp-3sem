#include "dataset.h"

DataLine::DataLine() : data(""), delimiter(' '), size(0) {}

DataLine::DataLine(std::string data) : data(data), delimiter(' '), size(0) {}

DataLine::DataLine(std::string line, char delimiter, size_t size) : delimiter(delimiter), size(size) 
{
	if (line.at(0) == delimiter)
	{
		line.erase(line.begin());
	}
	line.erase(std::remove(line.begin(), line.end(), '\r' ), line.end());
	data = line;
}

std::string DataLine::operator[](size_t index) const
{
	if (index >= size || index >= data.size())
	{
		return "index out of range";
	}
	std::string output;
	std::stringstream ss(data);
	while (index != -1)
	{
		getline(ss, output, delimiter);
		--index;
	}
	return output;
}

Column::Column() : value(nullptr), size(0), name(""), type(TypeData::kNotDefined) {}

Column::~Column()
{
	value = nullptr;
	size = 0;
	name = "";
}

Dataset::~Dataset()
{
	this->dispose();
}

void Dataset::Remove(size_t index)
{
	if (data_ == nullptr)
	{
		return;
	}
	if (index >= data_->size || data_->size == 0)
	{
		return;
	}
	Dataset dataset_new;
	dataset_new.size_ = size_;
	dataset_new.data_ = new Column[size_];
	dataset_new.data_->size = data_->size - 1;
	bool flag_remove = 0;
	for (size_t i = 0; i < dataset_new.data_->size; ++i)
	{
		if (i == index)
		{
			flag_remove = 1;
		}
		for (size_t j = 0; j < size_; ++j)
		{
			dataset_new.data_[j].size = dataset_new.data_->size;
			dataset_new.data_[j].name = data_[j].name;
			dataset_new.data_[j].type = data_[j].type;
			if (data_[j].type == TypeData::kInt)
			{
				if (dataset_new.data_[j].value == nullptr)
				{
					dataset_new.data_[j].value = new int[dataset_new.data_->size];
				}
				((int*)dataset_new.data_[j].value)[i] = ((int*)data_[j].value)[i + flag_remove];
			}
			else if (data_[j].type == TypeData::kDouble)
			{
				if (dataset_new.data_[j].value == nullptr)
				{
					dataset_new.data_[j].value = new double[dataset_new.data_->size];
				}
				((double*)dataset_new.data_[j].value)[i] = ((double*)data_[j].value)[i + flag_remove];
			}
			else if (data_[j].type == TypeData::kString)
			{
				if (dataset_new.data_[j].value == nullptr)
				{
					dataset_new.data_[j].value = new std::string[dataset_new.data_->size];
				}
				((std::string*)dataset_new.data_[j].value)[i] = ((std::string*)data_[j].value)[i + flag_remove];
			}
		}
	}
	*this = dataset_new;
}

Dataset::Dataset(std::string FilePath, bool IndexColumnExistsInFile, DataLine ColumnNames)
{
	data_ = nullptr;
	size_ = 0;
	delimiter_for_print_ = '\t';

	//file type determine
	TypeFile typef = TypeFile::kNotDefined;
	typef = TypeOfFile(FilePath);

	//open file
	std::ifstream file(FilePath);

	//rows count determine
	size_t row_count = 0;
	row_count = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
	if (ColumnNames.data.empty())
	{
		--row_count;
	}

	//columns count determine
	file.seekg(0, file.beg);
	file.clear();
	std::string line = "";
	std::getline(file, line);
	size_t column_count = 0;
	column_count = CountOfColumns(DelimiterSymbol(typef), line);
	if (IndexColumnExistsInFile)
	{
		--column_count;
	}

	//initialize data_ and size_
	data_ = new Column[column_count];
	size_ = column_count;

	//skip column names
	if (!ColumnNames.data.empty())
	{
		file.seekg(0, file.beg);
		file.clear();
	}

	//write name and size_ for columns
	if (ColumnNames.data.empty())
	{
		ColumnNames = DataLine(line, DelimiterSymbol(typef), size_);
	}
	for (size_t i = 0; i < size_ && i < ColumnNames.size; ++i)
	{
		data_[i].name = ColumnNames[i];
		data_[i].size = row_count;
	}
	if (data_->size == 0)
	{
		return;
	}

	//write data
	size_t j = 0;
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string value = "";
		size_t i = 0;
		if (IndexColumnExistsInFile)
		{
			std::getline(ss, value, DelimiterSymbol(typef));
		}
		while (std::getline(ss, value, DelimiterSymbol(typef)) && i < size_ && j < data_->size)
		{
			if (data_[i].value == nullptr)
			{
				data_[i].type = TypeOfVariable(value);
				if (TypeOfVariable(value) == TypeData::kInt)
				{
					data_[i].value = new int[data_->size];
				}
				else if (TypeOfVariable(value) == TypeData::kDouble)
				{
					data_[i].value = new double[data_->size];
				}
				else if (TypeOfVariable(value) == TypeData::kString)
				{
					data_[i].value = new std::string[data_->size];
				}
			}

			if (data_[i].type == TypeData::kInt)
			{
				((int*)data_[i].value)[j] = stoi(value);
			}
			else if (data_[i].type == TypeData::kDouble)
			{
				((double*)data_[i].value)[j] = stod(value);
			}
			else if (data_[i].type == TypeData::kString)
			{
				((std::string*)data_[i].value)[j] = value;
			}
			++i;
		}
		++j;
	}
	//close file
	file.close();
}

void Dataset::PrintData() const
{
	if (data_ == nullptr)
	{
		return;
	}
	std::cout << 'i' << delimiter_for_print_;
	for (size_t i = 0; i < size_ - 1; ++i)
	{
		std::cout << data_[i].name << delimiter_for_print_;
	}
	std::cout << data_[size_ - 1].name << '\n';
	for (size_t i = 0; i < data_->size; ++i)
	{
		std::cout << i << delimiter_for_print_ << (*this)[i] << '\n';
	}
	std::cout << '\n';
}

size_t Dataset::GetColumnCount() const
{
    return size_;
}

size_t Dataset::GetRowCount(size_t index) const
{
	if (data_ == nullptr)
	{
		return 0;
	}
	else if (index >= size_)
	{
		return 0;
	}
    return data_[index].size;
}

TypeData Dataset::GetColumnType(size_t index) const
{
	if (data_ == nullptr)
	{
		return TypeData::kNotDefined;
	}
	else if (index >= size_)
	{
		return TypeData::kNotDefined;
	}
    return data_[index].type;
}

std::string Dataset::GetColumnName(size_t index) const
{
	if (data_ == nullptr)
	{
		return "";
	}
	else if (index >= size_)
	{
		return "";
	}
    return data_[index].name;
}

void Dataset::dispose()
{
	if (data_ != nullptr)
	{
		if (data_->value != nullptr)
		{

			for (size_t i = 0; i < data_->size; ++i)
			{
				if (data_[i].type == TypeData::kInt)
				{
					delete[](int*)data_[i].value;
				}
				else if (data_[i].type == TypeData::kDouble)
				{
					delete[](double*)data_[i].value;
				}
				else if (data_[i].type == TypeData::kString)
				{
					delete[](std::string*)data_[i].value;
				}
			}
		}
		delete[] data_;
	}
	size_ = 0;
}

Dataset& Dataset::operator=(const Dataset& dataset)
{
	this->dispose();
	size_ = dataset.size_;
	data_ = new Column[dataset.size_];
	data_->size = dataset.data_->size;
	for (size_t i = 0; i < data_->size; ++i)
	{
		for (size_t j = 0; j < size_; ++j)
		{
			data_[j].size = data_->size;
			data_[j].name = dataset.data_[j].name;
			data_[j].type = dataset.data_[j].type;
			if (dataset.data_[j].type == TypeData::kInt)
			{
				data_[j].type = TypeData::kInt;
				if (data_[j].value == nullptr)
				{
					data_[j].value = new int[data_->size];
				}
				((int*)data_[j].value)[i] = ((int*)dataset.data_[j].value)[i];
			}
			else if (data_[j].type == TypeData::kDouble)
			{
				data_[j].type = TypeData::kDouble;
				if (data_[j].value == nullptr)
				{
					data_[j].value = new double[data_->size];
				}
				((double*)data_[j].value)[i] = ((double*)dataset.data_[j].value)[i];
			}
			else if (data_[j].type == TypeData::kString)
			{
				data_[j].type = TypeData::kString;
				if (data_[j].value == nullptr)
				{
					data_[j].value = new std::string[data_->size];
				}
				((std::string*)data_[j].value)[i] = ((std::string*)dataset.data_[j].value)[i];
			}
		}
	}
	return *this;
}

DataLine Dataset::operator[](size_t index) const
{
	if (data_ == nullptr)
	{
		return DataLine("index out of range");
	}
	if (data_->size == 0 || index >= data_->size)
	{
		return DataLine("index out of range");
	}
	std::stringstream ss;
	for (size_t i = 0; i < size_ - 1; ++i)
	{
		if (data_[i].type == TypeData::kInt)
		{
			ss << ((int*)data_[i].value)[index] << delimiter_for_print_;
		}
		else if (data_[i].type == TypeData::kDouble)
		{
			ss << ((double*)data_[i].value)[index] << delimiter_for_print_;
		}
		else if (data_[i].type == TypeData::kString)
		{
			ss << ((std::string*)data_[i].value)[index] << delimiter_for_print_;
		}
	}
	if (data_[size_ - 1].type == TypeData::kInt)
	{
		ss << ((int*)data_[size_ - 1].value)[index];
	}
	else if (data_[size_ - 1].type == TypeData::kDouble)
	{
		ss << ((double*)data_[size_ - 1].value)[index];
	}
	else if (data_[size_ - 1].type == TypeData::kString)
	{
		ss << ((std::string*)data_[size_ - 1].value)[index];
	}
	DataLine output_line(ss.str(), delimiter_for_print_, size_);
	return output_line;
}

void Dataset::ChangeDelimiterForPrint(char delimiter)
{
	delimiter_for_print_ = delimiter;
}

void Dataset::Head(size_t n) const
{
	if (data_ == nullptr)
	{
		return;
	}
	if (n > data_->size)
	{
		n = data_->size;
	}
	std::cout << 'i' << delimiter_for_print_;
	for (size_t i = 0; i < size_ - 1; ++i)
	{
		std::cout << data_[i].name << delimiter_for_print_;
	}
	std::cout << data_[size_ - 1].name << '\n';
	for (size_t i = 0; i < n; ++i)
	{
		std::cout << i << delimiter_for_print_ << (*this)[i] << '\n';
	}
	std::cout << '\n';
}

void Dataset::Tail(size_t n) const
{
	if (data_ == nullptr)
	{
		return;
	}
	if (n > data_->size)
	{
		n = data_->size;
	}
	std::cout << 'i' << delimiter_for_print_;
	for (size_t i = 0; i < size_ - 1; ++i)
	{
		std::cout << data_[i].name << delimiter_for_print_;
	}
	std::cout << data_[size_ - 1].name << '\n';
	for (size_t i = data_->size - n; i < data_->size; ++i)
	{
		std::cout << i << delimiter_for_print_ << (*this)[i] << '\n';
	}
	std::cout << '\n';
}

void Dataset::Insert(size_t index, DataLine data_line)
{
	if (data_ != nullptr)
	{
		if (index >= data_->size || data_->size == 0 || data_line.size != size_)
		{
			return;
		}
		std::stringstream ss(data_line.data);
		std::string value = "";
		for (size_t i = 0; i < size_; ++i)
		{
			std::getline(ss, value, data_line.delimiter);
			if (TypeOfVariable(value) != data_[i].type)
			{
				return;
			}
		}

		Dataset dataset_new;
		dataset_new.size_ = size_;
		dataset_new.data_ = new Column[size_];
		dataset_new.data_->size = data_->size + 1;
		bool flag_add = 0;
		for (size_t i = 0; i < data_->size; ++i)
		{
			if (i == index)
			{
				flag_add = 1;
			}
			for (size_t j = 0; j < size_; ++j)
			{
				dataset_new.data_[j].size = dataset_new.data_->size;
				dataset_new.data_[j].name = data_[j].name;
				dataset_new.data_[j].type = data_[j].type;
				if (data_[j].type == TypeData::kInt)
				{
					if (dataset_new.data_[j].value == nullptr)
					{
						dataset_new.data_[j].value = new int[dataset_new.data_->size];
					}
					((int*)dataset_new.data_[j].value)[i + flag_add] = ((int*)data_[j].value)[i];
				}
				else if (data_[j].type == TypeData::kDouble)
				{
					if (dataset_new.data_[j].value == nullptr)
					{
						dataset_new.data_[j].value = new double[dataset_new.data_->size];
					}
					((double*)dataset_new.data_[j].value)[i + flag_add] = ((double*)data_[j].value)[i];
				}
				else if (data_[j].type == TypeData::kString)
				{
					if (dataset_new.data_[j].value == nullptr)
					{
						dataset_new.data_[j].value = new std::string[dataset_new.data_->size];
					}
					((std::string*)dataset_new.data_[j].value)[i + flag_add] = ((std::string*)data_[j].value)[i];
				}
			}
		}
		//write new row
		ss.seekg(ss.beg);
		for (size_t i = 0; i < dataset_new.size_; ++i)
		{
			std::getline(ss, value, data_line.delimiter);
			if (dataset_new.data_[i].type == TypeData::kInt)
			{
				((int*)dataset_new.data_[i].value)[index] = stoi(value);
			}
			else if (dataset_new.data_[i].type == TypeData::kDouble)
			{
				((double*)dataset_new.data_[i].value)[index] = stod(value);
			}
			else if (dataset_new.data_[i].type == TypeData::kString)
			{
				((std::string*)dataset_new.data_[i].value)[index] = value;
			}
		}
		*this = dataset_new;
	}
	else
	{
		//create data_
		size_ = data_line.size;
		data_ = new Column[size_];
		std::stringstream ss(data_line.data);
		std::string value = "";
		for (size_t i = 0; i < size_; ++i)
		{
			std::getline(ss, value, data_line.delimiter);
			data_[i].size = 1;
			data_[i].type = TypeOfVariable(value);
			if (TypeOfVariable(value) == TypeData::kInt)
			{
				data_[i].value = new int[data_->size];
			}
			else if (TypeOfVariable(value) == TypeData::kDouble)
			{
				data_[i].value = new double[data_->size];
			}
			else if (TypeOfVariable(value) == TypeData::kString)
			{
				data_[i].value = new std::string[data_->size];
			}

			if (data_[i].type == TypeData::kInt)
			{
				*((int*)data_[i].value) = stoi(value);
			}
			else if (data_[i].type == TypeData::kDouble)
			{
				*((double*)data_[i].value) = stod(value);
			}
			else if (data_[i].type == TypeData::kString)
			{
				*((std::string*)data_[i].value) = value;
			}
		}
	}
}

TypeFile TypeOfFile(const std::string FilePath)
{
	std::string str = "";
	for (size_t i = FilePath.size() - 1; i != 0; --i)
	{
		if (FilePath[i] == '.')
		{
			break;
		}
		str = FilePath[i] + str;
	}
	if (str == "txt")
	{
		return TypeFile::kTxt;
	}
	if (str == "csv")
	{
		return TypeFile::kCsv;
	}
	return TypeFile::kNotDefined;
}

size_t CountOfColumns(char delimiter, std::string line)
{
	size_t sum = 1;
	for (std::string::iterator it = line.begin(); it != line.end(); ++it)
	{
		if (*it == delimiter)
		{
			++sum;
		}
	}
	return sum;
}

TypeData TypeOfVariable(std::string str)
{
	for (char i : str)
	{
		if (i == '.')
		{
			return TypeData::kDouble;
		}
		if (!(i >= '0' && i <= '9'))
		{
			return TypeData::kString;
		}
	}
	return TypeData::kInt;
}

char DelimiterSymbol(TypeFile typef)
{
	if (typef == TypeFile::kCsv)
	{
		return ',';
	}
	if (typef == TypeFile::kTxt)
	{
		return ' ';
	}
	return ' ';
}

std::string Column::Max() const
{
	if (size == 0)
	{
		return "column is empty";
	}
	void* result = value;
	if (type == TypeData::kInt)
	{
		static_cast<int*>(result);
	}
	else if (type == TypeData::kDouble)
	{
		static_cast<double*>(result);
	}
	else if (type == TypeData::kString)
	{
		static_cast<std::string*>(result);
	}
	else
	{
		return "type not allowed";
	}
	for (size_t i = 0; i < size; ++i)
	{
		if (type == TypeData::kInt)
		{
			result = (*(int*)result < ((int*)value)[i] ? &((int*)value)[i] : result);
		}
		else if (type == TypeData::kDouble)
		{
			result = (*(double*)result < ((double*)value)[i] ? &((double*)value)[i] : result);
		}
		else if (type == TypeData::kString)
		{
			result = ((*(std::string*)result).size() < ((std::string*)value)[i].size() ? &((std::string*)value)[i] : result);
		}
	}
	if (type == TypeData::kInt)
	{
		return std::to_string(*(int*)result);
	}
	else if (type == TypeData::kDouble)
	{
		return std::to_string(*(double*)result);
	}
	else if (type == TypeData::kString)
	{
		return *(std::string*)result;
	}
	return "error";
}

std::string Column::Min() const
{
	if (size == 0)
	{
		return "column is empty";
	}
	void* result = value;
	if (type == TypeData::kInt)
	{
		static_cast<int*>(result);
	}
	else if (type == TypeData::kDouble)
	{
		static_cast<double*>(result);
	}
	else if (type == TypeData::kString)
	{
		static_cast<std::string*>(result);
	}
	else
	{
		return "type not allowed";
	}
	for (size_t i = 0; i < size; ++i)
	{
		if (type == TypeData::kInt)
		{
			result = (*(int*)result > ((int*)value)[i] ? &((int*)value)[i] : result);
		}
		else if (type == TypeData::kDouble)
		{
			result = (*(double*)result > ((double*)value)[i] ? &((double*)value)[i] : result);
		}
		else if (type == TypeData::kString)
		{
			result = ((*(std::string*)result).size() > ((std::string*)value)[i].size() ? &((std::string*)value)[i] : result);
		}
	}
	if (type == TypeData::kInt)
	{
		return std::to_string(*(int*)result);
	}
	else if (type == TypeData::kDouble)
	{
		return std::to_string(*(double*)result);
	}
	else if (type == TypeData::kString)
	{
		return *(std::string*)result;
	}
	return "error";
}

std::string Column::Average() const
{
	if (size == 0)
	{
		return "column is empty";
	}
	if (type != TypeData::kInt && type != TypeData::kDouble && type != TypeData::kString)
	{
		return "type not allowed";
	}
	long double sum = 0.0l;
	for (size_t i = 0; i < size; ++i)
	{
		if (type == TypeData::kInt)
		{
			sum += ((int*)value)[i];
		}
		else if (type == TypeData::kDouble)
		{
			sum += ((double*)value)[i];
		}
		else if (type == TypeData::kString)
		{
			sum += ((std::string*)value)[i].size();
		}
	}
	sum /= size;
	return std::to_string(sum);
}

std::string Column::StandardDeviation() const
{
	if (size == 0)
	{
		return "column is empty";
	}
	if (type != TypeData::kInt && type != TypeData::kDouble && type != TypeData::kString)
	{
		return "type not allowed";
	}
	long double result = 0.0l;
	long double average = 0.0l;
	average = stold(Average());
	for (size_t i = 0; i < size; ++i)
	{
		if (type == TypeData::kInt)
		{
			result += powl(((int*)value)[i] - average, 2);
		}
		else if (type == TypeData::kDouble)
		{
			result += powl(((double*)value)[i] - average, 2);
		}
		else if (type == TypeData::kString)
		{
			result += powl(((std::string*)value)[i].size() - average, 2);
		}

	}
	result /= (size - 1);
	result = sqrtl(result);
	return std::to_string(result);
}

void Dataset::Describe(std::string column_name) const
{
	for (size_t i = 0; i < size_; ++i)
	{
		if (data_[i].name == column_name)
		{
			printf("Description \"%s\" column:\nmin: %s\nmax: %s\naverage: %s\nstandart deviation: %s\n\n",
				column_name.c_str(), data_[i].Max().c_str(), data_[i].Min().c_str(), data_[i].Average().c_str(), data_[i].StandardDeviation().c_str());
			return;
		}
	}
	std::cout << "describe error";
}
