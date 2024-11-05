#include<iostream>
#include"array.h"

int main(int argc, char* argv[])
{
	char b[5]{ 'z', 'A', 'o', 'e', 'B'};
	Array<char> a1(b, 5);
	a1.show();
	std::cout << a1.minimum(a1) << '\n';

	int* c = new int[5]{ 4, 4, 1, -20, 10 };
	Array<int> a2(c, 5);
	delete[] c;
	a2.show();
	std::cout << a2.minimum(a2) << '\n';

	bool d[3]{ true, false, true};
	Array<bool> a3(d, 3);
	a3.show();
	std::cout << a3.minimum(a3) << '\n';
	return 0;
}