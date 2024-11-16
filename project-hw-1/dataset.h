#ifndef DATA_SET_H
#define DATA_SET_H

#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>

enum class TypeData
{
    kInt,
    kDouble,
    kString,
    kNotDefined
};

enum class TypeFile
{
    kTxt,
    kCsv,
    kNotDefined
};

struct DataLine
{
    DataLine();
    DataLine(std::string data);
    DataLine(std::string data, char delimiter, size_t size);

    std::string operator[](size_t index) const;
    friend std::ostream& operator<<(std::ostream& stream, const DataLine& data_line)
    {
        stream << data_line.data;
        return stream;
    }
    
    std::string data;
    char delimiter;
    size_t size; // count of columns (elements)
};

struct Column {
    Column();
    ~Column();
    
    std::string Max() const;
    std::string Min() const;
    std::string Average() const;
    std::string StandardDeviation() const;

    TypeData type;
    std::string name;
    size_t size;
    void* value;
};

class Dataset
{
public:
    Dataset() : data_(nullptr), size_(0), delimiter_for_print_('\t') {}
    Dataset(std::string FilePath, bool IndexColumnExistsInFile, DataLine = DataLine());
    ~Dataset();

    void PrintData() const;
    size_t GetColumnCount() const;
    size_t GetRowCount(size_t index) const;
    TypeData GetColumnType(size_t index) const;
    std::string GetColumnName(size_t index) const;

    void Remove(size_t index);
    void Insert(size_t index, DataLine data_line);
    void ChangeDelimiterForPrint(char delimiter);
    void Head(size_t n = 5) const;
    void Tail(size_t n = 5) const;
    void Describe(std::string column_name) const;

    Dataset& operator=(const Dataset& dataset);
    DataLine operator[](size_t index) const;
private:
    void dispose();

    Column* data_;
	size_t size_; //count of columns
    char delimiter_for_print_;
};

TypeFile TypeOfFile(const std::string FilePath);
size_t CountOfColumns(char delimiter, std::string line);
TypeData TypeOfVariable(std::string str);
char DelimiterSymbol(TypeFile typef);

#endif