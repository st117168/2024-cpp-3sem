#include "dataset.h"

Dataset::~Dataset()
{
	for (size_t i = 0; i < size_ / data_->size; ++i)
	{
		if (data_[i].type == "int")
		{
			delete[](int*)data_[i].value;
		}
		else if (data_[i].type == "double")
		{
			delete[](double*)data_[i].value;
		}
		else if (data_[i].type == "string")
		{
			delete[](std::string*)data_[i].value;
		}
		else if (data_[i].type == "size_t") 
		{
			delete[](size_t*)data_[i].value;
		}
	}
	delete[] data_;
	size_ = 0;
}

Dataset::Dataset(const std::string& FilePath, bool IndexColumnExistsInFile, Names ColumnNames)
{
	data_ = nullptr;
	size_ = 0;

	//file type determine
	std::string typef = "";
	typef = TypeOfFile(FilePath);

	//open file
	std::ifstream file(FilePath);

	//rows count determine
	size_t row_count = 0;
	row_count = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
	if (ColumnNames.names.empty())
	{
		--row_count;
	}

	//columns count determine
	file.seekg(0, file.beg);
	file.clear();
	std::string line = "";
	std::getline(file, line);
	size_t column_count = 0;
	column_count = CountOfColumns(typef, line);
	if (!IndexColumnExistsInFile)
	{
		++column_count;
	}

	//initialize data_ and size_
	data_ = new Column[column_count];
	size_ = column_count * row_count;

	//skip column names
	if (!ColumnNames.names.empty())
	{
		file.seekg(0, file.beg);
		file.clear();
	}

	//write name and size_ for columns
	if (ColumnNames.names.empty())
	{
		ColumnNames = Names(line);
	}
	for (size_t i = 0; i < column_count; ++i)
	{
		if (i == 0)
		{
			data_[i].name = "";
			data_[i].size = row_count;
		}
		else
		{
			data_[i].name = ColumnNames.names[i - 1];
			data_[i].size = row_count;
		}
	}

	//write index column
	data_->value = new size_t[data_->size];
	data_->type = "size_t";
	for (size_t i = 0; i < data_->size; ++i)
	{
		((size_t*)data_->value)[i] = i;
	}

	//write data
	if (typef == "csv")
	{
		//initializing columns, write first row
		std::getline(file, line);
		std::stringstream ss(line);
		std::string value = "";
		size_t i = 1; // skip index column
		if (IndexColumnExistsInFile)
		{
			std::getline(ss, value, ',');
		}
		while (std::getline(ss, value, ',') && i < size_ / data_->size)
		{
			if (TypeOfVariable(value) == "int")
			{
				data_[i].type = "int";
				data_[i].value = new int[data_->size];
				((int*)data_[i].value)[0] = stoi(value);
			}
			else if (TypeOfVariable(value) == "double")
			{
				data_[i].type = "double";
				data_[i].value = new double[data_->size];
				((double*)data_[i].value)[0] = stod(value);
			}
			else if (TypeOfVariable(value) == "string")
			{
				data_[i].type = "string";
				data_[i].value = new std::string[data_->size];
				((std::string*)data_[i].value)[0] = value;
			}
			++i;
		}
		size_t j = 1; //skip naming row

		//write other rows
		while (std::getline(file, line)) {
			std::stringstream ss(line);
			std::string value = "";
			size_t i = 1; // skip index column
			if (IndexColumnExistsInFile)
			{
				std::getline(ss, value, ',');
			}
			while (std::getline(ss, value, ',') && i < size_ / data_->size && j < data_->size)
			{
				if (data_[i].type == "int")
				{
					((int*)data_[i].value)[j] = stoi(value);
				}
				else if (data_[i].type == "double")
				{
					((double*)data_[i].value)[j] = stod(value);
				}
				else if (data_[i].type == "string")
				{
					((std::string*)data_[i].value)[j] = value;
				}
				else if (data_[i].type == "size_t")
				{
					((size_t*)data_[i].value)[j] = stoi(value);
				}
				++i;
			}
			++j;
		}
	}
	//close file
	file.close();
}

void Dataset::PrintData() const
{
	for (size_t i = 0; i < size_ / data_->size; ++i)
	{
		std::cout << data_[i].name << " ";
	}
	std::cout << '\n';
	for (size_t i = 0; i < data_->size; ++i)
	{
		for (size_t j = 0; j < size_ / data_->size; ++j)
		{

			if (data_[j].type == "int")
			{
				std::cout << ((int*)data_[j].value)[i] << " ";
			}
			else if (data_[j].type == "double")
			{
				std::cout << ((double*)data_[j].value)[i] << " ";
			}
			else if (data_[j].type == "string")
			{
				std::cout << ((std::string*)data_[j].value)[i] << " ";
			}
			else if (data_[j].type == "size_t")
			{
				std::cout << ((size_t*)data_[j].value)[i] << " ";
			}
		}
		std::cout << '\n';
	}
}

static std::string TypeOfFile(const std::string& FilePath)
{
	std::string typef = "";
	for (size_t i = FilePath.size() - 1; i > 0; --i)
	{
		if (FilePath[i] == '.')
		{
			break;
		}
		typef = FilePath[i] + typef;
	}
	return typef;
}

static size_t CountOfColumns(std::string& FileType, std::string& line)
{
	size_t sum = 1;
	if (FileType == "csv")
	{
		for (std::string::iterator it = line.begin(); it != line.end(); ++it)
		{
			if (*it == ',')
			{
				++sum;
			}
		}
	}
	return sum;
}

static std::string TypeOfVariable(std::string str)
{
	for (char i : str)
	{
		if (i == '.')
		{
			return "double";
		}
		if (!(i >= '0' && i <= '9'))
		{
			return "string";
		}
	}
	return "int";
}
