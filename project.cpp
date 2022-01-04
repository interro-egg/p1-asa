#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
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
	std::unordered_map<long long, bool> map;
	long long number, maxSize, max = 0;

	std::getline(std::cin, xStr);
	std::getline(std::cin, yStr);
	std::istringstream xSs(xStr);
	std::istringstream ySs(yStr);

	while (xSs >> number) {
		x.push_back(number);
		map[number] = true;
	}

	while (ySs >> number) {
		if (map[number]) {
			y.push_back(number);
		}
	}

	std::vector<long long> tracker(y.size(), 0); // O(n)

	for (std::size_t i = 0; i < x.size(); i++) {
		maxSize = 0;
		for (std::size_t j = 0; j < y.size(); j++) {
			if (x[i] > y[j]) {
				maxSize = std::max(tracker[j], maxSize);
			} else if (x[i] == y[j]) {
				tracker[j] = std::max(tracker[j], maxSize + 1);
				if (tracker[j] > max) {
					max = tracker[j];
				}
			}
		}
	}

	return std::to_string(max) + '\n';
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