#include <iostream>
#include "dataset.h"

int main()
{
	DataLine s("11,22,33,wdf,qad,v,a,f", ',', 8);

	//Dataset data("./data-files/data.csv", 1);
	//data.ChangeDelimiterForPrint(' ');
	//Dataset data2("./data-files/data2.csv", 0);
	Dataset data3("./data-files/data3.csv", 0, s);
	//data.PrintData();
	//data.Remove(0);
	//data.Insert(1, DataLine("100,my,0.112", ',', 3));
	//data.PrintData();
	//data.Head(1);
	//data3.Tail(3);
	data3.Describe(s[1]);
	//data3.Describe(s[2]);
	//data3.Describe(s[7]);
	//Dataset data4;
	//data4.Insert(1, "100,my,0.112", ',');
	//data4.PrintData();
	//data2.PrintData();
	//data3.PrintData();
	//std::cout << data3[2] << '\n';

	//Dataset data_txt("./data-files/data.txt", 1);
	//Dataset data2_txt("./data-files/data2.txt", 0);
	//Dataset data3_txt("./data-files/data3.txt", 0, s);

	//data_txt.PrintData();
	//data2_txt.PrintData();
	//data3_txt.PrintData();

	return 0;
}
