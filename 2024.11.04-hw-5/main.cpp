#include<iostream>
#include"array.h"

int main(int argc, char* argv[])
{
	char b[5]{ 'z', 'A', 'o', 'e', 'B'};
	Array<char> a1(b);
	a1.show();
	std::cout << a1.minimum(a1) << '\n';

	int c[5]{ 4, 4, 1, -20, 10 };
	Array<int> a2(c);
	a2.show();
	std::cout << a2.minimum(a2) << '\n';

	bool d[5]{ true, false, true, false, false };
	Array<bool> a3(d);
	a3.show();
	std::cout << a3.minimum(a3) << '\n';
	return 0;
}