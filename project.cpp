#include <iostream>
#include <string>

std::string problem1()
{
	return "Not implemented";
}

std::string problem2()
{
	return "Not implemented";
}

int main()
{
	int problem;
	std::cin >> problem;
	switch (problem) {
	case 1:
		std::cout << problem1() << std::endl;
		break;
	case 2:
		std::cout << problem2() << std::endl;
		break;
	default:
		std::cout << "Invalid problem number" << std::endl;
		break;
	}
}