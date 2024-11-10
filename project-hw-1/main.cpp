#include <iostream>
#include "dataset.h"

int main()
{
	Dataset data("./data.csv", 1);
	Dataset data2("./data2.csv", 0);
	std::string s{ "11,22,33,wdf,qad,v,a,f" };
	Dataset data3("./data3.csv", 0, s);
	data.PrintData();
	data2.PrintData();
	data3.PrintData();

	return 0;
}
