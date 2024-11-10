#ifndef DATA_SET_H
#define DATA_SET_H

#include <iostream>
#include <fstream>
#include <sstream>

#include "data-column.h"

class Dataset
{
public:
    ~Dataset();
    Dataset(const std::string& FilePath, bool IndexColumnExistsInFile, Names ColumnNames = Names());
    void PrintData() const;
private:
    Column* data_;
	size_t size_;
};

std::string TypeOfFile(const std::string& FilePath);
size_t CountOfColumns(std::string& FileType, std::string& line);
std::string TypeOfVariable(std::string str);

#endif