#include <iostream>
#include <vector>

int main() {

	std::vector <int> c;
	if(c.empty())
		c.push_back(5);

	std::vector <int> c2(3);
	if (c2.empty())
		std::cout << "empty" << std::endl;
	std::vector <int> c3(3,5);

	c2.assign(2, 10);

	c2.swap(c);

	std::cout << c2.capacity() << std::endl;

	int arr[3] = { 10,20,30 };

	std::vector <int> c4(c3.begin(), c3.end());

	c4.~vector<int>();
	

	return 0;
}