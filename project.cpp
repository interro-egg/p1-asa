#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string problem1()
{
	return "Not implemented\n";
}

std::string problem2()
{
	std::vector<std::vector<long long>> matrix;
	std::vector<long long> x, y;
	std::string xStr, yStr;
	long long number;

	std::getline(std::cin, xStr);
	std::getline(std::cin, yStr);
	std::istringstream xSs(xStr);
	std::istringstream ySs(yStr);

	while (xSs >> number) {
		x.push_back(number);
	}

	while (ySs >> number) {
		y.push_back(number);
	}

	//! WRONG: does not care for INCREASING subsequences

	for (int i = 0; i < x.size(); i++) {
		for (int j = 0; j < y.size(); j++) {
			if (i == 0 || j == 0) {
				matrix[i][j] = 0;
			} else if (x[i] == y[j]) {
				matrix[i][j] = matrix[i - 1][j - 1] + 1;
			} else {
				matrix[i][j] = std::max(matrix[i - 1][j], matrix[i][j - 1]);
			}
		}
	}

	return "aa\n";
}

int main()
{
	int problem;
	std::cin >> problem;
	getchar(); // skip newline after problem number
	switch (problem) {
	case 1:
		std::cout << problem1();
		break;
	case 2:
		std::cout << problem2();
		break;
	default:
		std::cout << "Invalid problem number" << std::endl;
		break;
	}
}